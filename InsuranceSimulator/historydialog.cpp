#include "historydialog.h"
#include "ui_historydialog.h"

HistoryDialog::HistoryDialog(QVector<QString>* hist_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog), hist(hist_)
{
    ui->setupUi(this);
    setWindowTitle("История работы");
    for(auto& u : *hist_) {
        ui->listWidget->addItem(u);
    }
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::on_pushButton_clicked()
{
    close();
}

