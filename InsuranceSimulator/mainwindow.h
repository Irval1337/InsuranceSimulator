#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Insurance.h"
#include <QLineSeries>
#include <QValueAxis>

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

    void on_action_4_triggered();

    void on_action_9_triggered();

private:
    Ui::MainWindow *ui;
    Insurance* insurance;
    long long curr_month_ = 1;
    QString company_name_ = "???";
    long long list_level_ = 0;
    void* listp = nullptr;
    QVector<QString> hist_ = QVector<QString>();
    QVector<double> capitals_ = { 0 };
    QLineSeries *series_ = new QLineSeries();
    QValueAxis* gay = nullptr;
    double mx = 0;

    QString long long_to_months(long long n);
    void render();
    void render_list();
};
#endif // MAINWINDOW_H
