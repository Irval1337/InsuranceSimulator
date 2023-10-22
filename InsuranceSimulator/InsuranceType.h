#pragma once

#include "InsuranceOffer.h"
#include <QVector>

class InsuranceType {
public:
    QVector<InsuranceOffer> offers() const;
    void setOffers(const QVector<InsuranceOffer> &newOffers);
    bool enabled() const;
    void setEnabled(bool newEnabled);
    int potential_customers_count() const;
    void setPotential_customers_count(int newPotential_customers_count);
    QPair<int, int> insured_events_range() const;
    void setInsured_events_range(const QPair<int, int> &newInsured_events_range);
    StatsData stats() const;
    void setStats(const StatsData &newStats);

signals:
    void offersChanged();
    void enabledChanged();
    void potential_customers_countChanged();
    void insured_events_rangeChanged();
    void statsChanged();

private:
    QVector<InsuranceOffer> offers_; // все предложения, которые доступны для этого типа
    bool enabled_; // предоставляем ли мы сейчас эти услуги
    int potential_customers_count_; // количество потенциальных покупателей
    QPair<int, int> insured_events_range_; // диапазон изменения количества страховых случаев каждый месяц
    StatsData stats_; // общая информация о клиентах

    Q_PROPERTY(QVector<InsuranceOffer> offers READ offers WRITE setOffers NOTIFY offersChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(int potential_customers_count READ potential_customers_count WRITE setPotential_customers_count NOTIFY potential_customers_countChanged)
    Q_PROPERTY(QPair<int, int> insured_events_range READ insured_events_range WRITE setInsured_events_range NOTIFY insured_events_rangeChanged)
    Q_PROPERTY(StatsData stats READ stats WRITE setStats NOTIFY statsChanged)
};

inline void InsuranceType::offersChanged() {
    StatsData stats;
    QMap<int, int> duration;
    for(int i = 0; i < offers_.size(); ++i) {
        stats.setTotal_customers_count(stats.total_customers_count() + offers_[i].stats().total_customers_count());
        stats.setMonth_customers_count(stats.month_customers_count() + offers_[i].stats().month_customers_count());
        stats.setTotal_revenue(stats.total_revenue() + offers_[i].stats().total_revenue());
        stats.setMonth_revenue(stats.month_revenue() + offers_[i].stats().month_revenue());
        stats.setTotal_payment_amount(stats.total_payment_amount() + offers_[i].stats().total_payment_amount());
        stats.setMonth_payment_amount(stats.month_payment_amount() + offers_[i].stats().month_payment_amount());


        auto durations = offers_[i].stats().duration_count();
        for(auto& k : durations.keys()) {
            int count = durations.value(k);
            duration[k] += count;
        }
    }
    stats.setDuration_count(duration);
    setStats(stats);
}

inline QVector<InsuranceOffer> InsuranceType::offers() const
{
    return offers_;
}

inline void InsuranceType::setOffers(const QVector<InsuranceOffer> &newOffers)
{
    if (offers_ == newOffers)
        return;
    offers_ = newOffers;
    emit offersChanged();
}

inline bool InsuranceType::enabled() const
{
    return enabled_;
}

inline void InsuranceType::setEnabled(bool newEnabled)
{
    if (enabled_ == newEnabled)
        return;
    enabled_ = newEnabled;
    emit enabledChanged();
}

inline int InsuranceType::potential_customers_count() const
{
    return potential_customers_count_;
}

inline void InsuranceType::setPotential_customers_count(int newPotential_customers_count)
{
    if (potential_customers_count_ == newPotential_customers_count)
        return;
    potential_customers_count_ = newPotential_customers_count;
    emit potential_customers_countChanged();
}

inline QPair<int, int> InsuranceType::insured_events_range() const
{
    return insured_events_range_;
}

inline void InsuranceType::setInsured_events_range(const QPair<int, int> &newInsured_events_range)
{
    if (insured_events_range_ == newInsured_events_range)
        return;
    insured_events_range_ = newInsured_events_range;
    emit insured_events_rangeChanged();
}

inline StatsData InsuranceType::stats() const
{
    return stats_;
}

inline void InsuranceType::setStats(const StatsData &newStats)
{
    if (stats_ == newStats)
        return;
    stats_ = newStats;
    emit statsChanged();
}
