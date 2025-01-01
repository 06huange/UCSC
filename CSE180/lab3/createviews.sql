--view 1
CREATE VIEW HuntingtonReviewerConferences (conferenceName, year, hCount) AS
SELECT c.conferenceName, c.year, COUNT(*)
FROM Conferences c, Reviewers r, Persons p
WHERE
r.conferenceName = c.conferenceName AND
                    r.year = c.year AND
                    r.reviewerID = p.personID AND
                    p.lastName LIKE 'Huntington'
GROUP BY c.conferenceName, c.year
HAVING COUNT(*) > 0;

CREATE VIEW LongConferenceSubmissionsCount (conferenceName, year, longCount) AS
SELECT c.conferenceName, c.year, COUNT(*)
FROM Conferences c, Submissions s
WHERE
        s.conferenceName = c.conferenceName AND
        s.year = c.year AND
        s.numPages > 7
GROUP BY c.conferenceName, c.year