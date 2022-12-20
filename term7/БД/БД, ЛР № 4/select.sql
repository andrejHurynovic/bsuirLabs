-- 1.	Имена, фамилии, отчества, официальные названия стран гражданства и адреса регистрации всех физических лиц с сортировкой в порядке возрастания по ISO коду и фамилии.
SELECT individual.first_name,  individual.middle_name, individual.last_name, citizenship.official_name, individual.registration_address 
FROM individual 
    JOIN citizenship ON citizenship.id = individual.citizenship_id 
    ORDER BY citizenship.id, individual.last_name;

-- 2.	Имена, фамилии, отчества, официальные названия стран гражданства всех физических лиц, не являющихся гражданами Беларуси, с сортировкой в порядке возрастания по ISO коду и фамилии.
SELECT individual.first_name,  individual.middle_name, individual.last_name, citizenship.official_name 
FROM individual 
    JOIN citizenship ON individual.citizenship_id = citizenship.id 
    WHERE citizenship_id <> 'BY' 
    ORDER BY citizenship.id, individual.last_name;

-- 3.	Имена, фамилии, отчества всех физических лиц, являющихся гражданами США, с сортировкой в порядке возрастания по фамилии.
SELECT individual.first_name,  individual.middle_name, individual.last_name 
FROM individual 
    JOIN citizenship ON individual.citizenship_id = citizenship.id 
    WHERE citizenship_id = 'US' 
    ORDER BY individual.last_name;

-- 4.	УНП, названия и адреса регистрации всех юридических лиц отсортированные в порядке возрастания по названию юридического лица.
SELECT * FROM entity ORDER BY entity.official_name; 

-- 5.	УНП, названия и адреса регистрации всех юридических лиц с адресом регистрации в городе Минске, отсортированные в порядке возрастания по названию юридического лица.
SELECT * 
FROM entity 
    WHERE entity.registration_address LIKE 'г.Минск%' 
    ORDER BY entity.official_name;

-- 6.	УНП, названия адреса регистрации всех юридических лиц и номера счетов, отсортированные в порядке возрастания по названию юридического лица.
SELECT entity.prn, entity.official_name, entity.registration_address, account.iban 
FROM entity 
    JOIN account ON account.entity_PRN = entity.prn 
    ORDER BY entity.official_name; 

-- 7.	Идентификатор, название типа, дата, счёт получателя, сумма и валюта транзакции по номеру счёта.
SELECT transaction.id, transaction_type.transaction_type_name, transaction.transaction_date, transaction.recipients_account, transaction.amount, transaction.currency_code 
FROM transaction 
    JOIN transaction_type ON transaction_type.code = transaction.transaction_type_code 
    WHERE transaction.account_iban = 'BY34AMNG1011104US20100190001';

-- 8.	Идентификатор, название типа, дата, счёт получателя, сумма и валюта транзакции для всех карт.
SELECT card.card_number, transaction.id, transaction_type.transaction_type_name, transaction.transaction_date, transaction.recipients_account, transaction.amount, transaction.currency_code 
FROM card 
    JOIN transaction ON card.card_number = transaction.card_number 
    JOIN transaction_type ON transaction_type.code = transaction.transaction_type_code
    WHERE transaction.card_number IS NOT NULL 
    ORDER BY card_number;

-- 9.	Идентификатор, название типа, дата, счёт получателя, сумма и валюта транзакций определённого типа.
SELECT transaction.id, transaction_type.transaction_type_name, transaction.transaction_date, transaction.recipients_account, transaction.amount, transaction.currency_code 
FROM transaction 
    JOIN transaction_type ON transaction_type.code = transaction.transaction_type_code 
    WHERE transaction.transaction_type_code = 4; -- Refund

-- 10.	Номер карты, окончание срока действия, CVV-код, платёжная система и её класс обслуживания по номеру счёта.
SELECT card.card_number, to_char(card.expiration_date, 'Month YYYY') AS "expiration_date", card.cvv, card.payment_system, card.service_class
FROM account_card
    JOIN card ON card.card_number = account_card.card_number
    WHERE account_card.account_iban = 'BY34AMNG1011104US20030190001';

-- 11.	Номер, окончание срока действия, CVV-код, платёжная система и её класс обслуживания для карт, информация о лимитах у карт у которых есть лимиты.
SELECT card.card_number, to_char(card.expiration_date, 'Month YYYY') AS "expiration_date", card.cvv, card.payment_system, card.service_class, bank_limit.limit_start_date, bank_limit.limit_end_date, bank_limit.cash_amount, bank_limit.cash_count, bank_limit.non_cash_amount, bank_limit.non_cash_count, bank_limit.maximal_cash_amount, bank_limit.maximal_cash_count, bank_limit.maximal_non_cash_amount, bank_limit.maximal_non_cash_count
FROM bank_limit
    JOIN card ON bank_limit.card_number = card.card_number;

-- 12.	Номер, окончание срока действия, CVV-код, платёжная система и её класс обслуживания для карт, информация о лимитах у конкретной карты.
SELECT card.card_number, to_char(card.expiration_date, 'Month YYYY') AS "expiration_date", card.cvv, card.payment_system, card.service_class, bank_limit.limit_start_date, bank_limit.limit_end_date, bank_limit.cash_amount, bank_limit.cash_count, bank_limit.non_cash_amount, bank_limit.non_cash_count, bank_limit.maximal_cash_amount, bank_limit.maximal_cash_count, bank_limit.maximal_non_cash_amount, bank_limit.maximal_non_cash_count
FROM bank_limit
    JOIN card ON bank_limit.card_number = card.card_number
    WHERE card.card_number = '4024007166727312';

-- 13.	Информация о счёте и лимитах у счетов, которые имеют лимиты.
SELECT card.card_number, to_char(card.expiration_date, 'Month YYYY') AS "expiration_date", card.cvv, card.payment_system, card.service_class, bank_limit.limit_start_date, bank_limit.limit_end_date, bank_limit.cash_amount, bank_limit.cash_count, bank_limit.non_cash_amount, bank_limit.non_cash_count, bank_limit.maximal_cash_amount, bank_limit.maximal_cash_count, bank_limit.maximal_non_cash_amount, bank_limit.maximal_non_cash_count
FROM bank_limit
    JOIN card ON bank_limit.card_number = card.card_number;
