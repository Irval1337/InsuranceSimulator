## InsuranceSimulator

### Classes

#### InsuranceOffer: // страховое предложение
 * int contribution_amount // взнос
 * int contribution_period (in months) // периодичность взноса
 * int duration (in months) // срок действия договора
 * double max_reimbursement_amount (in rubles) // максимальныя сумма возмещения
 * double franchise (in rubles) // минимальная сумма возмещения (франшиза)
 * string insurance_company_name // название компании, которая предлагает страховку (ОСАГО/КАСКО)
 * string insurance_type // общий тип, к которому относится это предложение (авто/здоровье/жилье)
 * int relevance_period (in months) // сколько еще месяцев предложение актуально

 * int total_customers_count // количество покупателей этой страховки
 * int month_customers_count // количество новых покупателей за месяц
 * int total_revenue // общая выручка с этого предложения
 * int month_revenue // выручка за прошлый месяц
 * int total_payment_amount // общая сумма выплат за все время
 * int month_payment_amount // сумма выплат за последний месяц
 

#### InsuranceType: // тип страховки (авто/здоровье/жилье)
 * InsuranceOffer[] offers // все предложения, которые доступны для этого типа
 * bool enabled // предоставляем ли мы сейчас эти услуги
 * int potential_customers_count // количество потенциальных покупателей
 * pair<int, int> insured_events_range // диапазон изменения количества страховых случаев каждый месяц

 * int total_customers_count // количество покупателей
 * int month_customers_count // количество новых покупателей за месяц
 * int total_revenue // общая выручка
 * int month_revenue // выручка за прошлый месяц
 * int total_payment_amount // общая сумма выплат за все время
 * int month_payment_amount // сумма выплат за последний месяц


#### Insurance:
 * InsuranceType[] insurances // все страховки, которые предоставляются компанией
 * double tax_percentage // размер налога гос-ву
 
 * int total_customers_count // количество покупателей
 * int month_customers_count // количество новых покупателей за месяц
 * int total_revenue // общая выручка
 * int month_revenue // выручка за прошлый месяц
 * int total_payment_amount // общая сумма выплат за все время
 int month_payment_amount // сумма выплат за последний месяц
