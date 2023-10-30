#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLogValueAxis>
#include <QChart>
#include <QChartView>
#include "settingswindow.h"
#include "insurancetypedialog.h"
#include "insuranceofferdialog.h"
#include <QMessageBox>
#include "statsdialog.h"
#include "historydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    insurance = new Insurance();
    listp = nullptr;
    ui->pushButton_2->setVisible(false);
    series_->append(0, 0);

    auto chart = new QChart();
    chart->addSeries(series_);
    chart->createDefaultAxes();

    QValueAxis * axisX = new QValueAxis();
    axisX->setRange(0, 32);
    axisX->setTickCount(2);
    chart->setAxisX(axisX);

    gay = new QValueAxis();
    gay->setRange(0, 1);
    gay->setTickCount(2);
    chart->setAxisY(gay);

    series_->attachAxis(axisX);
    series_->attachAxis(gay);

    chart->setBackgroundVisible(false);
    chart->setMargins(QMargins(0,0,0,0));
    chart->legend()->hide();
    chart->setPlotAreaBackgroundVisible(true);

    auto chartView = new QChartView(chart);

    ui->horizontalLayout->addWidget(chartView);

    render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::int_to_months(int count) {
    if (count % 100 >= 11 && count % 100 <= 20)
        return QString::number(count) + " месяцев";
    else if (count % 10 == 1)
        return QString::number(count) + " месяц";
    else if (count % 10 >= 2 && count % 10 <= 4)
        return QString::number(count) + " месяца";
    else if (count % 10 >= 5 && count % 10 <= 9)
        return QString::number(count) + " месяцев";
    return QString::number(count) + " месяцев";
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->periodLabel->setAlignment(Qt::AlignCenter);
    ui->periodLabel->setText(int_to_months(value));
    ui->nextNmonths->setText("Вперед на " + int_to_months(value - curr_month_ + 1));
}

void MainWindow::on_pushButton_clicked() // Вперед
{
    if (curr_month_ == ui->horizontalSlider->maximum() || insurance->banned()) return;

    insurance->emulate(&hist_);

    curr_month_++;

    render();
    render_list();

    if (insurance->banned())
        QMessageBox::critical(this, "Внимание", "Ваша компания обонкротилась из-за невозможности выплаты по страховым случаям. Эмуляция завершена.");

    ui->horizontalSlider->setMinimum(curr_month_);
    ui->nextNmonths->setText("Вперед на " + int_to_months(ui->horizontalSlider->value() - curr_month_ + 1));
}

void MainWindow::on_nextNmonths_clicked() // Вперед N раз
{
    int cnt = ui->horizontalSlider->value() - curr_month_ + 1;
    for(int i = 0; i < cnt; ++i) {
        on_pushButton_clicked();
    }
}

void MainWindow::on_pushButton_5_clicked() // Вернуться
{
    if (curr_month_ == 1) return;
    curr_month_--;
    ui->horizontalSlider->setMinimum(curr_month_);
    ui->nextNmonths->setText("Вперед на " + int_to_months(ui->horizontalSlider->value() - curr_month_ + 1));
}

void MainWindow::render()
{
    if (!qFuzzyCompare(capitals_.back(), insurance->capital())) {
        capitals_.push_back(insurance->capital());
        mx = std::max(mx, capitals_.back());
        gay->setRange(0, mx);
        series_->append(curr_month_, capitals_.back());
    }
    setWindowTitle("Симулятор страховой [" + company_name_ + "]");
    ui->lineEdit->setText(QString::number(insurance->capital()) + "$");
    ui->lineEdit_2->setText(QString::number(insurance->stats().total_customers_count()));
}

void MainWindow::render_list()
{
    ui->listWidget->clear();
    if (list_level_ == 0) {
        for(auto& u : (insurance)->insurances()) {
            if (!u.enabled()) continue;
            ui->listWidget->addItem(u.insurance_type());
        }
    } else if (list_level_ == 1) {
        int ind = *(int*)listp;
        for(auto& u : insurance->insurances()[ind].offers()) {
            if (!u.enabled()) continue;
            ui->listWidget->addItem(u.insurance_company_name());
        }
    }
}

