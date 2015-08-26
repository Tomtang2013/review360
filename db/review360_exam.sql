-- ----------------------------
-- Table structure for `review360_exam`
-- ----------------------------
DROP TABLE IF EXISTS `review360_exam`;
CREATE TABLE `review360_exam` (
  `exam_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `exam_name` varchar(200) NOT NULL,
  `exam_key` varchar(20) DEFAULT NULL,
  `exam_type` varchar(50) DEFAULT NULL,
  `nid` int(11) DEFAULT NULL,
  `create_date` int(11) DEFAULT NULL,
  `update_date` int(11) DEFAULT NULL,
  PRIMARY KEY (`exam_id`)
) ENGINE=MyISAM AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `review360_survey`
-- ----------------------------
DROP TABLE IF EXISTS `review360_survey`;
CREATE TABLE `review360_survey` (
  `survey_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `survey_name` varchar(200) NOT NULL,
  `survey_key` varchar(10) DEFAULT NULL,
  `nid` int(11) DEFAULT NULL,
  `survey_nids` varchar(200) DEFAULT NULL,
  `survey_nid_name` varchar(200) DEFAULT NULL,
  `survey_status` int(10) DEFAULT '0',
  `survey_user_num` int(11) DEFAULT '0',
  `start_date` int(11) DEFAULT NULL,
  `end_date` int(11) DEFAULT NULL,
  `is_generate_key` int(1) DEFAULT '0',
  `create_date` int(11) DEFAULT NULL,
  `update_date` int(11) DEFAULT NULL,
  PRIMARY KEY (`survey_id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `review360_survey_user`
-- ----------------------------
DROP TABLE IF EXISTS `review360_survey_user`;
CREATE TABLE `review360_survey_user` (
  `su_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `survey_id` int(11) NOT NULL,
  `survey_user_key` varchar(200) NOT NULL,
  `u_email` varchar(200) DEFAULT NULL,
  `u_name` varchar(200) DEFAULT NULL,
  `nid` int(11) DEFAULT NULL,
  `create_date` int(11) DEFAULT NULL,
  `update_date` int(11) DEFAULT NULL,
  `u_sex` varchar(200) DEFAULT NULL,
  `u_p_number` varchar(200) DEFAULT NULL,
  `u_bachelor` varchar(200) DEFAULT NULL,
  `u_specialty` varchar(200) DEFAULT NULL,
  `u_university` varchar(200) DEFAULT NULL,
  `u_experience` int(11) DEFAULT NULL,
  `u_engaged` varchar(200) DEFAULT NULL,
  `u_company_name` varchar(200) DEFAULT NULL,
  `u_department` varchar(200) DEFAULT NULL,
  `u_work_nature` int(11) DEFAULT NULL,
  PRIMARY KEY (`su_id`)
) ENGINE=MyISAM AUTO_INCREMENT=557 DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `review360_user`
-- ----------------------------
DROP TABLE IF EXISTS `review360_user`;
CREATE TABLE `review360_user` (
  `user_id` int(11) NOT NULL AUTO_INCREMENT,
  `group_id` int(11) NOT NULL,
  `user_name` varchar(200) NOT NULL,
  `user_email` varchar(200) DEFAULT NULL,
  `createdate` int(11) DEFAULT NULL,
  `updatedate` int(11) DEFAULT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1939 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of review360_user
-- ----------------------------

-- ----------------------------
-- Table structure for `review360_user_group`
-- ----------------------------
DROP TABLE IF EXISTS `review360_user_group`;
CREATE TABLE `review360_user_group` (
  `group_id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `group_name` varchar(200) DEFAULT NULL,
  `createdate` int(11) DEFAULT NULL,
  `updatedate` int(11) DEFAULT NULL,
  PRIMARY KEY (`group_id`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;


