#pragma once

class StatsData {
public:
    int total_customers_count() const;
    void setTotal_customers_count(int newTotal_customers_count);
    int month_customers_count() const;
    void setMonth_customers_count(int newMonth_customers_count);
    int total_revenue() const;
    void setTotal_revenue(int newTotal_revenue);
    int month_revenue() const;
    void setMonth_revenue(int newMonth_revenue);
    int total_payment_amount() const;
    void setTotal_payment_amount(int newTotal_payment_amount);
    int month_payment_amount() const;
    void setMonth_payment_amount(int newMonth_payment_amount);

signals:
    void total_customers_countChanged();
    void month_customers_countChanged();
    void total_revenueChanged();
    void month_revenueChanged();
    void total_payment_amountChanged();
    void month_payment_amountChanged();

private:
    int total_customers_count_; // количество покупателей
    int month_customers_count_; // количество новых покупателей за месяц
    int total_revenue_; // общая выручка
    int month_revenue_; // выручка за прошлый месяц
    int total_payment_amount_; // общая сумма выплат за все время
    int month_payment_amount_; // сумма выплат за последний месяц
    Q_PROPERTY(int total_customers_count READ total_customers_count WRITE setTotal_customers_count NOTIFY total_customers_countChanged)
    Q_PROPERTY(int month_customers_count READ month_customers_count WRITE setMonth_customers_count NOTIFY month_customers_countChanged)
    Q_PROPERTY(int total_revenue READ total_revenue WRITE setTotal_revenue NOTIFY total_revenueChanged)
    Q_PROPERTY(int month_revenue READ month_revenue WRITE setMonth_revenue NOTIFY month_revenueChanged)
    Q_PROPERTY(int total_payment_amount READ total_payment_amount WRITE setTotal_payment_amount NOTIFY total_payment_amountChanged)
    Q_PROPERTY(int month_payment_amount READ month_payment_amount WRITE setMonth_payment_amount NOTIFY month_payment_amountChanged)
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

inline int StatsData::total_revenue() const
{
    return total_revenue_;
}

inline void StatsData::setTotal_revenue(int newTotal_revenue)
{
    if (total_revenue_ == newTotal_revenue)
        return;
    total_revenue_ = newTotal_revenue;
    emit total_revenueChanged();
}

inline int StatsData::month_revenue() const
{
    return month_revenue_;
}

inline void StatsData::setMonth_revenue(int newMonth_revenue)
{
    if (month_revenue_ == newMonth_revenue)
        return;
    month_revenue_ = newMonth_revenue;
    emit month_revenueChanged();
}

inline int StatsData::total_payment_amount() const
{
    return total_payment_amount_;
}

inline void StatsData::setTotal_payment_amount(int newTotal_payment_amount)
{
    if (total_payment_amount_ == newTotal_payment_amount)
        return;
    total_payment_amount_ = newTotal_payment_amount;
    emit total_payment_amountChanged();
}

inline int StatsData::month_payment_amount() const
{
    return month_payment_amount_;
}

inline void StatsData::setMonth_payment_amount(int newMonth_payment_amount)
{
    if (month_payment_amount_ == newMonth_payment_amount)
        return;
    month_payment_amount_ = newMonth_payment_amount;
    emit month_payment_amountChanged();
}
