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

 Date: 07/07/2023 18:48:19
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

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

SET FOREIGN_KEY_CHECKS = 1;
