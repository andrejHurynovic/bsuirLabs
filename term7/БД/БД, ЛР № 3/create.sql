;
\c postgres;
DROP DATABASE bank;

CREATE DATABASE bank;
\c bank

CREATE TABLE citizenship (
	id CHAR(2) NOT NULL PRIMARY KEY,
		CONSTRAINT is_ISO3166 CHECK (id ~ '[A-Z]{2}'),
	official_name VARCHAR(128) NOT NULL
);

CREATE TABLE individual (
	document_number VARCHAR(32) NOT NULL PRIMARY KEY,
	first_name VARCHAR(32) NOT NULL,
	middle_name VARCHAR(32),
	last_name VARCHAR(32) NOT NULL,
	date_of_birth DATE NOT NULL,
	registration_address VARCHAR(128) NOT NULL,
	citizenship_id CHAR(2) NOT NULL REFERENCES citizenship (id) ON DELETE RESTRICT
);

CREATE TABLE entity (
    PRN CHAR(9) NOT NULL PRIMARY KEY,
	CONSTRAINT is_PRN CHECK (PRN ~ '[0-9]{9}'),
    official_name VARCHAR(512),
    registration_address VARCHAR(128) NOT NULL
);

CREATE TABLE account (
    IBAN CHAR(28) NOT NULL PRIMARY KEY,
	constraint is_IBAN CHECK (IBAN ~ '^([A-Z]{2}[ ''+''\\''+''-]?[0-9]{2})(?=(?:[ ''+''\\''+''-]?[A-Z0-9]){9,30}$)((?:[ ''+''\\''+''-]?[A-Z0-9]{3,5}){2,7})([ ''+''\\''+''-]?[A-Z0-9]{1,3})?$'),
    opening_date DATE NOT NULL,
    currency_code VARCHAR(3) NOT NULL,
		CONSTRAINT ISO4217 CHECK (currency_code ~ '[A-Z]{3}'),
    balance MONEY NOT NULL,
    individual_document_number VARCHAR(32) REFERENCES individual (document_number) ON DELETE CASCADE,
	entity_PRN CHAR(9) REFERENCES entity (PRN) ON DELETE CASCADE,
		CONSTRAINT haveConnection CHECK (individual_document_number IS NOT NULL AND entity_PRN IS NOT NULL),
		CONSTRAINT onlyOneConnection CHECK ((individual_document_number IS NOT NULL) != (entity_PRN IS NOT NULL))
);

CREATE TABLE card (
    card_number CHAR(16) NOT NULL PRIMARY KEY,
		CONSTRAINT is_card_number CHECK (card_number ~ '[0-9]{16}'),
    CVV CHAR(3) NOT NULL,
		CONSTRAINT is_CVV_code CHECK (CVV ~ '[0-9]{3}'),
    expiration_date DATE NOT NULL,
    payment_system VARCHAR(16) NOT NULL,
    service_class VARCHAR(16) NOT NULL
);

CREATE TABLE account_card (
	account_IBAN CHAR(28) NOT NULL REFERENCES account (IBAN) ON DELETE CASCADE,
		CONSTRAINT is_IBAN CHECK (account_IBAN ~ '^([A-Z]{2}[ ''+''\\''+''-]?[0-9]{2})(?=(?:[ ''+''\\''+''-]?[A-Z0-9]){9,30}$)((?:[ ''+''\\''+''-]?[A-Z0-9]{3,5}){2,7})([ ''+''\\''+''-]?[A-Z0-9]{1,3})?$'),
	card_number CHAR(16) NOT NULL REFERENCES card (card_number) ON DELETE CASCADE,
		CONSTRAINT is_card_number CHECK (card_number ~ '[0-9]{16}'),
	PRIMARY KEY (account_IBAN, card_number)
);

