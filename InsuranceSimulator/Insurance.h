#pragma once

#include "InsuranceType.h"
#include "Random.h"
#include "cmath"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Insurance {
public:
    Insurance() {
        insurances_ = QVector<InsuranceType>();
        tax_percentage_ = 0;
        stats_ = StatsData();
        capital_ = 0;
        banned_ = false;
    }
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

    void emulate(QVector<QString>* hist); // Функция для эмуляции работы компании в течение месяца
    bool save(QString path) const;
    bool open(QString path);

private:
    QVector<InsuranceType> insurances_; // все страховки, которые предоставляются компанией
    double tax_percentage_; // размер налога гос-ву
    StatsData stats_; // общая информация о клиентах
    double capital_; // капитал компании
    bool banned_; // обонкротились или нет

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

void Insurance::open(QString& path) {
    Insurance prev;

    try {
        QFile file(path);
        if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return false;
        }
        QString data = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject json = doc.object();

        prev.setBanned(false);
        prev.setCapital(json["capital"].toDouble());
        prev.setTax_percentage(json["tax_percentage"].toDouble());
        QVector<InsuranceType> ins;
        QJsonArray ins_arr = json["insurances"].toArray();
        for(QJsonValue& val : ins_arr) {
            QJsonObject obj = val.toObject();
            InsuranceType type;
            type.setEnabled(true);
            type.setInsurance_type(obj["insurance_type"].toString());
            type.setInsured_events_range({obj["insured_events_min"].toDouble(), obj["insured_events_max"].toDouble()});
            type.setPotential_customers_count(obj["potential_customers_count"].toInt());

            QJsonArray offers_arr = obj["offers"].toArray();
            QVector<InsuranceOffer> offers;
            for(QJsonValue& v : offers_arr) {
                QJsonObject ob = v.toObject();
                InsuranceOffer offer;
                offer.setEnabled(true);
                offer.setContribution_amount(ob["contribution_amount"].toDouble());
                offer.setContribution_period(ob["contribution_period"].toInt());
                offer.setDuration(ob["duration"].toInt());
                offer.setMax_reimbursement_amount(ob["max_reimbursement_amount"].toDouble());
                offer.setFranchise(ob["franchise"].toDouble());
                offer.setInsurance_company_name(ob["insurance_company_name"].toString());
                offer.setInsurance_type(type.insurance_type());
                offer.setRelevance_period(ob["relevance_period"].toInt());
                offers.push_back(offer);
            }
            type.setOffers(offers);
            ins.push_back(type);
        }
        prev.setInsurances(ins);

        *this = prev;
        return true;
    } catch (...) {
        return false;
    }
}

bool Insurance::save(QString path) const {
    if (path == QString()) {
        return false;
    }

    try {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
            return false;
        }
        QJsonObject json;
        json["capital"] = this->capital();
        json["tax_percentage"] = this->tax_percentage();
        QJsonArray ins;
        for(auto& in : insurances_) {
            QJsonObject in_json;
            in_json["insurance_type"] = in.insurance_type();
            in_json["insured_events_min"] = in.insured_events_range().first;
            in_json["insured_events_max"] = in.insured_events_range().second;
            in_json["potential_customers_count"] = in.potential_customers_count();
            QJsonArray offers;
            for(auto& of : in.offers()) {
                QJsonObject offer;
                offer["contribution_amount"] = of.contribution_amount();
                offer["contribution_period"] = of.contribution_period();
                offer["duration"] = of.duration();
                offer["max_reimbursement_amount"] = of.max_reimbursement_amount();
                offer["franchise"] = of.franchise();
                offer["insurance_company_name"] = of.insurance_company_name();
                offer["relevance_period"] = of.relevance_period();
                offers.push_back(offer);
            }
            in_json["offers"] = offers;
            ins.push_back(in_json);
        }
        json["insurances"] = ins;

        QTextStream stream(&file);
        stream << QJsonDocument(json).toJson();
        file.flush();
        file.close();

        return true;
    } catch (...) {
        return false;
    }
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

    StatsData stats = stats_;
    int customers = 0, payment = 0, revenue = 0;

    QMap<int, int> duration;
    for(int i = 0; i < insurances_.size(); ++i) {
        customers += insurances_[i].stats().month_customers_count();
        payment += insurances_[i].stats().month_payment_amount();
        revenue += insurances_[i].stats().month_revenue();

        auto durations = insurances_[i].stats().duration_count();
        for(auto& k : durations.keys()) {
            int count = durations.value(k);
            duration[k] += count;
        }
    }
    stats.setDuration_count(duration);
    stats.setMonth_customers_count(customers);
    stats.setMonth_payment_amount(payment);
    stats.setMonth_revenue(revenue);
    setStats(stats);
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
}

inline double sqr(double x) {
    return x * x;
}

