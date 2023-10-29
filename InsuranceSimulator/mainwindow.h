#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Insurance.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_nextNmonths_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    Insurance* insurance;
    int curr_month_ = 1;
    QString company_name_ = "???";
    int list_level_ = 0;
    void* listp = nullptr;
    QVector<QString> hist_ = QVector<QString>();

    QString int_to_months(int n);
    void render();
    void render_list();
};
#endif // MAINWINDOW_H
