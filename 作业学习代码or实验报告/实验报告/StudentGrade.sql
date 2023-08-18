create DATABASE studentGrade;

use studentGrade;


CREATE TABLE student  (
  sno char(10) not  NULL ,
  sname varchar(20) not  NULL,
  ssex char(2) default '男',
  entrance_age tinyint not  NULL,
  entrance_year int not  NULL,
  class varchar(20) ,
	password varchar(50) default '123456',
  PRIMARY KEY (sno)
);

INSERT INTO student (sno,sname,ssex,entrance_age,entrance_year,class) VALUES
('s201215121','李勇','男',18,2022,'商务英语1班'),
('s201215122','刘晨','女',18,2021,'软件工程1班'),
('s201215123','王敏','女',18,2021,'软件工程1班'),
('s201215124','张立','男',18,2020,'自动化1班');

CREATE TABLE teacher (
  tno char(5) not  NULL ,
  tname varchar(20) not  NULL,
	password varchar(50) default '123456',
  PRIMARY KEY (tno)
);

INSERT INTO teacher (tno,tname) VALUES
('t0001','许巍'),
('t0002','张三'),
('t0003','李四'),
('t0004','王主任');

CREATE TABLE course  (
  cno char(10) not  NULL ,
  cname varchar(50) not  NULL,
  tno char(5) ,
  credit tinyint not  NULL,
	face_year int not  NULL,
  canceled_year tinyint,
  PRIMARY KEY (cno),
 FOREIGN KEY (tno) REFERENCES teacher (tno)
);

INSERT INTO course VALUES
('c001001','数据库','t0001',1,2018,null),
('c001002','数学','t0002',2,2018,null),
('c001003','物理化学','t0003',1,2018,null),
('c001004','大学英语','t0004',2,2023,null);


CREATE TABLE sc  (
 id int not  NULL PRIMARY KEY AUTO_INCREMENT,
 sno char(10) not  NULL ,
  cno char(7) not  NULL ,
  tno char(5) not  NULL ,
  chosen_year int,
  score tinyint,
  FOREIGN KEY(sno)REFERENCES student(sno) on DELETE CASCADE,
  FOREIGN KEY(cno)REFERENCES course(cno),
  FOREIGN KEY(tno)REFERENCES teacher(tno)
);

INSERT INTO sc (sno,cno,tno,chosen_year,score) VALUES
('s201215121','c001001','t0001',2022,100),
('s201215121','c001002','t0002',2022,88),
('s201215121','c001003','t0003',2022,55),
('s201215121','c001004','t0004',2022,3),
('s201215122','c001001','t0001',2022,100);




CREATE TABLE t_user  (
  id int not  NULL ,
  username varchar(50) not  NULL,
  password varchar(50) not  NULL,
  PRIMARY KEY (id)
);

INSERT INTO t_user VALUES (1, 'user', 'user'),(2, 'admin', 'admin'),(3, 'cat', 'cat');

create view v_course
as
select course.*,teacher.tname from course,teacher
where course.tno = teacher.tno ;

create view v_tea_course
as
select teacher.*,GROUP_CONCAT(course.cname) as 'courses' from teacher
left JOIN course on course.tno = teacher.tno
GROUP BY teacher.tno ;

create view v_sc
as
select student.*,course.*,teacher.tname,sc.chosen_year,sc.score from course,teacher,student,sc
where sc.tno = teacher.tno and student.sno = sc.sno and course.cno = sc.cno ;
