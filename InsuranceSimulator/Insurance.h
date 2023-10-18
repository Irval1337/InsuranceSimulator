#pragma once

#include "InsuranceType.h"
#include "Random.h"
#include "cmath"

class Insurance {
public:
    QVector<InsuranceType> insurances() const;
    void setInsurances(const QVector<InsuranceType> &newInsurances);
    double tax_percentage() const;
    void setTax_percentage(double newTax_percentage);
    StatsData stats() const;
    void setStats(const StatsData &newStats);
    double capital() const;
    void setCapital(double newCapital);
    bool banned() const;
    void setBanned(bool newBanned);

    void emulate(); // Функция для эмуляции работы компании в течение месяца

signals:
    void insurancesChanged();
    void tax_percentageChanged();
    void statsChanged();
    void capitalChanged();
    void bannedChanged();

private:
    QVector<InsuranceType> insurances_; // все страховки, которые предоставляются компанией
    double tax_percentage_; // размер налога гос-ву
    StatsData stats_; // общая информация о клиентах
    double capital_; // капитал компании
    bool banned_; // обонкротились или нет
    Q_PROPERTY(QVector<InsuranceType> insurances READ insurances WRITE setInsurances NOTIFY insurancesChanged)
    Q_PROPERTY(double tax_percentage READ tax_percentage WRITE setTax_percentage NOTIFY tax_percentageChanged)
    Q_PROPERTY(StatsData stats READ stats WRITE setStats NOTIFY statsChanged)
    Q_PROPERTY(double capital READ capital WRITE setCapital NOTIFY capitalChanged)
    Q_PROPERTY(bool banned READ banned WRITE setBanned NOTIFY bannedChanged)
};

inline QVector<InsuranceType> Insurance::insurances() const
{
    return insurances_;
}

inline void Insurance::setInsurances(const QVector<InsuranceType> &newInsurances)
{
    if (insurances_ == newInsurances)
        return;
    insurances_ = newInsurances;
    emit insurancesChanged();
}

inline double Insurance::tax_percentage() const
{
    return tax_percentage_;
}

inline void Insurance::setTax_percentage(double newTax_percentage)
{
    if (qFuzzyCompare(tax_percentage_, newTax_percentage))
        return;
    tax_percentage_ = newTax_percentage;
    emit tax_percentageChanged();
}

inline StatsData Insurance::stats() const
{
    return stats_;
}

inline void Insurance::setStats(const StatsData &newStats)
{
    if (stats_ == newStats)
        return;
    stats_ = newStats;
    emit statsChanged();
}

inline double Insurance::capital() const
{
    return capital_;
}

inline void Insurance::setCapital(double newCapital)
{
    if (qFuzzyCompare(capital_, newCapital))
        return;
    capital_ = newCapital;
    emit capitalChanged();
}

inline bool Insurance::banned() const
{
    return banned_;
}

inline void Insurance::setBanned(bool newBanned)
{
    if (banned_ == newBanned)
        return;
    banned_ = newBanned;
    emit bannedChanged();
}

void Insurance::emulate() {
    auto insurs = insurances();
    for(int i = 0; i < insurs.size(); ++i) {
        if (!insurs[i].enabled()) continue;
        double tax = capital() * tax_percentage();
        // todo tax

        int insurance_events = Random::get(insurs[i].insured_events_range().first, insurs[i].insured_events_range().second);
        int customers = insurs[i].stats().total_customers_count();
        QVector<int> pref_sums;
        pref_sums.push_back(insurs[i].offers()[0].stats().total_customers_count());
        for(int j = 1; j < insurs[i].offers().size(); ++j) {
            pref_sums.push_back(pref_sums[pref_sums.size() - 1] + insurs[i].offers()[j].stats().total_customers_count());
        }

        // todo QVector<event>, event = new customer, bad event, tax (в начале месяца)
        // + random shuffle

        for(int j = 0; j < insurance_events; ++j) {
            int _rnd = Random::get(0, pref_sums[pref_sums.size() - 1]);

            int L = -1, R = pref_sums.size(), M;
            while (L < R - 1) {
                M = L + (R - L) / 2;
                if (pref_sums[M] < _rnd) L = M;
                else R = M;
            }

            // bad event with R-th offer
        }

        // adding new customers sqrt(sqrt(customers)) * rnd(0, 50) * выгода
    }
}
