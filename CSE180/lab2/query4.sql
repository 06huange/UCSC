SELECT c.conferenceName AS name, c.year, c.regularAttendeeCost as theCost, c.importance AS theImportance
    FROM Conferences c
    WHERE 
        c.regularAttendeeCost IS NOT NULL AND 
        c.importance IS NOT NULL AND
        regularAttendeeCost IN (SELECT min(regularAttendeeCost) FROM Conferences)

        



