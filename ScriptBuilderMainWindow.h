#ifndef SCRIPTBUILDERMAINWINDOW_H
#define SCRIPTBUILDERMAINWINDOW_H

#include <boost/variant.hpp>

#include <QMainWindow>
#include <Theme.h>
#include <Test1Properties_UI.h>
#include <Test2Properties_UI.h>

namespace Ui {
class ScriptBuilderMainWindow;
}

enum class BlockType
{
    NONE = 0,
    TEST_1 = 1,
    TEST_2 = 2,
    TEST_3 = 3
};
QDataStream &operator<<(QDataStream &out, const BlockType &t);
QDataStream &operator>>(QDataStream &in, BlockType &t);

struct NoneProperties {};
QDataStream &operator<<(QDataStream &out, const NoneProperties &p);
QDataStream &operator>>(QDataStream &in, NoneProperties &p);

using PropertyVariant = boost::variant<NoneProperties,Test1Properties,Test2Properties>;
QDataStream &operator<<(QDataStream &out, const PropertyVariant &p);
QDataStream &operator>>(QDataStream &in, PropertyVariant &p);

struct BlockProperties
{
    BlockType type;
    PropertyVariant properties;
};
Q_DECLARE_METATYPE(BlockProperties)
QDataStream &operator<<(QDataStream &out, const BlockProperties &bt);
QDataStream &operator>>(QDataStream &in, BlockProperties &bt);

class QListWidget;
class ScriptBuilderMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScriptBuilderMainWindow(QApplication &parentApp, QWidget *parent = 0);
    ~ScriptBuilderMainWindow();

private slots:
    void handleBtnRemove();
    void handleListBuilderItemSelectionChanged();
    void handlePage1Updated(Test1Properties newProps);
    void handlePage2Updated(Test2Properties newProps);

private:
    void buttonifyList(QListWidget* list);
    void setTheme(const Theme& theme);

    Ui::ScriptBuilderMainWindow *ui;
    QApplication &m_parentApp;
};

#endif // SCRIPTBUILDERMAINWINDOW_H
