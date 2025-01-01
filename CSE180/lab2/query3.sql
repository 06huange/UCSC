SELECT DISTINCT p.lastName, p.firstName
    FROM Persons p, Reviewers rvw, Reviews rv
    WHERE EXISTS
    (
        SELECT *
            FROM Reviewers rvw1
            WHERE rvw1.reviewerID = rvw.reviewerID AND
            (rvw1.conferenceName <> rvw.conferenceName OR rvw1.year <> rvw.year)
    )
    AND rvw.reviewerID = p.personID
    ORDER BY p.lastName DESC, p.firstName DESC;