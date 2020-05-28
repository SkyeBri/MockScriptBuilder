#include "Test1Properties_UI.h"
#include "ui_Test1Properties_UI.h"

Test1Properties_UI::Test1Properties_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test1Properties_UI)
{
    ui->setupUi(this);
    ui->radio1->setChecked(true);
    ui->lblDetails->setText(RADIO_1_STR);
    connect(ui->btnApply, &QPushButton::clicked, this, &Test1Properties_UI::handleApplyButton);
}

Test1Properties_UI::~Test1Properties_UI()
{
    delete ui;
}

void Test1Properties_UI::setProperties(Test1Properties props)
{
    m_properties = props;
    ui->cb1->setChecked(m_properties.check1);
    ui->cb2->setChecked(m_properties.check2);
    ui->radio1->setChecked(m_properties.radio1);
    ui->radio2->setChecked(m_properties.radio2);
    updateDetailString();
}

void Test1Properties_UI::handleApplyButton()
{
    m_properties.check1 = ui->cb1->isChecked();
    m_properties.check2 = ui->cb2->isChecked();
    m_properties.radio1 = ui->radio1->isChecked();
    m_properties.radio2 = ui->radio2->isChecked();

    QString prevDetails = ui->lblDetails->text();
    QString details = updateDetailString();
    details += (((prevDetails == details) || (prevDetails == details+APPLY_STR)) ? "" : APPLY_STR);
    ui->lblDetails->setText(details);
    emit updated(m_properties);
}

QString Test1Properties_UI::updateDetailString()
{
    QString details = (m_properties.check1 ? CHECKBOX_1_STR : "") +
                      (m_properties.check2 ? CHECKBOX_2_STR : "") +
                      (m_properties.radio1 ? RADIO_1_STR : "") +
                      (m_properties.radio2 ? RADIO_2_STR : "");
    ui->lblDetails->setText(details);
    return details;
}