inline void Insurance::emulate(QVector<QString>* hist) {
    setCapital(capital() - capital() * tax_percentage());
    auto insurs = insurances();
    QVector<InsuranceType> _ins = QVector<InsuranceType>();
    for(int i = 0; i < insurs.size(); ++i) {
        auto offers = insurs[i].offers();
        int prev = insurs[i].potential_customers_count();
        insurs[i].setPotential_customers_count(ceil(insurs[i].potential_customers_count() + (-1 + 2 * (Random::get(1, 100) % 2)) *
                                               (sqrt(insurs[i].potential_customers_count()) + 1) * Random::get(1.0, log(insurs[i].potential_customers_count()))));

        if (offers.empty()) {
            if (insurs[i].stats().total_customers_count() == 0 && !insurs[i].enabled())
                continue;
            _ins.push_back(insurs[i]);
            continue;
        }

        QVector<event> events; // события

        int insurance_events = 0; // кол-во страховых случаев
        if (stats().total_customers_count() != 0)
            insurance_events = (int)(ceil(Random::get(insurs[i].insured_events_range().first, insurs[i].insured_events_range().second) *
                            ((double)stats().total_customers_count() / 1000.0))) % stats().total_customers_count();
        if (!offers.empty()) {
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
                hist->push_back("Возмещение по " + offers[ind].insurance_company_name() + " - " + QString::number(amount));
            }
        }

        for(int j = 0; j < offers.size(); ++j) { // Периодичные выплаты
            for(auto& u : offers[j].stats().duration_count().keys()) {
                int count = offers[j].stats().duration_count().value(u);
                for(int k = 0; k < count; ++k) {
                    if (u != 1 && (offers[j].duration() - u - 1) % offers[j].contribution_period() == 0) {
                        events.push_back(event(3, offers[j].contribution_amount(), j)); // Тип 3 - выплата
                    }
                }
                hist->push_back("Выплаты по " + offers[j].insurance_company_name() + " - " + QString::number(count) + "x" + QString::number(offers[j].contribution_amount()) + "$");
            }
        }

        for(int j = 0; j < offers.size(); ++j) { // Добавляем новых пользователей
            if (!offers[j].enabled() || insurs[i].potential_customers_count() == 0) continue;
            int new_customers_count = ((int)sqrt(sqrt(offers[j].stats().total_customers_count())) + 1) * Random::get(0.0, 2.0)
                                            * offers[j].max_reimbursement_amount() / offers[j].duration() / offers[j].contribution_amount() *
                                            sqr(log2(prev) + 1) + 1; // TODO: добавить разность с рынком
            if (new_customers_count > prev && new_customers_count % prev < prev / 2)
                new_customers_count = prev / 2 + Random::get(0.0, 0.5) * prev;
            insurs[i].setPotential_customers_count(insurs[i].potential_customers_count() - new_customers_count);
            prev -= new_customers_count;
            hist->push_back("Новые клиенты по " + offers[j].insurance_company_name() + " - " + QString::number(new_customers_count));
            for(int k = 0; k < new_customers_count; ++k) {
                events.push_back(event(2, offers[j].contribution_amount(), j)); // Тип 2 - новый пользователь
            }
            StatsData prevStats = offers[j].stats();
            auto prevDuration = prevStats.duration_count();
            prevDuration[offers[j].duration() + 1] += new_customers_count;
            prevStats.setDuration_count(prevDuration);
            offers[j].setStats(prevStats);
        }

        std::random_shuffle(events.begin(), events.end());

        QVector<QPair<int, QPair<double, double>>> changed_stats(offers.size(), {0, {0, 0}});

        for(int j = 0; j < events.size(); ++j) {
            double diff = events[j].amount_diff;
            int offer = events[j].offer;
            if (events[j].type == 0) { // налог
                setCapital(capital() - diff);
            } else if (events[j].type == 1) { // выплата
                changed_stats[offer].second.second += diff;
                setCapital(capital() - diff);
            } else if (events[j].type == 2) { // новый пользователь
                changed_stats[offer].second.first += diff;
                changed_stats[offer].first++;
                setCapital(capital() + diff);
            } else { // Выплата от пользователя
                changed_stats[offer].second.first += diff;
                setCapital(capital() + diff);
            }

            if (capital() < 0) {
                setBanned(true);
                hist->push_back("БАНКРОТ");
            }
        }

        QVector<InsuranceOffer> _offers = QVector<InsuranceOffer>();
        for(int j = 0; j < offers.size(); ++j) {
            if (offers[j].stats().duration_count().empty() && !offers[j].enabled())
                continue;

            offers[j].setRelevance_period(offers[j].relevance_period() - 1);
            if (offers[j].relevance_period() == 0) {
                offers[j].setEnabled(false);
                hist->push_back("Предложение по " + offers[j].insurance_company_name() + " больше не актуально");
            }

            auto prev_stats = offers[j].stats();
            QMap<int, int> nextDuration;
            auto prevDuration = prev_stats.duration_count();
            for(auto& k : prevDuration.keys()) {
                int count = prevDuration.value(k);
                if (k == 1) {
                    changed_stats[j].first -= count;
                    hist->push_back("Конец контракта по " + offers[j].insurance_company_name() + " - " + QString::number(count));
                } else
                    nextDuration[k - 1] += count;
            }
            prev_stats.setDuration_count(nextDuration);
            prev_stats.setMonth_customers_count(changed_stats[j].first);
            prev_stats.setMonth_payment_amount(changed_stats[j].second.first);
            prev_stats.setMonth_revenue(changed_stats[j].second.second);
            offers[j].setStats(prev_stats);
            _offers.push_back(offers[j]);
        }

        if (insurs[i].potential_customers_count() <= 0) {
            insurs[i].setPotential_customers_count(prev * Random::get(1.0, 2.0));
        }

        insurs[i].setOffers(_offers);
        if (insurs[i].stats().total_customers_count() == 0 && !insurs[i].enabled())
            continue;
        _ins.push_back(insurs[i]);
    }
    setInsurances(_ins);
}
