SELECT DISTINCT hrc.year, COUNT(*)
FROM HuntingtonReviewerConferences hrc, LongConferenceSubmissionsCount lcsc
WHERE hrc.hCount = 1 AND
hrc.conferenceName = lcsc.conferenceName AND
lcsc.longCount >= 4 AND
hrc.year = lcsc.year
GROUP BY hrc.year;

/* View Query
 year | count 
------+-------
 2020 |     2
 2022 |     1
(2 rows)
*/

DELETE FROM Reviewers r
WHERE r.reviewerID = 3488 
AND r.conferenceName LIKE 'Santa Cruz Law Review'
AND r.year = 2021;

DELETE FROM Reviewers r
WHERE r.reviewerID = 3396
AND r.conferenceName LIKE 'American Conference of Law'
AND r.year = 2020;

/*
 year | count 
------+-------
 2020 |     1
 2021 |     1
 2022 |     1
(3 rows)
*/