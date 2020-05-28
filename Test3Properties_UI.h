#ifndef TEST3PROPERTIES_UI_H
#define TEST3PROPERTIES_UI_H

#include <QWidget>

namespace Ui {
class Test3Properties_UI;
}

class Test3Properties_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Test3Properties_UI(QWidget *parent = 0);
    ~Test3Properties_UI();

private:
    Ui::Test3Properties_UI *ui;
};

#endif // TEST3PROPERTIES_UI_H
