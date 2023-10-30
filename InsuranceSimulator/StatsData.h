#pragma once

#include <QMap>

class StatsData {
public:
    StatsData() {
        total_customers_count_ = 0;
        month_customers_count_ = 0;
        total_revenue_ = 0;
        month_revenue_ = 0;
        total_payment_amount_ = 0;
        month_payment_amount_ = 0;
        duration_count_ = QMap<long long, long long>();
    }

    long long total_customers_count() const;
    void setTotal_customers_count(long long newTotal_customers_count);
    long long month_customers_count() const;
    void setMonth_customers_count(long long newMonth_customers_count);
    double total_revenue() const;
    void setTotal_revenue(double newTotal_revenue);
    double month_revenue() const;
    void setMonth_revenue(double newMonth_revenue);
    double total_payment_amount() const;
    void setTotal_payment_amount(double newTotal_payment_amount);
    double month_payment_amount() const;
    void setMonth_payment_amount(double newMonth_payment_amount);
    QMap<long long, long long> duration_count() const;
    void setDuration_count(const QMap<long long, long long>& newDuration_count);

    bool operator==(const StatsData& other) const {
        return total_customers_count_ == other.total_customers_count_ &&
                month_customers_count_ == other.month_customers_count_ &&
                qFuzzyCompare(total_revenue_, other.total_revenue_) &&
                qFuzzyCompare(month_revenue_, other.month_revenue_) &&
                qFuzzyCompare(total_payment_amount_, other.total_payment_amount_) &&
                qFuzzyCompare(month_payment_amount_, other.month_payment_amount_) &&
                duration_count_ == other.duration_count_;
    }
    bool operator!=(const StatsData& other) const {
        return !(*this == other);
    }

private:
    long long total_customers_count_; // количество покупателей
    long long month_customers_count_; // количество новых покупателей за месяц
    double total_revenue_; // общая выручка
    double month_revenue_; // выручка за прошлый месяц
    double total_payment_amount_; // общая сумма выплат за все время
    double month_payment_amount_; // сумма выплат за последний месяц

    QMap<long long, long long> duration_count_; // сроки страховки текущих пользователей
};

inline long long StatsData::total_customers_count() const
{
    return total_customers_count_;
}

inline void StatsData::setTotal_customers_count(long long newTotal_customers_count)
{
    if (total_customers_count_ == newTotal_customers_count)
        return;
    total_customers_count_ = newTotal_customers_count;
}

inline long long StatsData::month_customers_count() const
{
    return month_customers_count_;
}

inline void StatsData::setMonth_customers_count(long long newMonth_customers_count)
{
    if (month_customers_count_ == newMonth_customers_count)
        return;
    setTotal_customers_count(total_customers_count_ + newMonth_customers_count);
    month_customers_count_ = newMonth_customers_count;
}

inline double StatsData::total_revenue() const
{
    return total_revenue_;
}

inline void StatsData::setTotal_revenue(double newTotal_revenue)
{
    if (qFuzzyCompare(total_revenue_, newTotal_revenue))
        return;
    total_revenue_ = newTotal_revenue;
}

inline double StatsData::month_revenue() const
{
    return month_revenue_;
}

inline void StatsData::setMonth_revenue(double newMonth_revenue)
{
    if (qFuzzyCompare(month_revenue_, newMonth_revenue))
        return;
    setTotal_revenue(total_revenue_ + newMonth_revenue);
    month_revenue_ = newMonth_revenue;
}

inline double StatsData::total_payment_amount() const
{
    return total_payment_amount_;
}

inline void StatsData::setTotal_payment_amount(double newTotal_payment_amount)
{
    if (qFuzzyCompare(total_payment_amount_, newTotal_payment_amount))
        return;
    total_payment_amount_ = newTotal_payment_amount;
}

inline double StatsData::month_payment_amount() const
{
    return month_payment_amount_;
}

inline void StatsData::setMonth_payment_amount(double newMonth_payment_amount)
{
    if (qFuzzyCompare(month_payment_amount_, newMonth_payment_amount))
        return;
    setTotal_payment_amount(total_payment_amount_ + newMonth_payment_amount);
    month_payment_amount_ = newMonth_payment_amount;
}

inline QMap<long long, long long> StatsData::duration_count() const
{
    return duration_count_;
}

inline void StatsData::setDuration_count(const QMap<long long, long long> &newDuration_count)
{
    if (duration_count_ == newDuration_count)
        return;
    duration_count_ = newDuration_count;
}

template<class T>
bool operator==(const QVector<T>& vec, const QVector<T>& vec2) {
    if (vec.size() != vec2.size()) return false;
    long long sz = vec.size();
    for(long long i = 0; i < sz; ++i) {
        if (vec[i] != vec2[i]) return false;
    }
    return true;
}
