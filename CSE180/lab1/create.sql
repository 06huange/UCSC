--Lab1
--khuang53

--*TESTING* DROP AND CREATE NEW SCHEMA
--DROP SCHEMA Lab1 CASCADE;
--CREATE SCHEMA Lab1;

--Create Tables
CREATE TABLE Persons(
    personID INT PRIMARY KEY,
    lastName VARCHAR(30),
    firstName VARCHAR(30),
    email VARCHAR(60),
    affiliation VARCHAR(60),
    isStudent BOOLEAN
);

CREATE TABLE Conferences(
    conferenceName VARCHAR(60),
    year INT,
    conferenceDate DATE,
    regularAttendeeCost NUMERIC(6, 2),
    studentAttendeeCost NUMERIC(6, 2),
    submissionDueDate DATE,
    reviewDueDate DATE,
    importance CHAR(1),
    PRIMARY KEY(conferenceName, year)
);

CREATE TABLE Submissions(
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    numPages INT,
    submitDate DATE,
    wasAccepted BOOLEAN,
    PRIMARY KEY(conferenceName, year, submissionID),
    FOREIGN KEY(conferenceName, year) REFERENCES Conferences
);

CREATE TABLE Authors(
    authorID INT,
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    authorPosition INT,
    PRIMARY KEY(authorID, conferenceName, year, submissionID),
    FOREIGN KEY(authorID) REFERENCES Persons(personID),
    FOREIGN KEY(conferenceName, year) REFERENCES Conferences
);

CREATE TABLE Reviewers(
    reviewerID INT,
    conferenceName VARCHAR(60),
    year INT,
    reliability CHAR(1),
    PRIMARY KEY(reviewerID, conferenceName, year),
    FOREIGN KEY(reviewerID) REFERENCES Persons(personID),
    FOREIGN KEY(conferenceName, year) REFERENCES Conferences
);

CREATE TABLE Reviews(
    reviewerID INT,
    conferenceName VARCHAR(60),
    year INT,
    submissionID INT,
    reviewDate DATE,
    rating INT,
    PRIMARY KEY(reviewerID, conferenceName, year, submissionID),
    FOREIGN KEY(reviewerID, conferenceName, year) REFERENCES Reviewers,
    FOREIGN KEY(conferenceName, year, submissionID) REFERENCES Submissions
);

CREATE TABLE Attendees(
    attendeeID INT,
    conferenceName VARCHAR(60),
    year INT,
    PRIMARY KEY(attendeeID, conferenceName, year),
    FOREIGN KEY(attendeeID) REFERENCES Persons(personID),
    FOREIGN KEY(conferenceName, year) REFERENCES Conferences

);