#pragma once

#include "InsuranceOffer.h"
#include <QVector>

class InsuranceType {
public:
    QVector<InsuranceOffer> offers() const;
    void setOffers(const QVector<InsuranceOffer> &newOffers);
    bool enabled() const;
    void setEnabled(bool newEnabled);
    long long potential_customers_count() const;
    void setPotential_customers_count(long long newPotential_customers_count);
    QPair<double, double> insured_events_range() const;
    void setInsured_events_range(const QPair<double, double> &newInsured_events_range);
    StatsData stats() const;
    void setStats(const StatsData &newStats);
    QString insurance_type() const;
    void setInsurance_type(const QString& newInsurance_type);

    bool operator==(const InsuranceType& other) const {
        return offers_ == other.offers_ && enabled_ == other.enabled_ && potential_customers_count_ == other.potential_customers_count_ &&
                insured_events_range_ == other.insured_events_range_ && stats_ == other.stats_;
    }
    bool operator!=(const InsuranceType& other) const {
        return !(*this == other);
    }

private:
    QVector<InsuranceOffer> offers_; // все предложения, которые доступны для этого типа
    bool enabled_; // предоставляем ли мы сейчас эти услуги
    long long potential_customers_count_; // количество потенциальных покупателей
    QPair<double, double> insured_events_range_; // диапазон изменения количества страховых случаев каждый месяц
    StatsData stats_; // общая информация о клиентах
    QString insurance_type_; // тип страховки
};

inline QString InsuranceType::insurance_type() const {
    return insurance_type_;
}

inline void InsuranceType::setInsurance_type(const QString& newInsurance_type)
{
    if (insurance_type_ == newInsurance_type)
        return;
    insurance_type_ = newInsurance_type;
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

    StatsData stats = stats_;
    long long customers = 0, payment = 0, revenue = 0;

    QMap<long long, long long> duration;
    for(long long i = 0; i < offers_.size(); ++i) {
        customers += offers_[i].stats().month_customers_count();
        payment += offers_[i].stats().month_payment_amount();
        revenue += offers_[i].stats().month_revenue();

        auto durations = offers_[i].stats().duration_count();
        for(auto& k : durations.keys()) {
            long long count = durations.value(k);
            duration[k] += count;
        }
    }
    stats.setDuration_count(duration);
    stats.setMonth_customers_count(customers);
    stats.setMonth_payment_amount(payment);
    stats.setMonth_revenue(revenue);
    setStats(stats);
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
}

inline long long InsuranceType::potential_customers_count() const
{
    return potential_customers_count_;
}

inline void InsuranceType::setPotential_customers_count(long long newPotential_customers_count)
{
    if (potential_customers_count_ == newPotential_customers_count)
        return;
    potential_customers_count_ = newPotential_customers_count;
}

inline QPair<double, double> InsuranceType::insured_events_range() const
{
    return insured_events_range_;
}

inline void InsuranceType::setInsured_events_range(const QPair<double, double> &newInsured_events_range)
{
    if (insured_events_range_ == newInsured_events_range)
        return;
    insured_events_range_ = newInsured_events_range;
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
}
