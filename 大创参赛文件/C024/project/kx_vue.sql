/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 50726
 Source Host           : localhost:3306
 Source Schema         : kx_vue

 Target Server Type    : MySQL
 Target Server Version : 50726
 File Encoding         : 65001

 Date: 06/03/2023 09:18:04
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for kx_table
-- ----------------------------
DROP TABLE IF EXISTS `kx_table`;
CREATE TABLE `kx_table`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `longitude` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `latitude` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 12 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of kx_table
-- ----------------------------
INSERT INTO `kx_table` VALUES (5, '114.5193', '38.04300');
INSERT INTO `kx_table` VALUES (11, '114.48868028429', '38.045245496962');

SET FOREIGN_KEY_CHECKS = 1;
