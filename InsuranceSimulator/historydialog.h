#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QVector<QString>* hist_, QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::HistoryDialog *ui;
    QVector<QString>* hist;
};

#endif // HISTORYDIALOG_H
