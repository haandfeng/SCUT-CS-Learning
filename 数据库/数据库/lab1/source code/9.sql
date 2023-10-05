SELECT s.ID, s.Name, c.CourseName, sc.Score
FROM Student s
JOIN StudentCourse sc ON s.ID = sc.ID
JOIN Course c ON sc.CourseID = c.CourseID
ORDER BY s.ID DESC;
