-- Log of SQL queries executed to solve the mystery.
SELECT *
FROM crime_scene_reports
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';

SELECT *
FROM interviews
WHERE year = 2021
  AND month = 7
  AND day = 28;

-- Within ten minutes of the theft thief left the place in car
SELECT people.name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute BETWEEN 15 AND 25

INTERSECT

-- The thief was seen withdrawing money from an ATM on Leggett Street earlier that morning.
SELECT people.name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw'

INTERSECT

-- After leaving the bakery, the thief made less than a minute call, mentioning plans to take the
-- earliest flight from Fiftyville the next day and asking the other person to purchase the ticket.
SELECT people.name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60

INTERSECT

SELECT people.name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = (
    SELECT flights.id
    FROM airports
    JOIN flights ON airports.id = flights.origin_airport_id
    WHERE airports.city = 'Fiftyville'
      AND year = 2021
      AND month = 7
      AND day = 29
      AND hour IN (
          SELECT MIN(hour)
          FROM flights
          WHERE origin_airport_id = airports.id
            AND year = 2021
            AND month = 7
            AND day = 29
      )
);

-- The person who received less than a minute call from thief Bruce is accomplice
SELECT people.name AS accomplice_name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller = (
    SELECT phone_number
    FROM people
    WHERE name = 'Bruce'
)
  AND phone_calls.year = 2021
  AND phone_calls.month = 7
  AND phone_calls.day = 28
  AND phone_calls.duration < 60;

-- City the thief escaped to is the destination airport city of the flight from Fiftyville city airport
SELECT city
FROM airports
WHERE airports.id = (
    SELECT flights.destination_airport_id
    FROM airports
    JOIN flights ON airports.id = flights.origin_airport_id
    WHERE airports.city = 'Fiftyville'
      AND year = 2021
      AND month = 7
      AND day = 29
      AND hour IN (
          SELECT MIN(hour)
          FROM flights
          WHERE origin_airport_id = airports.id
            AND year = 2021
            AND month = 7
            AND day = 29
      )
);
