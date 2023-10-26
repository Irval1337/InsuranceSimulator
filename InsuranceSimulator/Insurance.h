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
        int offer;
        event(int type_, double amount_diff_, int offer_) {
            type = type_;
            amount_diff = amount_diff_;
            offer = offer_;
        }
    };
};

inline void Insurance::insurancesChanged() {
    StatsData stats;
    QMap<int, int> duration;
    for(int i = 0; i < insurances_.size(); ++i) {
        stats.setTotal_customers_count(stats.total_customers_count() + insurances_[i].stats().total_customers_count());
        stats.setMonth_customers_count(stats.month_customers_count() + insurances_[i].stats().month_customers_count());
        stats.setTotal_revenue(stats.total_revenue() + insurances_[i].stats().total_revenue());
        stats.setMonth_revenue(stats.month_revenue() + insurances_[i].stats().month_revenue());
        stats.setTotal_payment_amount(stats.total_payment_amount() + insurances_[i].stats().total_payment_amount());
        stats.setMonth_payment_amount(stats.month_payment_amount() + insurances_[i].stats().month_payment_amount());

        auto durations = insurances_[i].stats().duration_count();
        for(auto& k : durations.keys()) {
            int count = durations.value(k);
            duration[k] += count;
        }
    }
    stats.setDuration_count(duration);
    setStats(stats);
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

        QVector<event> events; // события

        int insurance_events = Random::get(insurs[i].insured_events_range().first, insurs[i].insured_events_range().second) % stats().total_customers_count(); // кол-во страховых случаев
        QVector<int> pref_sums; // префикс-суммы для определения предложения страховки
        pref_sums.push_back(offers[0].stats().total_customers_count());
        for(int j = 1; j < offers.size(); ++j) {
            pref_sums.push_back(pref_sums[pref_sums.size() - 1] + offers[j].stats().total_customers_count());
        }

        for(int j = 0; j < insurance_events; ++j) {
            int _rnd = Random::get(0, pref_sums[pref_sums.size() - 1]); // рандомный номер клиента

            int L = -1, R = pref_sums.size(), M; // ищем предложение
            while (L < R - 1) {
                M = L + (R - L) / 2;
                if (pref_sums[M] <= _rnd) L = M;
                else R = M;
            }

            double coeff = Random::get(0.0, 1.0); // коэффициент ущерба
            int ind = fmin(fmax(L, 0), offers.size() - 1); // L - номер предложения, в котором произошел страховой случай, ind нормирован
            double amount = offers[ind].max_reimbursement_amount() * coeff; // сумма для возмещения
            if (amount < offers[ind].franchise()) continue; // если франшиза больше, то не добавляем событие
            events.push_back(event(1, amount, ind)); // Тип 1 - страховое возмещение
        }

        for(int j = 0; j < offers.size(); ++j) { // Добавляем новых пользователей
            if (!offers[j].enabled()) continue;
            int new_customers_count = sqrt(sqrt(offers[j].stats().total_customers_count())) * Random::get(0, 5) *
                    offers[j].max_reimbursement_amount() / offers[j].duration() / offers[j].contribution_amount(); // TODO: добавить разность с рынком
            for(int k = 0; k < new_customers_count; ++k) {
                events.push_back(event(2, offers[j].contribution_amount(), j)); // Тип 2 - новый пользователь
            }
            StatsData prevStats = offers[j].stats();
            auto prevDuration = prevStats.duration_count();
            prevDuration[offers[j].contribution_period() + 1] += new_customers_count;
            prevStats.setDuration_count(prevDuration);
            offers[j].setStats(prevStats);
        }

        std::random_shuffle(events.begin(), events.end());
        events.push_front(event(0, capital() * tax_percentage(), -1)); // 0 - налог гос-ву

        StatsData newStats = stats();
        newStats.setMonth_customers_count(0);
        newStats.setMonth_payment_amount(0);
        newStats.setMonth_revenue(0);

        for(int j = 0; j < events.size(); ++j) {
            double diff = events[j].amount_diff;
            int offer = events[j].offer;
            if (events[j].type == 0) { // налог
                newStats.setMonth_revenue(newStats.month_revenue() + diff);
                setCapital(capital() - diff);
            } else if (events[j].type == 1) { // выплата
                auto prevStats = offers[j].stats();
                prevStats.setMonth_revenue(prevStats.month_revenue() + diff);
                offers[j].setStats(prevStats);
                setCapital(capital() - diff);
            } else { // новый пользователь
                auto prevStats = offers[j].stats();
                prevStats.setMonth_payment_amount(prevStats.month_payment_amount() + diff);
                prevStats.setMonth_customers_count(prevStats.month_customers_count() + 1);
                offers[j].setStats(prevStats);
                setCapital(capital() + diff);
            }

            if (capital() < 0) {
                setBanned(true);
            }
        }

        for(int j = 0; j < offers.size(); ++j) {
            offers[j].setRelevance_period(offers[j].relevance_period() - 1);
            if (offers[j].relevance_period() == 0) offers[j].setEnabled(false);

            auto prev_stats = offers[j].stats();
            QMap<int, int> nextDuration;
            auto prevDuration = prev_stats.duration_count();
            for(auto& k : prevDuration.keys()) {
                int count = prevDuration.value(k);
                if (k == 1) {
                    prev_stats.setMonth_customers_count(prev_stats.month_customers_count() - count);
                }
                nextDuration[k - 1] += count;
            }
            prev_stats.setDuration_count(nextDuration);
            offers[j].setStats(prev_stats);
            if (nextDuration.empty() && !offers[j].enabled())
                offers.erase(offers.begin() + j);
        }

        insurs[i].setOffers(offers);
    }
    setInsurances(insurs);
}
