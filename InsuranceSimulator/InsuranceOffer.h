#pragma once

#include "StatsData.h"
#include <QString>

class InsuranceOffer {
public:
    int contribution_amount() const;
    void setContribution_amount(int newContribution_amount);
    int contribution_period() const;
    void setContribution_period(int newContribution_period);
    int duration() const;
    void setDuration(int newDuration);
    double max_reimbursement_amount() const;
    void setMax_reimbursement_amount(double newMax_reimbursement_amount);
    double franchise() const;
    void setFranchise(double newFranchise);
    QString insurance_company_name() const;
    void setInsurance_company_name(const QString &newInsurance_company_name);
    QString insurance_type() const;
    void setInsurance_type(const QString &newInsurance_type);
    int relevance_period() const;
    void setRelevance_period(int newRelevance_period);
    StatsData stats() const;
    void setStats(const StatsData &newStats);

    bool enabled() const;
    void setEnabled(bool newEnabled);

signals:
    void contribution_amountChanged();
    void contribution_periodChanged();
    void durationChanged();
    void max_reimbursement_amountChanged();
    void franchiseChanged();
    void insurance_company_nameChanged();
    void insurance_typeChanged();
    void relevance_periodChanged();
    void statsChanged();

    void enabledChanged();

private:
    bool enabled_; // предоставляется ли эта услуга
    int contribution_amount_; // взнос
    int contribution_period_; // периодичность взноса
    int duration_; // срок действия договора
    double max_reimbursement_amount_; // максимальныя сумма возмещения
    double franchise_; // минимальная сумма возмещения (франшиза)
    QString insurance_company_name_; // название компании, которая предлагает страховку (ОСАГО/КАСКО)
    QString insurance_type_; // общий тип, к которому относится это предложение (авто/здоровье/жилье)
    int relevance_period_; // сколько еще месяцев предложение актуально
    StatsData stats_; // общая информация о клиентах

    Q_PROPERTY(int contribution_amount READ contribution_amount WRITE setContribution_amount NOTIFY contribution_amountChanged)
    Q_PROPERTY(int contribution_period READ contribution_period WRITE setContribution_period NOTIFY contribution_periodChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(double max_reimbursement_amount READ max_reimbursement_amount WRITE setMax_reimbursement_amount NOTIFY max_reimbursement_amountChanged)
    Q_PROPERTY(double franchise READ franchise WRITE setFranchise NOTIFY franchiseChanged)
    Q_PROPERTY(QString insurance_company_name READ insurance_company_name WRITE setInsurance_company_name NOTIFY insurance_company_nameChanged)
    Q_PROPERTY(QString insurance_type READ insurance_type WRITE setInsurance_type NOTIFY insurance_typeChanged)
    Q_PROPERTY(int relevance_period READ relevance_period WRITE setRelevance_period NOTIFY relevance_periodChanged)
    Q_PROPERTY(StatsData stats READ stats WRITE setStats NOTIFY statsChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
};

inline int InsuranceOffer::contribution_amount() const
{
    return contribution_amount_;
}

inline void InsuranceOffer::setContribution_amount(int newContribution_amount)
{
    if (contribution_amount_ == newContribution_amount)
        return;
    contribution_amount_ = newContribution_amount;
    emit contribution_amountChanged();
}

inline int InsuranceOffer::contribution_period() const
{
    return contribution_period_;
}

inline void InsuranceOffer::setContribution_period(int newContribution_period)
{
    if (contribution_period_ == newContribution_period)
        return;
    contribution_period_ = newContribution_period;
    emit contribution_periodChanged();
}

inline int InsuranceOffer::duration() const
{
    return duration_;
}

inline void InsuranceOffer::setDuration(int newDuration)
{
    if (duration_ == newDuration)
        return;
    duration_ = newDuration;
    emit durationChanged();
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
    emit max_reimbursement_amountChanged();
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
    emit franchiseChanged();
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
    emit insurance_company_nameChanged();
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
    emit insurance_typeChanged();
}

inline int InsuranceOffer::relevance_period() const
{
    return relevance_period_;
}

inline void InsuranceOffer::setRelevance_period(int newRelevance_period)
{
    if (relevance_period_ == newRelevance_period)
        return;
    relevance_period_ = newRelevance_period;
    emit relevance_periodChanged();
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
    emit statsChanged();
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
    emit enabledChanged();
}
