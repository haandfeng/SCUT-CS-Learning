SELECT s.ID, s.Name, AVG(sc.Score) AS AverageScore
FROM Student s
JOIN StudentCourse sc ON s.ID = sc.ID
GROUP BY s.ID, s.Name;