CREATE TABLE bank_limit (
    id SERIAL PRIMARY KEY,
    limit_start_date DATE NOT NULL,
    limit_end_date DATE NOT NULL,
    cash_amount MONEY,
    cash_count SMALLINT,
    non_cash_amount MONEY,
    non_cash_count SMALLINT,
	maximal_cash_amount MONEY,
    maximal_cash_count SMALLINT,
    maximal_non_cash_amount MONEY,
    maximal_non_cash_count SMALLINT,
	account_IBAN CHAR(28) REFERENCES account (IBAN) ON DELETE CASCADE, 
		CONSTRAINT is_IBAN CHECK (account_IBAN ~ '^([A-Z]{2}[ ''+''\\''+''-]?[0-9]{2})(?=(?:[ ''+''\\''+''-]?[A-Z0-9]){9,30}$)((?:[ ''+''\\''+''-]?[A-Z0-9]{3,5}){2,7})([ ''+''\\''+''-]?[A-Z0-9]{1,3})?$') ,
	card_number CHAR(16) REFERENCES card (card_number) ON DELETE CASCADE
		CONSTRAINT is_card_number CHECK (card_number ~ '[0-9]{16}'),
		
		CONSTRAINT haveConnection CHECK (account_IBAN IS NOT NULL AND card_number IS NOT NULL),
		CONSTRAINT onlyOneConnection CHECK ((account_IBAN IS NOT NULL) != (card_number IS NOT NULL))
);


CREATE TABLE transaction_type (
    code SERIAL PRIMARY KEY,
    transaction_type_name VARCHAR(32)
);

CREATE TABLE transaction (
    id SERIAL PRIMARY KEY,
    transaction_date TIMESTAMP NOT NULL,
    recipients_account VARCHAR(28) NOT NULL,
		constraint is_IBAN CHECK (recipients_account ~ '^([A-Z]{2}[ ''+''\\''+''-]?[0-9]{2})(?=(?:[ ''+''\\''+''-]?[A-Z0-9]){9,30}$)((?:[ ''+''\\''+''-]?[A-Z0-9]{3,5}){2,7})([ ''+''\\''+''-]?[A-Z0-9]{1,3})?$'),
    amount MONEY NOT NULL,
    currency_code CHAR(3) NOT NULL,
		CONSTRAINT ISO4217 CHECK (currency_code ~ '[A-Z]{3}')
);

ALTER TABLE account
	DROP CONSTRAINT haveConnection,
	ADD CONSTRAINT haveConnection CHECK (individual_document_number IS NOT NULL OR entity_PRN IS NOT NULL);

ALTER TABLE bank_limit
	DROP CONSTRAINT haveConnection,
	ADD CONSTRAINT haveConnection CHECK (account_IBAN IS NOT NULL OR card_number IS NOT NULL);

ALTER TABLE transaction 
	ADD COLUMN account_IBAN CHAR(28) REFERENCES account (IBAN) ON DELETE CASCADE,
		ADD CONSTRAINT is_Account_IBAN CHECK (account_IBAN ~ '^([A-Z]{2}[ ''+''\\''+''-]?[0-9]{2})(?=(?:[ ''+''\\''+''-]?[A-Z0-9]){9,30}$)((?:[ ''+''\\''+''-]?[A-Z0-9]{3,5}){2,7})([ ''+''\\''+''-]?[A-Z0-9]{1,3})?$'),
	ADD COLUMN card_number CHAR(16) REFERENCES card (card_number) ON DELETE CASCADE,
		ADD CONSTRAINT is_card_number CHECK (card_number ~ '[0-9]{16}'),
		ADD CONSTRAINT haveConnection CHECK (account_IBAN IS NOT NULL OR card_number IS NOT NULL),
		ADD CONSTRAINT onlyOneConnection CHECK ((account_IBAN IS NOT NULL) != (card_number IS NOT NULL)),
	ADD COLUMN transaction_type_code INT NOT NULL REFERENCES transaction_type (code) ON DELETE RESTRICT
;
