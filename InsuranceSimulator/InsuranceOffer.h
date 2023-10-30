#pragma once

#include "StatsData.h"
#include <QString>

class InsuranceOffer {
public:
    double contribution_amount() const;
    void setContribution_amount(double newContribution_amount);
    long long contribution_period() const;
    void setContribution_period(long long newContribution_period);
    long long duration() const;
    void setDuration(long long newDuration);
    double max_reimbursement_amount() const;
    void setMax_reimbursement_amount(double newMax_reimbursement_amount);
    double franchise() const;
    void setFranchise(double newFranchise);
    QString insurance_company_name() const;
    void setInsurance_company_name(const QString &newInsurance_company_name);
    QString insurance_type() const;
    void setInsurance_type(const QString &newInsurance_type);
    long long relevance_period() const;
    void setRelevance_period(long long newRelevance_period);
    StatsData stats() const;
    void setStats(const StatsData &newStats);
    bool enabled() const;
    void setEnabled(bool newEnabled);

    bool operator==(const InsuranceOffer& other) const {
        return enabled_ == other.enabled_ && qFuzzyCompare(contribution_amount_, other.contribution_amount_) &&
                contribution_period_ == other.contribution_period_ && duration_ == other.duration_ &&
                qFuzzyCompare(max_reimbursement_amount_, other.max_reimbursement_amount_) && qFuzzyCompare(franchise_, other.franchise_) &&
                insurance_company_name_ == other.insurance_company_name_ && insurance_type_ == other.insurance_type_ &&
                relevance_period_ == other.relevance_period_ && stats_ == other.stats_;
    }
    bool operator!=(const InsuranceOffer& other) const {
        return !(*this == other);
    }

private:
    bool enabled_; // предоставляется ли эта услуга
    double contribution_amount_; // взнос
    long long contribution_period_; // периодичность взноса
    long long duration_; // срок действия договора
    double max_reimbursement_amount_; // максимальныя сумма возмещения
    double franchise_; // минимальная сумма возмещения (франшиза)
    QString insurance_company_name_; // название компании, которая предлагает страховку (ОСАГО/КАСКО)
    QString insurance_type_; // общий тип, к которому относится это предложение (авто/здоровье/жилье)
    long long relevance_period_; // сколько еще месяцев предложение актуально
    StatsData stats_; // общая информация о клиентах
};

inline double InsuranceOffer::contribution_amount() const
{
    return contribution_amount_;
}

inline void InsuranceOffer::setContribution_amount(double newContribution_amount)
{
    if (contribution_amount_ == newContribution_amount)
        return;
    contribution_amount_ = newContribution_amount;
}

inline long long InsuranceOffer::contribution_period() const
{
    return contribution_period_;
}

inline void InsuranceOffer::setContribution_period(long long newContribution_period)
{
    if (contribution_period_ == newContribution_period)
        return;
    contribution_period_ = newContribution_period;
}

inline long long InsuranceOffer::duration() const
{
    return duration_;
}

inline void InsuranceOffer::setDuration(long long newDuration)
{
    if (duration_ == newDuration)
        return;
    duration_ = newDuration;
}

inline double InsuranceOffer::max_reimbursement_amount() const
{
    return max_reimbursement_amount_;
}

inline void InsuranceOffer::setMax_reimbursement_amount(double newMax_reimbursement_amount)
{
    if (qFuzzyCompare(max_reimbursement_amount_, newMax_reimbursement_amount))
        return;
    max_reimbursement_amount_ = newMax_reimbursement_amount;
}

inline double InsuranceOffer::franchise() const
{
    return franchise_;
}

inline void InsuranceOffer::setFranchise(double newFranchise)
{
    if (qFuzzyCompare(franchise_, newFranchise))
        return;
    franchise_ = newFranchise;
}

inline QString InsuranceOffer::insurance_company_name() const
{
    return insurance_company_name_;
}

inline void InsuranceOffer::setInsurance_company_name(const QString &newInsurance_company_name)
{
    if (insurance_company_name_ == newInsurance_company_name)
        return;
    insurance_company_name_ = newInsurance_company_name;
}

inline QString InsuranceOffer::insurance_type() const
{
    return insurance_type_;
}

inline void InsuranceOffer::setInsurance_type(const QString &newInsurance_type)
{
    if (insurance_type_ == newInsurance_type)
        return;
    insurance_type_ = newInsurance_type;
}

inline long long InsuranceOffer::relevance_period() const
{
    return relevance_period_;
}

inline void InsuranceOffer::setRelevance_period(long long newRelevance_period)
{
    if (relevance_period_ == newRelevance_period)
        return;
    relevance_period_ = newRelevance_period;
    if (relevance_period_ == 0)
        setEnabled(false);
}

inline StatsData InsuranceOffer::stats() const
{
    return stats_;
}

inline void InsuranceOffer::setStats(const StatsData &newStats)
{
    if (stats_ == newStats)
        return;
    stats_ = newStats;
}

inline bool InsuranceOffer::enabled() const
{
    return enabled_;
}

inline void InsuranceOffer::setEnabled(bool newEnabled)
{
    if (enabled_ == newEnabled)
        return;
    enabled_ = newEnabled;
}
