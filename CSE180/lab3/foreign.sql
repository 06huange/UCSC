ALTER TABLE Reviews
ADD CONSTRAINT fk_1 FOREIGN KEY (reviewerID, conferenceName, year)
REFERENCES Reviewers(reviewerID, conferenceName, year)
	ON UPDATE CASCADE
	ON DELETE SET NULL;

ALTER TABLE Reviews
ADD CONSTRAINT fk_2 FOREIGN KEY (conferenceName, year, submissionID)
REFERENCES Submissions(conferenceName, year, submissionID)
	ON UPDATE NO ACTION
	ON DELETE CASCADE;