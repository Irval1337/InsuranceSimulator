#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include "StatsData.h"

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(StatsData data_, QWidget *parent = nullptr);
    ~StatsDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StatsDialog *ui;
    StatsData data;
};

#endif // STATSDIALOG_H
