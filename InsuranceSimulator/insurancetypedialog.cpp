#include "insurancetypedialog.h"
#include "ui_insurancetypedialog.h"
#include <QMessageBox>
#include "statsdialog.h"

InsuranceTypeDialog::InsuranceTypeDialog(InsuranceType* insurance_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsuranceTypeDialog), insurance(insurance_)
{
    ui->setupUi(this);
    setWindowTitle("Добавить новый тип");
    ui->buttonBox->buttons()[1]->setText("Отмена");
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    insurance = insurance_;

    if (*insurance_ == InsuranceType()) return;
    setWindowTitle("Редактирование типа");
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->lineEdit->setText(QString::number(insurance_->potential_customers_count()));
    ui->lineEdit_2->setText(QString::number(insurance_->insured_events_range().first, 'g', 10));
    ui->lineEdit_3->setText(QString::number(insurance_->insured_events_range().second, 'g', 10));
    ui->lineEdit_4->setText(insurance->insurance_type());
}

InsuranceTypeDialog::~InsuranceTypeDialog()
{
    delete ui;
}

void InsuranceTypeDialog::on_buttonBox_accepted()
{
    bool ok = true;
    bool check = true;
    long long customers = ui->lineEdit->text().toLongLong(&ok);
    check &= ok;
    double min = ui->lineEdit_2->text().toDouble(&ok);
    check &= ok;
    double max = ui->lineEdit_3->text().toDouble(&ok);
    check &= ok;
    QString type = ui->lineEdit_4->text();

    if (!check) {
        QMessageBox::warning(this, "Ошибка", "Указанные данные имеют неверные типы");
    } else if (customers < 0) {
        QMessageBox::warning(this, "Ошибка", "Потенциальное количество клиентов должено быть положительным числом");
    } else if (min < 0 || max < 0 || max > 1000) {
        QMessageBox::warning(this, "Ошибка", "Количество страховых случаев должено быть положительным числом, не превыщающем 1000");
    } else if (min > max) {
        QMessageBox::warning(this, "Ошибка", "Минимум не может быть больше максимума");
    } else if (type.size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Тип страховки не может быть пустой строкой");
    } else {
        QVector<InsuranceOffer> tmp;
        if (*insurance != InsuranceType()) {
            tmp = insurance->offers();
        }
        insurance->setOffers(tmp);
        insurance->setEnabled(true);
        insurance->setPotential_customers_count(customers);
        QPair<double, double> p = {min, max};
        insurance->setInsured_events_range(p);
        insurance->setInsurance_type(type);
    }
}


void InsuranceTypeDialog::on_pushButton_clicked() // Удалить
{
    *insurance = InsuranceType();
    close();
}


void InsuranceTypeDialog::on_pushButton_2_clicked() // Статистика
{
    (new StatsDialog(insurance->stats()))->exec();
}

