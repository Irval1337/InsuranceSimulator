#pragma once

#include "qtmetamacros.h"
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
    }

    int total_customers_count() const;
    void setTotal_customers_count(int newTotal_customers_count);
    int month_customers_count() const;
    void setMonth_customers_count(int newMonth_customers_count);
    double total_revenue() const;
    void setTotal_revenue(double newTotal_revenue);
    double month_revenue() const;
    void setMonth_revenue(double newMonth_revenue);
    double total_payment_amount() const;
    void setTotal_payment_amount(double newTotal_payment_amount);
    double month_payment_amount() const;
    void setMonth_payment_amount(double newMonth_payment_amount);
    QMap<QPair<int, int>, int> duration_count() const;
    void setDuration_count(const QMap<QPair<int, int>, int>& newDuration_count);

    bool operator==(const StatsData& other) const {
        return total_customers_count_ == other.total_customers_count_ &&
                month_customers_count_ == other.month_customers_count_ &&
                total_revenue_ == other.total_revenue_ &&
                month_revenue_ == other.month_revenue_ &&
                total_payment_amount_ == other.total_payment_amount_ &&
                month_payment_amount_ == other.month_payment_amount_ &&
                duration_count_ == other.duration_count_;
    }

signals:
    void total_customers_countChanged();
    void month_customers_countChanged();
    void total_revenueChanged();
    void month_revenueChanged();
    void total_payment_amountChanged();
    void month_payment_amountChanged();
    void duration_countChanged();

private:
    int total_customers_count_; // количество покупателей
    int month_customers_count_; // количество новых покупателей за месяц
    double total_revenue_; // общая выручка
    double month_revenue_; // выручка за прошлый месяц
    double total_payment_amount_; // общая сумма выплат за все время
    double month_payment_amount_; // сумма выплат за последний месяц

    QMap<QPair<int, int>, int> duration_count_; // сроки страховки текущих пользователей

    Q_PROPERTY(int total_customers_count READ total_customers_count WRITE setTotal_customers_count NOTIFY total_customers_countChanged)
    Q_PROPERTY(int month_customers_count READ month_customers_count WRITE setMonth_customers_count NOTIFY month_customers_countChanged)
    Q_PROPERTY(double total_revenue READ total_revenue WRITE setTotal_revenue NOTIFY total_revenueChanged)
    Q_PROPERTY(double month_revenue READ month_revenue WRITE setMonth_revenue NOTIFY month_revenueChanged)
    Q_PROPERTY(double total_payment_amount READ total_payment_amount WRITE setTotal_payment_amount NOTIFY total_payment_amountChanged)
    Q_PROPERTY(double month_payment_amount READ month_payment_amount WRITE setMonth_payment_amount NOTIFY month_payment_amountChanged)
    Q_PROPERTY(QMap<int, int> duration_count READ duration_count WRITE setDuration_count NOTIFY duration_countChanged)
};

inline int StatsData::total_customers_count() const
{
    return total_customers_count_;
}

inline void StatsData::setTotal_customers_count(int newTotal_customers_count)
{
    if (total_customers_count_ == newTotal_customers_count)
        return;
    total_customers_count_ = newTotal_customers_count;
    emit total_customers_countChanged();
}

inline int StatsData::month_customers_count() const
{
    return month_customers_count_;
}

inline void StatsData::setMonth_customers_count(int newMonth_customers_count)
{
    if (month_customers_count_ == newMonth_customers_count)
        return;
    month_customers_count_ = newMonth_customers_count;
    emit month_customers_countChanged();
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
    emit total_revenueChanged();
}

inline double StatsData::month_revenue() const
{
    return month_revenue_;
}

inline void StatsData::setMonth_revenue(double newMonth_revenue)
{
    if (qFuzzyCompare(month_revenue_, newMonth_revenue))
        return;
    month_revenue_ = newMonth_revenue;
    emit month_revenueChanged();
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
    emit total_payment_amountChanged();
}

inline double StatsData::month_payment_amount() const
{
    return month_payment_amount_;
}

inline void StatsData::setMonth_payment_amount(double newMonth_payment_amount)
{
    if (qFuzzyCompare(month_payment_amount_, newMonth_payment_amount))
        return;
    month_payment_amount_ = newMonth_payment_amount;
    emit month_payment_amountChanged();
}

inline QMap<QPair<int, int>, int> StatsData::duration_count() const
{
    return duration_count_;
}

inline void StatsData::setDuration_count(const QMap<QPair<int, int>, int> &newDuration_count)
{
    if (duration_count_ == newDuration_count)
        return;
    duration_count_ = newDuration_count;
    emit duration_countChanged();
}

template<class T>
bool operator==(const QVector<T>& vec, const QVector<T>& vec2) {
    if (vec.size() != vec2.size()) return false;
    int sz = vec.size();
    for(int i = 0; i < sz; ++i) {
        if (vec[i] != vec2[i]) return false;
    }
    return true;
}
