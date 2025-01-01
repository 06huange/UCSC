/* create.sql for Lab3 based on our Lab2 solution, except without UNIQUE and NOT NULL constraints.
   Also, both Foreign Key constraints on the Reviews table are omitted, and a new table,
   SubmissionChanges (conferenceName, year, submissionID, dateAccepted), has been added.
*/

--DROP SCHEMA CASCADE and CREATE SCHEMA statements for Lab3

DROP SCHEMA Lab3 CASCADE;
CREATE SCHEMA Lab3;


-- Create the tables


--Persons(personID, lastName, firstName, email, affiliation, isStudent)
CREATE TABLE Persons(
    personID INT PRIMARY KEY,
    lastName VARCHAR(30),
    firstName VARCHAR(30),
    email VARCHAR(60),
    affiliation VARCHAR(60),
    isStudent BOOLEAN
);
-- Okay to have PRIMARY KEY (personID) as a schema element, instead of next to attribute.


-- Conferences(conferenceName, year, conferenceDate, regularAttendeeCost, studentAttendeeCost,
--             submissionDueDate, reviewDueDate, importance)
CREATE TABLE Conferences(
    conferenceName VARCHAR(60),
    year INT,
    conferenceDate DATE,
    regularAttendeeCost NUMERIC(6,2),
    studentAttendeeCost NUMERIC(6,2),
    submissionDueDate DATE,
    reviewDueDate DATE,
    importance CHAR(1),
    PRIMARY KEY (conferenceName, year)
);
-- Okay to have DECIMAL(6,2) instead of NUMERIC(6,2).


-- Submissions(conferenceName, year, submissionID, numPages, submitDate, wasAccepted)
CREATE TABLE Submissions(
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    numPages INT,
    submitDate DATE,
    wasAccepted BOOLEAN,
    submissionTitle VARCHAR(60),
    dateAccepted DATE,
    datePublished DATE,
    PRIMARY KEY (conferenceName, year, submissionID),
    FOREIGN KEY (conferenceName, year) REFERENCES Conferences(conferenceName, year)
);
-- Okay to  have just REFERENCES Conferences, since attributes are the same.


-- Authors(authorID, conferenceName, year, submissionID, authorPosition)
CREATE TABLE Authors(
    authorID INT,
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    authorPosition INT,
    PRIMARY KEY (authorID, conferenceName, year, submissionID),
    FOREIGN KEY (authorID) REFERENCES Persons(personID),
    FOREIGN KEY (conferenceName, year) REFERENCES Conferences(conferenceName, year)
);
-- Okay to have REFERENCES Persons(personID) next to the authorID attribute.
-- Okay to  have just REFERENCES Conferences, since attributes are the same.


-- Reviewers(reviewerID, conferenceName, year, reliability)
CREATE TABLE Reviewers(
    reviewerID INT,
    conferenceName VARCHAR(60),
    year INT,
    reliability CHAR(1),
    PRIMARY KEY (reviewerID, conferenceName, year),
    FOREIGN KEY (reviewerID) REFERENCES Persons(personID),
    FOREIGN KEY (conferenceName, year) REFERENCES Conferences(conferenceName, year)
);
-- Okay to have REFERENCES Persons(personID) next to the reviewerID attribute.
-- Okay to  have just REFERENCES Conferences, since attributes are the same.


-- Reviews(reviewerID, conferenceName, year, submissionID, reviewDate, rating)
CREATE TABLE Reviews(
    reviewerID INT,
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    reviewDate DATE,
    rating INT,
    PRIMARY KEY (reviewerID, conferenceName, year, submissionID)
);
-- The Foreign Key constraints that Lab1 had for Reviews have been omitted.


-- Attendees(attendeeID, conferenceName, year)
CREATE TABLE Attendees(
    attendeeID INT,
    conferenceName VARCHAR(60),
    year INT,
    PRIMARY KEY (attendeeID, conferenceName, year),
    FOREIGN KEY (attendeeID) REFERENCES Persons(personID),
    FOREIGN KEY (conferenceName, year) REFERENCES Conferences(conferenceName, year)
);
-- Okay to have REFERENCES Persons(personID) next to the attendeeID attribute.
-- Okay to  have just REFERENCES Conferences, since attributes are the same.


-- SubmissionChanges(conferenceName, year, submissionID, dateAccepted)
CREATE TABLE SubmissionChanges(
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    dateAccepted DATE,
    PRIMARY KEY (conferenceName, year, submissionID),
    FOREIGN KEY (conferenceName, year) REFERENCES Conferences(conferenceName, year)
);
-- Okay to  have just REFERENCES Conferences, since attributes are the same.
