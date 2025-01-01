SELECT DISTINCT c.conferenceName, c.year, c.importance
    FROM Conferences c
    WHERE EXISTS
    (
        SELECT s.conferenceName, s.wasAccepted
            FROM Submissions s
            WHERE s.conferenceName = c.conferenceName and s.year = c.year and s.wasAccepted = true
    )