#ifndef INSURANCETYPEDIALOG_H
#define INSURANCETYPEDIALOG_H

#include <QDialog>
#include "InsuranceType.h"

namespace Ui {
class InsuranceTypeDialog;
}

class InsuranceTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsuranceTypeDialog(InsuranceType* insurance_, QWidget *parent = nullptr);
    ~InsuranceTypeDialog();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::InsuranceTypeDialog *ui;
    InsuranceType* insurance;
};

#endif // INSURANCETYPEDIALOG_H
