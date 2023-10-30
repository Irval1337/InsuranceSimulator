#include "statsdialog.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(StatsData data_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatsDialog), data(data_)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(data_.total_customers_count()));
    ui->lineEdit_2->setText(QString::number(data_.month_customers_count()));
    ui->lineEdit_3->setText(QString::number(data_.total_payment_amount(), 'g', 10) + "$");
    ui->lineEdit_4->setText(QString::number(data_.month_payment_amount(), 'g', 10) + "$");
    ui->lineEdit_5->setText(QString::number(data_.total_revenue(), 'g', 10) + "$");
    ui->lineEdit_6->setText(QString::number(data_.month_revenue(), 'g', 10) + "$");

    setWindowTitle("Статистика");
}

StatsDialog::~StatsDialog()
{
    delete ui;
}

void StatsDialog::on_pushButton_clicked()
{
    close();
}

