--Test for Foreign Key
INSERT INTO Reviews(1234,'test1',2021);

INSERT INTO Submission ('test2',2021,4321);

--Test for General Constraint
--Constraint 1
UPDATE Authors
SET authorPosition = 2;

UPDATE Authors
SET authorPosition = -1;

--Constraint 2
UPDATE Conferences
SET studentAttendeeCost = 5, regularAttendeeCost = 7;

UPDATE Conferences
SET studentAttendeeCost = 5, regularAttendeeCost = 3;

--Constraint 3
UPDATE Submissions
SET wasAccepted = NULL, dateAccepted = NULL;

UPDATE Submissions
SET wasAccepted = NULL, dateAccepted = DATE '2021-05-10';