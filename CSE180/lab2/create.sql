--Lab2
--khuang53

--*TESTING* DROP AND CREATE NEW SCHEMA
--DROP SCHEMA Lab2 CASCADE;
--CREATE SCHEMA Lab2;

--Create Tables
CREATE TABLE Persons(
    personID INT PRIMARY KEY,
    lastName VARCHAR(30),
    firstName VARCHAR(30),
    email VARCHAR(60) NOT NULL,
    affiliation VARCHAR(60),
    isStudent BOOLEAN,
    UNIQUE(email),
    UNIQUE(firstName, lastName)
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
    submitDate DATE NOT NULL,
    wasAccepted BOOLEAN,
    submissionTitle VARCHAR(60),
    dateAccepted DATE,
    datePublished DATE,
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
    FOREIGN KEY(conferenceName, year) REFERENCES Conferences,
    UNIQUE(conferenceName, year, submissionID, authorPosition)
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
    reviewDate DATE NOT NULL,
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