void MainWindow::on_pushButton_8_clicked() // Настройки
{
    (new SettingsWindow(insurance, &company_name_))->exec();
    render();
}


void MainWindow::on_pushButton_4_clicked() // Добавить
{
    if (list_level_ == 0) {
        InsuranceType* ptr = new InsuranceType();
        (new InsuranceTypeDialog(ptr))->exec();
        if (*ptr == InsuranceType()) return;

        auto insurs = insurance->insurances();
        for(auto& u : insurs) {
            if (u.insurance_type() == ptr->insurance_type()) {
                QMessageBox::warning(this, "Ошибка", "Тип с таким названием уже существует");
                return;
            }
        }

        insurs.append(*ptr);
        insurance->setInsurances(insurs);
        ui->listWidget->addItem(ptr->insurance_type());
        delete ptr;
    } else if (list_level_ == 1) {
        int ind = *(int*)listp;
        InsuranceOffer* ptr = new InsuranceOffer();
        (new InsuranceOfferDialog(ptr, insurance->insurances()[ind].insurance_type()))->exec();
        if (*ptr == InsuranceOffer()) return;

        auto offers = insurance->insurances()[ind].offers();
        for(auto& u : offers) {
            if (u.insurance_company_name() == ptr->insurance_company_name()) {
                QMessageBox::warning(this, "Ошибка", "Предложение с таким названием уже существует");
                return;
            }
        }

        offers.append(*ptr);
        auto insurs = insurance->insurances();
        insurs[ind].setOffers(offers);
        insurance->setInsurances(insurs);
        ui->listWidget->addItem(ptr->insurance_company_name());
        delete ptr;
    }
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    if (ui->listWidget->selectedItems().empty()) return;

    if (list_level_ == 0) {
        int index = ui->listWidget->row(ui->listWidget->selectedItems()[0]);
        listp = new int(index);
        list_level_++;
        ui->infoLabel->setText("Актуальные предложения по " + insurance->insurances()[index].insurance_type());
        ui->pushButton_2->setVisible(true);
        render_list();
    } else {
        int index = ui->listWidget->row(ui->listWidget->selectedItems()[0]);
        int sec_index = *(int*)listp;
        InsuranceOffer* ptr = new InsuranceOffer(insurance->insurances()[sec_index].offers()[index]);
        (new InsuranceOfferDialog(ptr, insurance->insurances()[sec_index].insurance_type()))->exec();

        auto offers = insurance->insurances()[sec_index].offers();
        auto ins = insurance->insurances();
        if (*ptr == InsuranceOffer()) {
            offers[index].setEnabled(false);
        } else {
            offers[index] = *ptr;
        }
        ins[sec_index].setOffers(offers);
        insurance->setInsurances(ins);
        delete ptr;
    }
}


void MainWindow::on_pushButton_3_clicked() // Назад
{
    if (list_level_ == 0) return;
    if (list_level_ == 1) {
        ui->infoLabel->setText("Предлагаемые виды страховок");
        ui->pushButton_2->setVisible(false);
    }
    list_level_--;
    render_list();
}


void MainWindow::on_pushButton_2_clicked() // Ред.
{
    int index = *(int*)listp;
    InsuranceType* ptr = new InsuranceType(insurance->insurances()[index]);
    (new InsuranceTypeDialog(ptr))->exec();

    auto ins = insurance->insurances();
    if (*ptr == InsuranceType()) {
        ins[index].setEnabled(false);
    } else {
        ins[index] = *ptr;
    }
    insurance->setInsurances(ins);
    delete ptr;
}


void MainWindow::on_pushButton_6_clicked() // Статистика
{
    (new StatsDialog(insurance->stats()))->exec();
}


void MainWindow::on_pushButton_7_clicked() // История
{
    (new HistoryDialog(&hist_))->exec();
}

