SELECT s.ID, s.Name, COUNT(*) AS CourseCount
FROM Student s
JOIN StudentCourse sc ON s.ID = sc.ID
GROUP BY s.ID, s.Name;
