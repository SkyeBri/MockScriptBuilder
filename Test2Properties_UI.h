#ifndef TEST2PROPERTIES_UI_H
#define TEST2PROPERTIES_UI_H

#include <QWidget>

namespace Ui {
class Test2Properties_UI;
}

struct Test2Properties
{
    int numInt{0};
    double numDouble{0.0};
    QString textString{""};
};
Q_DECLARE_METATYPE(Test2Properties)
QDataStream &operator<<(QDataStream &out, const Test2Properties &p);
QDataStream &operator>>(QDataStream &in, Test2Properties &p);

class Test2Properties_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Test2Properties_UI(QWidget *parent = 0);
    ~Test2Properties_UI();

    void setProperties(Test2Properties props);
    Test2Properties getProperties() { return m_properties; }

signals:
    void updated(Test2Properties newProps);

private slots:
    void handleBtnApplyClicked();

private:
    Ui::Test2Properties_UI *ui;
    Test2Properties m_properties;
};

#endif // TEST2PROPERTIES_UI_H
