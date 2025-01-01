BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;
UPDATE Submissions s
SET dateAccepted = sc.dateAccepted, wasAccepted = true, submitDate = NULL
FROM SubmissionChanges sc
WHERE s.conferenceName = sc.conferenceName
					AND s.year = sc.year
					AND s.submissionID = sc.submissionID;

INSERT INTO Submissions(conferenceName, year, submissionID, numPages, submitDate, wasAccepted,
submissionTitle, dateAccepted, datePublished)
SELECT sc.conferenceName, sc.year, sc.submissionID, NULL, CURRENT_DATE, TRUE, NULL, sc.dateAccepted, NULL
FROM SubmissionChanges sc
WHERE NOT EXISTS (	SELECT * 
					FROM Submissions s
					WHERE s.conferenceName = sc.conferenceName
					AND s.year = sc.year
					AND s.submissionID = sc.submissionID);
COMMIT TRANSACTION;
