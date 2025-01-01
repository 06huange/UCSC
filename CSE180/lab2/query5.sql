SELECT  DISTINCT p.email, c.conferenceName, c.year, c.studentAttendeeCost
    FROM Persons p, Conferences c, Attendees a
    WHERE 
        a.attendeeID = p.personID AND
        p.affiliation LIKE 'Harvard University' AND
        EXISTS 
            (SELECT *
                FROM Reviewers r, Persons p
                WHERE
                    r.conferenceName = c.conferenceName AND
                    r.year = c.year AND
                    r.reviewerID = p.personID AND
                    p.lastName LIKE 'Huntington'
            )
        AND EXISTS 
            (SELECT *
                FROM Submissions s
                WHERE
                    s.conferenceName = c.conferenceName AND
                    s.year = c.year AND
                    s.dateAccepted = '2021-03-28' AND
                    s.numPages > 7
            )
        


