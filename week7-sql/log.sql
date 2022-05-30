-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT
    *
FROM
    crime_scene_reports
WHERE
    day = 28
    AND month = 7
    AND year = 2021
    AND street = "Humphrey Street";

-- crime_scene_id = 295
-- hour and minute 10:15am

SELECT
    *
FROM
    interviews
WHERE
    transcript LIKE "%bakery%";

-- Ruth (161): search for the security footage
-- for cars that letf 10 minutes after the theft

-- Eugene (162): search for the ATM log in the same
-- day. Leggett Street ATM.

-- Raymond (163): search for call history which
-- were shorter than a minute, search for the
-- earlist flight the next day. The person on the
-- phone should buy the tickets.

SELECT
    people.name
FROM
    people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE
    day = 28
    AND month = 7
    AND year = 2021
    AND hour = 10
    AND minute <= 25
    AND activity = "exit"
ORDER BY
    people.name;

-- Suspects:
-- Barry
-- Bruce
-- Diana
-- Iman
-- Kelsey
-- Luca
-- Sofia
-- Vanessa

SELECT
    people.name
FROM
    people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE
    atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021
    AND atm_transactions.atm_location = "Leggett Street"
    AND atm_transactions.transaction_type = "withdraw"
ORDER BY
    people.name;

-- Suspects: (Delete those who aren't in the last queries)
-- Bruce
-- Diana
-- Iman
-- Luca

SELECT
    people.name, phone_calls.id
FROM
    people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE
    phone_calls.day = 28
    AND phone_calls.month = 7
    AND phone_calls.year = 2021
    AND phone_calls.duration < 60
ORDER BY
    people.name;

SELECT
    people.name, phone_calls.id
FROM
    people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE
    phone_calls.id  = 233
    OR  phone_calls.id  = 255;

-- Suspects: (Delete those who aren't in the last queries)
-- 233 Bruce to Robin
-- 255 Diana to Phillip

SELECT
    people.name, flights.id
FROM
    people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON flights.origin_airport_id = airports.id
WHERE
    flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
    AND people.name IN ('Bruce', 'Robin', 'Diana', 'Phillip')
    AND airports.city = 'Fiftyville'
ORDER BY
    flights.hour, flights.minute
LIMIT
    1;

-- Bruce and Robin, Flight Id 36

SELECT
    airports.city
FROM
    airports JOIN flights ON airports.id = flights.destination_airport_id
WHERE
    flights.id = 36;

-- New York City
