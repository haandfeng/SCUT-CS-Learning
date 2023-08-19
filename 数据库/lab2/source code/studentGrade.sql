/*
 Navicat Premium Data Transfer

 Source Server         : ex
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : studentGrade

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 07/07/2023 22:18:54
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course` (
  `cno` char(10) NOT NULL,
  `cname` varchar(50) NOT NULL,
  `tno` char(5) DEFAULT NULL,
  `credit` tinyint NOT NULL,
  `face_year` int NOT NULL,
  `canceled_year` tinyint DEFAULT NULL,
  PRIMARY KEY (`cno`),
  KEY `tno` (`tno`),
  CONSTRAINT `course_ibfk_1` FOREIGN KEY (`tno`) REFERENCES `teacher` (`tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of course
-- ----------------------------
BEGIN;
INSERT INTO `course` (`cno`, `cname`, `tno`, `credit`, `face_year`, `canceled_year`) VALUES ('c001001', 'Database', 't0001', 1, 2023, NULL);
INSERT INTO `course` (`cno`, `cname`, `tno`, `credit`, `face_year`, `canceled_year`) VALUES ('c001002', 'Calculus', 't0002', 2, 2024, NULL);
INSERT INTO `course` (`cno`, `cname`, `tno`, `credit`, `face_year`, `canceled_year`) VALUES ('c001003', 'Physical', 't0003', 1, 2023, NULL);
INSERT INTO `course` (`cno`, `cname`, `tno`, `credit`, `face_year`, `canceled_year`) VALUES ('c001004', 'English', 't0004', 2, 2023, NULL);
COMMIT;

-- ----------------------------
-- Table structure for sc
-- ----------------------------
DROP TABLE IF EXISTS `sc`;
CREATE TABLE `sc` (
  `id` int NOT NULL AUTO_INCREMENT,
  `sno` char(10) NOT NULL,
  `cno` char(7) NOT NULL,
  `tno` char(5) NOT NULL,
  `chosen_year` int DEFAULT NULL,
  `score` tinyint DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `sno` (`sno`),
  KEY `cno` (`cno`),
  KEY `tno` (`tno`),
  CONSTRAINT `sc_ibfk_1` FOREIGN KEY (`sno`) REFERENCES `student` (`sno`) ON DELETE CASCADE,
  CONSTRAINT `sc_ibfk_2` FOREIGN KEY (`cno`) REFERENCES `course` (`cno`),
  CONSTRAINT `sc_ibfk_3` FOREIGN KEY (`tno`) REFERENCES `teacher` (`tno`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of sc
-- ----------------------------
BEGIN;
INSERT INTO `sc` (`id`, `sno`, `cno`, `tno`, `chosen_year`, `score`) VALUES (1, 's201215121', 'c001001', 't0001', 2022, 100);
INSERT INTO `sc` (`id`, `sno`, `cno`, `tno`, `chosen_year`, `score`) VALUES (2, 's201215121', 'c001002', 't0002', 2022, 88);
INSERT INTO `sc` (`id`, `sno`, `cno`, `tno`, `chosen_year`, `score`) VALUES (3, 's201215121', 'c001003', 't0003', 2022, 55);
INSERT INTO `sc` (`id`, `sno`, `cno`, `tno`, `chosen_year`, `score`) VALUES (4, 's201215121', 'c001004', 't0004', 2022, 3);
INSERT INTO `sc` (`id`, `sno`, `cno`, `tno`, `chosen_year`, `score`) VALUES (5, 's201215122', 'c001001', 't0001', 2022, 100);
COMMIT;

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `sno` char(10) NOT NULL,
  `sname` varchar(20) NOT NULL,
  `ssex` char(2) DEFAULT '男',
  `entrance_age` tinyint NOT NULL,
  `entrance_year` int NOT NULL,
  `class` varchar(20) DEFAULT NULL,
  `password` varchar(50) DEFAULT '123456',
  PRIMARY KEY (`sno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of student
-- ----------------------------
BEGIN;
INSERT INTO `student` (`sno`, `sname`, `ssex`, `entrance_age`, `entrance_year`, `class`, `password`) VALUES ('s201215121', '李勇', '男', 18, 2022, '商务英语1班', '123456');
INSERT INTO `student` (`sno`, `sname`, `ssex`, `entrance_age`, `entrance_year`, `class`, `password`) VALUES ('s201215122', '刘晨', '女', 18, 2021, '软件工程1班', '123456');
INSERT INTO `student` (`sno`, `sname`, `ssex`, `entrance_age`, `entrance_year`, `class`, `password`) VALUES ('s201215123', '王敏', '男', 18, 2021, '软件工程1班', '123456');
INSERT INTO `student` (`sno`, `sname`, `ssex`, `entrance_age`, `entrance_year`, `class`, `password`) VALUES ('s201215124', '张立', '男', 18, 2020, '自动化1班', '123456');
COMMIT;

-- ----------------------------
-- Table structure for t_user
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user` (
  `id` int NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_user
-- ----------------------------
BEGIN;
INSERT INTO `t_user` (`id`, `username`, `password`) VALUES (1, 'user', 'user');
INSERT INTO `t_user` (`id`, `username`, `password`) VALUES (2, 'admin', 'admin');
INSERT INTO `t_user` (`id`, `username`, `password`) VALUES (3, 'cat', 'cat');
COMMIT;

-- ----------------------------
-- Table structure for teacher
-- ----------------------------
DROP TABLE IF EXISTS `teacher`;
CREATE TABLE `teacher` (
  `tno` char(5) NOT NULL,
  `tname` varchar(20) NOT NULL,
  `password` varchar(50) DEFAULT '123456',
  `teaching_course` varchar(50) NOT NULL,
  PRIMARY KEY (`tno`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of teacher
-- ----------------------------
BEGIN;
INSERT INTO `teacher` (`tno`, `tname`, `password`, `teaching_course`) VALUES ('t0001', '许巍', '123456', 'Database');
INSERT INTO `teacher` (`tno`, `tname`, `password`, `teaching_course`) VALUES ('t0002', '张三', '123456', 'Calculus');
INSERT INTO `teacher` (`tno`, `tname`, `password`, `teaching_course`) VALUES ('t0003', '李四', '123456', 'Physical');
INSERT INTO `teacher` (`tno`, `tname`, `password`, `teaching_course`) VALUES ('t0004', '王主任', '123456', 'English');
COMMIT;

-- ----------------------------
-- View structure for v_course
-- ----------------------------
DROP VIEW IF EXISTS `v_course`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_course` AS select `course`.`cno` AS `cno`,`course`.`cname` AS `cname`,`course`.`tno` AS `tno`,`course`.`credit` AS `credit`,`course`.`face_year` AS `face_year`,`course`.`canceled_year` AS `canceled_year`,`teacher`.`tname` AS `tname` from (`course` join `teacher`) where (`course`.`tno` = `teacher`.`tno`);

-- ----------------------------
-- View structure for v_sc
-- ----------------------------
DROP VIEW IF EXISTS `v_sc`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_sc` AS select `student`.`sno` AS `sno`,`student`.`sname` AS `sname`,`student`.`ssex` AS `ssex`,`student`.`entrance_age` AS `entrance_age`,`student`.`entrance_year` AS `entrance_year`,`student`.`class` AS `class`,`student`.`password` AS `password`,`course`.`cno` AS `cno`,`course`.`cname` AS `cname`,`course`.`tno` AS `tno`,`course`.`credit` AS `credit`,`course`.`face_year` AS `face_year`,`course`.`canceled_year` AS `canceled_year`,`teacher`.`tname` AS `tname`,`sc`.`chosen_year` AS `chosen_year`,`sc`.`score` AS `score` from (((`course` join `teacher`) join `student`) join `sc`) where ((`sc`.`tno` = `teacher`.`tno`) and (`student`.`sno` = `sc`.`sno`) and (`course`.`cno` = `sc`.`cno`));

-- ----------------------------
-- View structure for v_tea_course
-- ----------------------------
DROP VIEW IF EXISTS `v_tea_course`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_tea_course` AS select `teacher`.`tno` AS `tno`,`teacher`.`tname` AS `tname`,`teacher`.`password` AS `password`,group_concat(`course`.`cname` separator ',') AS `courses` from (`teacher` left join `course` on((`course`.`tno` = `teacher`.`tno`))) group by `teacher`.`tno`;

SET FOREIGN_KEY_CHECKS = 1;
