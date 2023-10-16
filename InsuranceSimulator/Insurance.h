#pragma once

#include "InsuranceType.h"

class Insurance {
public:
    QVector<InsuranceType> insurances() const;
    void setInsurances(const QVector<InsuranceType> &newInsurances);
    double tax_percentage() const;
    void setTax_percentage(double newTax_percentage);
    StatsData stats() const;
    void setStats(const StatsData &newStats);

signals:
    void insurancesChanged();
    void tax_percentageChanged();
    void statsChanged();

private:
    QVector<InsuranceType> insurances_; // все страховки, которые предоставляются компанией
    double tax_percentage_; // размер налога гос-ву
    StatsData stats_; // общая информация о клиентах
    Q_PROPERTY(QVector<InsuranceType> insurances READ insurances WRITE setInsurances NOTIFY insurancesChanged)
    Q_PROPERTY(double tax_percentage READ tax_percentage WRITE setTax_percentage NOTIFY tax_percentageChanged)
    Q_PROPERTY(StatsData stats READ stats WRITE setStats NOTIFY statsChanged)
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
