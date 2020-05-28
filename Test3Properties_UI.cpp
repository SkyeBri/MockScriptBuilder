#include "Test3Properties_UI.h"
#include "ui_Test3Properties_UI.h"

Test3Properties_UI::Test3Properties_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test3Properties_UI)
{
    ui->setupUi(this);
}

Test3Properties_UI::~Test3Properties_UI()
{
    delete ui;
}
