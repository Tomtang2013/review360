/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50621
Source Host           : localhost:3306
Source Database       : review360

Target Server Type    : MYSQL
Target Server Version : 50621
File Encoding         : 65001

Date: 2015-10-10 18:33:31
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `review360_survey_exam_result`
-- ----------------------------
DROP TABLE IF EXISTS `review360_survey_exam_result`;
CREATE TABLE `review360_survey_exam_result` (
  `sr_id` int(11) NOT NULL AUTO_INCREMENT,
  `sid` int(11) DEFAULT NULL,
  `se_id` int(11) DEFAULT NULL,
  `nid` int(11) DEFAULT NULL,
  `quadrant` varchar(200) DEFAULT NULL,
  `d` int(11) DEFAULT NULL,
  `i` int(11) DEFAULT NULL,
  `s` int(11) DEFAULT NULL,
  `c` int(11) DEFAULT NULL,
  `d_value` int(11) DEFAULT NULL,
  `i_value` int(11) DEFAULT NULL,
  `s_value` int(11) DEFAULT NULL,
  `c_value` int(11) DEFAULT NULL,
  `create_date` int(11) DEFAULT NULL,
  `update_date` int(11) DEFAULT NULL,
  PRIMARY KEY (`sr_id`)
) ENGINE=MyISAM AUTO_INCREMENT=405 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of review360_survey_exam_result
-- ----------------------------
INSERT INTO `review360_survey_exam_result` VALUES ('401', '12', '81', '106', 'in_working_me', '10', '8', '2', '4', '47', '47', '47', '48', '1444450931', '1444450931');
INSERT INTO `review360_survey_exam_result` VALUES ('402', '12', '81', '106', 'innate', '-2', '-2', '1', '3', '50', '50', '50', '50', '1444450931', '1444450931');
INSERT INTO `review360_survey_exam_result` VALUES ('403', '12', '81', '106', 'other', '8', '6', '3', '7', '48', '48', '48', '49', '1444450931', '1444450931');
INSERT INTO `review360_survey_exam_result` VALUES ('404', '12', '81', '106', 'stress', '12', '10', '1', '1', '5', '5', '5', '5', '1444450931', '1444450931');
