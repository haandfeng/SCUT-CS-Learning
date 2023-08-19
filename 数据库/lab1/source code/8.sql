SELECT s.ID, s.Name, c.CourseName, sc.Score
FROM StudentCourse sc
JOIN Student s ON s.ID = sc.ID
JOIN Course c ON c.CourseID = sc.CourseID;

