ALTER TABLE Authors
ADD CONSTRAINT positive_authorPosition CHECK (authorPosition >= 0);

ALTER TABLE Conferences
ADD CONSTRAINT students_pay_less CHECK (studentAttendeeCost < regularAttendeeCost);

ALTER TABLE Submissions
ADD CONSTRAINT consistent_acceptance CHECK ((wasAccepted IS NULL AND dateAccepted IS NULL) OR (wasAccepted IS NOT NULL));