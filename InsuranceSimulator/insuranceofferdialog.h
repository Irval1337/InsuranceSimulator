#ifndef INSURANCEOFFERDIALOG_H
#define INSURANCEOFFERDIALOG_H

#include <QDialog>
#include "InsuranceOffer.h"

namespace Ui {
class InsuranceOfferDialog;
}

class InsuranceOfferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsuranceOfferDialog(InsuranceOffer* offer_, QString type_name_, QWidget *parent = nullptr);
    ~InsuranceOfferDialog();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::InsuranceOfferDialog *ui;
    InsuranceOffer* offer;
    QString type_name;
};

#endif // INSURANCEOFFERDIALOG_H
