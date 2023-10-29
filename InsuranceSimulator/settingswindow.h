#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "Insurance.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(Insurance* insurance_, QString* company_name_, QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsWindow *ui;
    Insurance* insurance;
    QString* company_name;
};

#endif // SETTINGSWINDOW_H
