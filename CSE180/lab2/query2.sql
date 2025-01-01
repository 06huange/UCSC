SELECT a.authorID AS theAuthor, s.submissionTitle AS theSubmission , c.conferenceDate AS theConferenceDate
    FROM Authors a, Submissions s, Conferences c
    WHERE EXISTS
        (
            SELECT p.personID
                FROM Persons p
                WHERE p.personID = a.authorID and p.lastName LIKE 'K%'
        )
        and c.conferenceName = s.conferenceName 
        and c.year = s.year
        and s.submissionID = a.submissionID
        and s.datePublished IS NULL
        and c.conferenceDate >= '2020-01-09'