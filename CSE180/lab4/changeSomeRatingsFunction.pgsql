CREATE OR REPLACE FUNCTION
changeSomeRatingsFunction(theReviewerID INTEGER, maxRatingChanges INTEGER)
RETURNS INTEGER AS $$


    DECLARE
    	numChanged		INTEGER;	  /* Number actually fired, the value returned */
        rID INTEGER;
        rel CHAR(1);

    DECLARE changeRating CURSOR FOR
        SELECT r.submissionID
        FROM Reviews r, Reviewers rvw 
        WHERE r.reviewerID = rvw.reviewerID AND 
        r.conferenceName = rvw.conferenceName AND 
        r.year = rvw.year AND
        r.reviewerID = theReviewerID
        ORDER BY r.reviewDate DESC;
        
    DECLARE reliab CURSOR FOR
        SELECT rvw.reliability
        FROM Reviewers rvw
        WHERE rvw.reviewerID = theReviewerID;
    BEGIN

	-- Input Validation
	IF maxRatingChanges < 0 THEN
	    RETURN -1;
	    END IF;
    IF NOT EXISTS (SELECT rvw.reviewerID FROM Reviewers rvw WHERE rvw.reviewerID = theReviewerID) THEN
        RETURN -2;
        END IF;

        numChanged := 0;

        OPEN changeRating;
        OPEN reliab;
        FETCH reliab INTO rel;

        LOOP

            FETCH changeRating INTO rID;
            -- Exit if there are no more records for changeRating,
            -- or when we already have performed maxFired firings.
            EXIT WHEN NOT FOUND OR numChanged >= maxRatingChanges OR rel = 'L';

            --Skip to next iteration if rating does not need to be changed based on reliability and rating
            IF (rel = 'H') OR (rel = 'M') THEN
                continue when (SELECT r.rating FROM Reviews r WHERE r.submissionID = rID AND r.reviewerID = theReviewerID) = 5;
            ELSEIF (rel IS NULL) THEN
                continue when (SELECT r.rating FROM Reviews r WHERE r.submissionID = rID AND r.reviewerID = theReviewerID) = 0;
            END IF;

            --Case when Reliability is high
            UPDATE Reviews
            SET rating = 
                CASE WHEN rating = 5 THEN 5
                WHEN rating = 4 THEN rating + 1
                WHEN rating <= 3 THEN rating + 2
                END
            WHERE submissionID = rID AND
            rel = 'H';

            --Case when Reliability is medium
            UPDATE Reviews
            SET rating = 
                CASE WHEN rating = 5 THEN 5
                WHEN rating <= 4 THEN rating + 1
                END
            WHERE submissionID = rID AND
            rel = 'M';

            --Case when Reliability is NULL
            UPDATE Reviews
            SET rating = 
                CASE WHEN rating = 0 THEN 0
                WHEN rating > 0 THEN rating - 1
                END
            WHERE submissionID = rID AND
            rel IS NULL;

            numChanged := numChanged + 1;

        END LOOP;
        CLOSE changeRating;

	RETURN numChanged;

    END

$$ LANGUAGE plpgsql;
