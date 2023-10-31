#include "insuranceofferdialog.h"
#include "ui_insuranceofferdialog.h"
#include <QMessageBox>
#include "statsdialog.h"

InsuranceOfferDialog::InsuranceOfferDialog(InsuranceOffer* offer_, QString type_name_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsuranceOfferDialog), offer(offer_), type_name(type_name_)
{
    ui->setupUi(this);
    setWindowTitle("Добавить новое предложение");
    ui->buttonBox->buttons()[1]->setText("Отмена");
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);

    if (*offer_ == InsuranceOffer()) return;
    setWindowTitle("Редактирование предложения");
    ui->lineEdit->setText(offer_->insurance_company_name());
    ui->lineEdit_2->setText(QString::number(offer_->contribution_period()));
    ui->lineEdit_3->setText(QString::number(offer_->contribution_amount(), 'g', 10));
    ui->lineEdit_4->setText(QString::number(offer_->duration()));
    ui->lineEdit_5->setText(QString::number(offer_->max_reimbursement_amount(), 'g', 10));
    ui->lineEdit_6->setText(QString::number(offer_->franchise(), 'g', 10));
    ui->lineEdit_7->setText(QString::number(offer_->relevance_period()));
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
}

InsuranceOfferDialog::~InsuranceOfferDialog()
{
    delete ui;
}

void InsuranceOfferDialog::on_buttonBox_accepted()
{
    bool ok = true;
    bool check = true;
    QString name = ui->lineEdit->text();
    long long period_cont = ui->lineEdit_2->text().toLongLong(&ok);
    check &= ok;
    double sum = ui->lineEdit_3->text().toDouble(&ok);
    check &= ok;
    long long duration = ui->lineEdit_4->text().toLongLong(&ok);
    check &= ok;
    double max_sum = ui->lineEdit_5->text().toDouble(&ok);
    check &= ok;
    double min_sum = ui->lineEdit_6->text().toDouble(&ok);
    check &= ok;
    long long meme_duration = ui->lineEdit_7->text().toLongLong(&ok);
    check &= ok;

    if (!check) {
        QMessageBox::warning(this, "Ошибка", "Указанные данные имеют неверные типы");
    } else if (name.size() == 0) {
        QMessageBox::warning(this, "Ошибка", "Название предложения не может быть пустой строкой");
    } else if (period_cont < 0) {
        QMessageBox::warning(this, "Ошибка", "Периодичность взноса должена быть положительным числом");
    } else if (sum < 0) {
        QMessageBox::warning(this, "Ошибка", "Cумма взноса должена быть положительным числом");
    } else if (duration < 0) {
        QMessageBox::warning(this, "Ошибка", "Срок действия договора должен быть положительным числом");
    } else if (max_sum < 0) {
        QMessageBox::warning(this, "Ошибка", "Максимальная сумма возмещения должена быть положительным числом");
    } else if (min_sum < 0) {
        QMessageBox::warning(this, "Ошибка", "Минимальная сумма возмещения должена быть положительным числом");
    } else if (min_sum > max_sum) {
        QMessageBox::warning(this, "Ошибка", "Минимальная сумма возмещения не может быть больше максимальной");
    } else if (duration < 0) {
        QMessageBox::warning(this, "Ошибка", "Срок действия предложения должен быть положительным числом");
    } else {
        offer->setEnabled(true);
        offer->setContribution_amount(sum);
        offer->setContribution_period(period_cont);
        offer->setDuration(duration);
        offer->setMax_reimbursement_amount(max_sum);
        offer->setFranchise(min_sum);
        offer->setInsurance_company_name(name);
        offer->setRelevance_period(meme_duration);
        offer->setInsurance_type(type_name);
    }
}


void InsuranceOfferDialog::on_pushButton_clicked() // Удалить
{
    *offer = InsuranceOffer();
    close();
}


void InsuranceOfferDialog::on_pushButton_2_clicked() // Статистика
{
    (new StatsDialog(offer->stats()))->exec();
}

