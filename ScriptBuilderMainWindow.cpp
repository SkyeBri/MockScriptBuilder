#include "ScriptBuilderMainWindow.h"
#include "ui_ScriptBuilderMainWindow.h"

#include <QFile>
#include <QTextStream>

//QDataStream override definitions for drag/drop with QVariant data
QDataStream &operator<<(QDataStream &out, const BlockType &t)
{
    out << static_cast<int>(t); return out;
}
QDataStream &operator>>(QDataStream &in, BlockType &t)
{
    int temp;
    in >> temp;
    t = static_cast<BlockType>(temp);
    return in;
}

QDataStream &operator<<(QDataStream &out, const NoneProperties &p)
{
    return out;
}
QDataStream &operator>>(QDataStream &in, NoneProperties &p)
{
    return in;
}

QDataStream &operator<<(QDataStream &out, const PropertyVariant &p)
{
    out << static_cast<BlockType>(p.which());
    switch(static_cast<BlockType>(p.which()))
    {
    case BlockType::TEST_1:
        out << boost::get<Test1Properties>(p);
        break;
    case BlockType::TEST_2:
        out << boost::get<Test2Properties>(p);
        break;
    default:
        out << boost::get<NoneProperties>(p);
        break;
    }
    return out;
}
QDataStream &operator>>(QDataStream &in, PropertyVariant &p)
{
    BlockType type;
    in >> type;
    switch(type)
    {
        case BlockType::TEST_1:
        {
            Test1Properties temp;
            in >> temp;
            p = temp;
            break;
        }
        case BlockType::TEST_2:
        {
            Test2Properties temp;
            in >> temp;
            p = temp;
            break;
        }
        default:
        {
            NoneProperties temp;
            p = temp;
        }
    }
    return in;
}

QDataStream &operator<<(QDataStream &out, const BlockProperties &bt)
{
    out << bt.type << bt.properties;
    return out;
}
QDataStream &operator>>(QDataStream &in, BlockProperties &bt)
{
    in >> bt.type;
    in >> bt.properties;
    return in;
}

// "REAL CODE" STARTS HERE

ScriptBuilderMainWindow::ScriptBuilderMainWindow(QApplication &parentApp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScriptBuilderMainWindow),
    m_parentApp(parentApp)
{
    ui->setupUi(this);
    qRegisterMetaType<BlockProperties>("BlockProperties");
    qRegisterMetaTypeStreamOperators<BlockProperties>("BlockProperties");

    // The following two calls are necessary in the VM to have proper drag/drop functionality, and do
    // not appear to be required in my actual linuxbox...but it doesn't hurt to have them...
    ui->listWidgetBlockOptions->setAcceptDrops(false);
    ui->listWidgetScriptBuilder->setAcceptDrops(true);

    //Setup Initial Block Properties
    Test1Properties test1Props;
    BlockProperties block1Props = {BlockType::TEST_1,test1Props};

    ui->listWidgetBlockOptions->item(0)->setData(Qt::UserRole, QVariant::fromValue(block1Props));

    Test2Properties test2Props;
    BlockProperties block2Props = {BlockType::TEST_2, test2Props};
    ui->listWidgetBlockOptions->item(1)->setData(Qt::UserRole, QVariant::fromValue(block2Props));

    NoneProperties noProps;
    BlockProperties block3Props = {BlockType::TEST_3, noProps};
    ui->listWidgetBlockOptions->item(2)->setData(Qt::UserRole, QVariant::fromValue(block3Props));

    connect(ui->btnRemove,&QPushButton::clicked,this,&ScriptBuilderMainWindow::handleBtnRemove);
    connect(ui->listWidgetScriptBuilder, &QListWidget::itemSelectionChanged,this,&ScriptBuilderMainWindow::handleListBuilderItemSelectionChanged);
    connect(ui->page1, &Test1Properties_UI::updated,this,&ScriptBuilderMainWindow::handlePage1Updated);
    connect(ui->page2, &Test2Properties_UI::updated,this,&ScriptBuilderMainWindow::handlePage2Updated);

    //TODO: make open action open
    //TODO: make save action save
    //TODO: make run action run

    //TODO: Figure out how to drag buttons... If anyone has ideas for this
    //      (or if anyone knows the secrets of making QListWidgetItems look like buttons via css)
    //      feel free to fix it :)
//    buttonifyList(ui->listWidgetBlockOptions);
//    buttonifyList(ui->listWidgetScriptBuilder);
    setTheme(DarkTheme);
}

