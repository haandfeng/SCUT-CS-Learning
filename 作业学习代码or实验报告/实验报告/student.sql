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

 Date: 07/07/2023 18:38:02
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

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

SET FOREIGN_KEY_CHECKS = 1;
