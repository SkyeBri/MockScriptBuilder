#include "Test2Properties_UI.h"
#include "ui_Test2Properties_UI.h"

QDataStream &operator<<(QDataStream &out, const Test2Properties &p)
{
    out << p.numInt << p.numDouble << p.textString;
    return out;
}

QDataStream &operator>>(QDataStream &in, Test2Properties &p)
{
    in >> p.numInt;
    in >> p.numDouble;
    in >> p.textString;
    return in;
}

Test2Properties_UI::Test2Properties_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test2Properties_UI)
{
    ui->setupUi(this);
    QValidator *intValidator = new QIntValidator(0,9999999,this);
    QValidator *fValidator = new QDoubleValidator(0.0,99999999.9999999999,10,this);
    ui->leNumInt->setValidator(intValidator);
    ui->leNumDouble->setValidator(fValidator);

    connect(ui->btnApply, &QPushButton::clicked, this, &Test2Properties_UI::handleBtnApplyClicked);
}

Test2Properties_UI::~Test2Properties_UI()
{
    delete ui;
}

void Test2Properties_UI::setProperties(Test2Properties props)
{
    m_properties = props;
    ui->leNumInt->setText(QString::number(m_properties.numInt));
    ui->leNumDouble->setText(QString::number(m_properties.numDouble));
    ui->leString->setText(m_properties.textString);
}

void Test2Properties_UI::handleBtnApplyClicked()
{
    m_properties.numDouble = ui->leNumDouble->text().toDouble();
    m_properties.numInt = ui->leNumInt->text().toInt();
    m_properties.textString = ui->leString->text();
    emit updated(m_properties);
}
