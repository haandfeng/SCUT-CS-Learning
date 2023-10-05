SELECT c.CourseID, c.CourseName, COUNT(DISTINCT sc.ID) AS StudentCount
FROM Course c
JOIN StudentCourse sc ON c.CourseID = sc.CourseID
GROUP BY c.CourseID, c.CourseName;
