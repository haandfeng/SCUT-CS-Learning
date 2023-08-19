CREATE TABLE Student (
    ID VARCHAR(20),
    Name VARCHAR(10),
    Age INT,
    Department VARCHAR(30)
);
CREATE TABLE Course (
    CourseID VARCHAR(15),
    CourseName VARCHAR(30),
    CourseBefore VARCHAR(15)
);
CREATE TABLE StudentCourse (
    ID VARCHAR(20),
    CourseID VARCHAR(15),
    Score DECIMAL(5,2)
);