ScriptBuilderMainWindow::~ScriptBuilderMainWindow()
{
    delete ui;
}

void ScriptBuilderMainWindow::handleBtnRemove()
{
    qDeleteAll(ui->listWidgetScriptBuilder->selectedItems());
}

void ScriptBuilderMainWindow::buttonifyList(QListWidget *list)
{
    for(int i = 0; i < list->count(); ++i)
    {
        QListWidgetItem* itm = list->item(i);
        QPushButton* btn = new QPushButton(itm->text());
        //TODO: How to make drag?
        list->setItemWidget(itm,btn);
    }
}

void ScriptBuilderMainWindow::handleListBuilderItemSelectionChanged()
{
    if(ui->listWidgetScriptBuilder->selectedItems().empty())
    {
        ui->stackedWidget->setCurrentIndex(static_cast<int>(BlockType::NONE));
        return;
    }
    BlockProperties props = qvariant_cast<BlockProperties>(ui->listWidgetScriptBuilder->currentItem()->data(Qt::UserRole));
    ui->stackedWidget->setCurrentIndex(static_cast<int>(props.type));
    switch(props.type)
    {
    case BlockType::TEST_1:
        ui->page1->setProperties(boost::get<Test1Properties>(props.properties));
        break;
    case BlockType::TEST_2:
        ui->page2->setProperties(boost::get<Test2Properties>(props.properties));
        break;
    default:
        break;
    }
}

void ScriptBuilderMainWindow::handlePage1Updated(Test1Properties newProps)
{
    if(ui->listWidgetScriptBuilder->selectedItems().empty())
    {
        return; //We should never get here
    }
    BlockProperties props {BlockType::TEST_1,newProps};
    ui->listWidgetScriptBuilder->currentItem()->setData(Qt::UserRole,QVariant::fromValue(props));
}

void ScriptBuilderMainWindow::handlePage2Updated(Test2Properties newProps)
{
    if(ui->listWidgetScriptBuilder->selectedItems().empty())
    {
        return; //We should never get here
    }
    BlockProperties props {BlockType::TEST_2,newProps};
    ui->listWidgetScriptBuilder->currentItem()->setData(Qt::UserRole,QVariant::fromValue(props));
}

void ScriptBuilderMainWindow::setTheme(const Theme &theme)
{
    QFile f(":/variable-windows.css");
    if(f.open(QFile::ReadOnly))
    {
        QTextStream ts(&f);
        QString style = ts.readAll();

        style.replace("CWB_COLOR", theme.ContainerBackground.name())
             .replace("CWHB_COLOR", theme.ContainerHandleBackground.name())
             .replace("SWB_COLOR", theme.SectionBackground.name())
             .replace("SWBC_COLOR", theme.SectionBorder.name())
             .replace("STWB_COLOR", theme.SectionTitleBackground.name())
             .replace("STWBC_COLOR", theme.SectionTitleBorder.name())
             .replace("STWBA_COLOR_0", theme.SelectedTabHighlight.name())
             .replace("STWBA_COLOR_1", theme.SelectedTabBackground.name())
             .replace("SCWB_COLOR", theme.SectionContentBackground.name())
             .replace("SCWBC_COLOR", theme.SectionContentBorder.name())
             .replace("MAIN_COLOR_0", theme.MainColor0.name())
             .replace("MAIN_COLOR_1", theme.MainColor1.name())
             .replace("TEXT_COLOR_0", theme.TextColor.name())
             .replace("DISABLED_COLOR", theme.DisabledTextColor.name());
        m_parentApp.setStyleSheet(style);
    }
}
