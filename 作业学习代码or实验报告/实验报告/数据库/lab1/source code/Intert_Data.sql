INSERT INTO Student (ID, Name, Age, Department)
VALUES
    ('00001', 'ZhangSan', 20, 'Computer Science'),
    ('00002', 'LiSi', 19, 'Computer Science'),
    ('00003', 'WangWu', 21, 'Computer Science');
		
INSERT INTO Course (CourseID, CourseName, CourseBefore)
VALUES
    ('C1', 'Introduction to Computer', NULL),
    ('C2', 'PASCAL Programming Language', 'C1'),
    ('C3', 'Data Structure', 'C2');
		
INSERT INTO StudentCourse (ID, CourseID, Score)
VALUES
    ('00001', 'C1', 95),
    ('00001', 'C2', 80),
    ('00001', 'C3', 84),
    ('00002', 'C1', 80),
    ('00002', 'C2', 85),
    ('00003', 'C1', 78),
    ('00003', 'C3', 70);
