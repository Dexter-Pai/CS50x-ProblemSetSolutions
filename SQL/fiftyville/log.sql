-- Keep a log of any SQL queries you execute as you solve the mystery.

--schemes
.schema

--tables
.table

--start with crime scene reports
SELECT * FROM crime_scene_reports;


--to get an idea of what we are dealing with
SELECT
    year, month, description
FROM
    crime_scene_reports;


--initiate the investigation
SELECT
    description, id
FROM
    crime_scene_reports
WHERE
    month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street' AND description LIKE '%CS50%';
--BREAKTHROUGH--
--theft took place at 10:15 a.m at bakery, 3 witnesses


--interviews
SELECT
    id, transcript
FROM
    interviews
WHERE
    month = 7 AND day = 28 AND year = 2021 AND name IN ('Ruth', 'Eugene', 'Raymond') AND transcript LIKE '%thief%';
--BREAKTHROUGH--
--within 10 minute of theft, thief get into a car
--before ariving at bakery, atm on leggett street, saw theif withdrawing money
--thief left bakery, called someone, talked for less than a minute
----in the call, they were planning to take earliest flight out of fiftyville tomorrow, month = 7 AND day = 29 AND year = 2021
----the other person purchased the flight ticket


--plates of interest, exit after the theft
SELECT
    license_plate
FROM
    bakery_security_logs
WHERE
    hour = 10 AND minute >15 AND minute <=25 AND month = 7 AND day = 28 AND year = 2021 AND activity = 'exit';


--investigate the atm
--to get an idea
SELECT * FROM atm_transactions LIMIT 10;
--investigate the day of theft
SELECT
    id, account_number, amount
FROM
    atm_transactions
WHERE
    year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';


--investigate phone calls
SELECT
    caller, receiver
FROM
    phone_calls
WHERE
    year = 2021 AND month = 7 AND day = 28 AND duration < 60;


--investigate banking information
SELECT
    person_id
FROM
    bank_accounts
WHERE
    account_number IN
    (
        SELECT
            account_number
        FROM
            atm_transactions
        WHERE
            year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    );


--search for the caller, according to phone call records, license plate and account info
SELECT
    id, name, passport_number
FROM
    people
WHERE
    phone_number IN
    (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            year = 2021 AND month = 7 AND day = 28 AND duration < 60
    )
    AND
    license_plate IN
    (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            hour = 10 AND minute >15 AND minute <=25 AND month = 7 AND day = 28 AND year = 2021 AND activity = 'exit'
    )
    AND
    id IN
    (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN
            (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
            )
    );
   -- AND
    --passport_number =
    --(
      --  SELECT
       --     passport_number
       -- FROM
        --    passengers
      --  WHERE
        --    flight_id = 36
    );


--investigate flights
SELECT
    id, origin_airport_id, destination_airport_id, MIN(hour), minute
FROM
    flights
WHERE
    month = 7 AND day = 29 AND year = 2021;
--BREAKTHROUGH--
--earliest flight revealed, with origin_airport_id = 8, destination_airport_id = 4
--destination airport is id = 4, full_name = 'LaGuardia Airport', city = 'New York City'

--airport id
SELECT
    id, full_name, city
FROM
    airports
WHERE
    id in (4);


--flights passengers
SELECT
    passport_number, seat
FROM
    passengers
WHERE
    flight_id = 36;


--search for Affiliate
SELECT
    id, name
FROM
    people
WHERE
    phone_number IN
    (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            year = 2021 AND month = 7 AND day = 28 AND duration < 60
    );

--Bruce is the cultprint, searching for affiliate
SELECT
    phone_number
FROM
    people
WHERE
    name = 'Bruce';

SELECT
    name
FROM
    people
WHERE
    phone_number =
    (
        SELECT
            receiver
        FROM
            phone_calls
        WHERE
            year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller =
            (
                SELECT
                    phone_number
                FROM
                    people
                WHERE
                    name = 'Bruce'
            )
    );
--BREAKTHROUGH--
--Robin!!