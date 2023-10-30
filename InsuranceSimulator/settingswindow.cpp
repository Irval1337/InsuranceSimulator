#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QMessageBox>

SettingsWindow::SettingsWindow(Insurance* insurance_, QString* company_name_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow), insurance(insurance_), company_name(company_name_)
{
    ui->setupUi(this);
    setWindowTitle("Настройки");
    ui->buttonBox->buttons()[1]->setText("Отмена");

    ui->lineEdit->setText(QString::number(insurance->tax_percentage() * 100, 'g', 10));
    ui->lineEdit_2->setText(QString::number(insurance->capital(), 'g', 10));
    ui->lineEdit_3->setText(*company_name);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_buttonBox_accepted()
{
    bool ok = true;
    bool check = true;
    double tax = ui->lineEdit->text().toDouble(&ok) / 100;
    check &= ok;
    double capital = ui->lineEdit_2->text().toDouble(&ok);
    check &= ok;
    QString name = ui->lineEdit_3->text();

    if (!check) {
        QMessageBox::warning(this, "Ошибка", "Указанные данные имеют неверные типы");
    } else if (tax < 0 || tax > 100) {
        QMessageBox::warning(this, "Ошибка", "Процент налога должен находиться в промежутке от 0 до 100");
    } else if (capital < 0) {
        QMessageBox::warning(this, "Ошибка", "Капитал должен быть положительным числом");
    } else if (name.size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Название компании не может быть пустой строкой");
    } else {
        *company_name = name;
        insurance->setCapital(capital);
        insurance->setTax_percentage(tax);
    }
}

