#ifndef TEST1PROPERTIES_H
#define TEST1PROPERTIES_H

#include <QWidget>
#include <Test1.h>

namespace Ui {
class Test1Properties_UI;
}

class Test1Properties_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Test1Properties_UI(QWidget *parent = 0);
    ~Test1Properties_UI();

    void setProperties(Test1Properties props);
    Test1Properties getProperties() { return m_properties; }

signals:
    void updated(Test1Properties newProps);

private slots:
    void handleApplyButton();

private:
    QString updateDetailString();

    Ui::Test1Properties_UI *ui;
    Test1Properties m_properties;

    const QString CHECKBOX_1_STR = "Checkbox 1 is checked.\n";
    const QString CHECKBOX_2_STR = "Checkbox 2 is checked.\n";
    const QString RADIO_1_STR = "Radio 1 is Selected.\n";
    const QString RADIO_2_STR = "Radio 2 is Selected.\n";
    const QString APPLY_STR = "Changes Applied.\n";
};
#endif // TEST1PROPERTIES_H
