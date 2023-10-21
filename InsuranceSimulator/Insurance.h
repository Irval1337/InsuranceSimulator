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

    struct event {
        int type;
        double amount_diff;
        event(int type_, int amount_diff_) {
            type = type_;
            amount_diff = amount_diff_;
        }
    };
};

inline void Insurance::insurancesChanged() {
    StatsData stats;
    QMap<QPair<int, int>, int> duration;
    for(int i = 0; i < insurances_.size(); ++i) {
        stats.setTotal_customers_count(stats.total_customers_count() + insurances_[i].stats().total_customers_count());
        stats.setMonth_customers_count(stats.month_customers_count() + insurances_[i].stats().month_customers_count());
        stats.setTotal_revenue(stats.total_revenue() + insurances_[i].stats().total_revenue());
        stats.setMonth_revenue(stats.month_revenue() + insurances_[i].stats().month_revenue());
        stats.setTotal_payment_amount(stats.total_payment_amount() + insurances_[i].stats().total_payment_amount());
        stats.setMonth_payment_amount(stats.month_payment_amount() + insurances_[i].stats().month_payment_amount());

        for(auto& k : insurances_[i].stats().duration_count().keys()) {
            int count = insurances_[i].stats().duration_count().value(k);
            duration[k] += count;
        }
    }
    stats.setDuration_count(duration);
}

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
        auto offers = insurs[i].offers();

        QVector<event> events;

        int insurance_events = Random::get(insurs[i].insured_events_range().first, insurs[i].insured_events_range().second);
        QVector<int> pref_sums;
        pref_sums.push_back(offers[0].stats().total_customers_count());
        for(int j = 1; j < offers.size(); ++j) {
            pref_sums.push_back(pref_sums[pref_sums.size() - 1] + offers[j].stats().total_customers_count());
        }
        // + random shuffle

        for(int j = 0; j < insurance_events; ++j) {
            int _rnd = Random::get(0, pref_sums[pref_sums.size() - 1]);

            int L = -1, R = pref_sums.size(), M;
            while (L < R - 1) {
                M = L + (R - L) / 2;
                if (pref_sums[M] <= _rnd) L = M;
                else R = M;
            }

            double coeff = Random::get(0.0, 1.0);
            int ind = min(max(L, 0), offers.size() - 1);
            double amount = offers[ind].max_reimbursement_amount() * coeff;
            if (amount < offers[ind].franchise()) continue;
            events.push_back(event(1, amount));
        }

        for(int j = 0; j < offers.size(); ++j) {
            offers[j].setRelevance_period(offers[j].relevance_period() - 1);
            auto prev_stats = offers[j].stats();
            prev_stats.setMonth_revenue(0);
            prev_stats.setMonth_customers_count(0);
            prev_stats.setMonth_payment_amount(0);
            offers[j].setStats(prev_stats);
        }

        // adding new customers sqrt(sqrt(customers)) * rnd(0, 50) * выгода

        for(int j = 0; j < offers.size(); ++j) {
            QMap<int, int> next_duration;
            auto stats = offers[j].stats();
            stats.setMonth_customers_count(0);
            for(auto& k : offers[j].stats().duration_count().keys()) {
                int count = offers[j].stats().duration_count().value(k);
                if (k == 1) {
                    stats.setMonth_customers_count(stats.month_customers_count() - count);
                    stats.setTotal_customers_count(stats.total_customers_count() - count);
                } else {
                    next_duration[k - 1] += count;
                }
            }
            stats.setDuration_count(next_duration);
            offers[i].se
        }

        events.push_front(-capital() * tax_percentage());
    }
}
