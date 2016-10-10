-- Update Version JC-DB
-- By Bodeguero for JadeCore.

/*
Navicat MySQL Data Transfer

Source Server         : DeathCore
Source Server Version : 50624
Source Host           : 127.0.0.1:3306
Source Database       : world5481

Target Server Type    : MYSQL
Target Server Version : 50624
File Encoding         : 65001

Date: 2016-10-10 00:05:37
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `version`
-- ----------------------------
DROP TABLE IF EXISTS `version`;
CREATE TABLE `version` (
  `core_version` varchar(120) NOT NULL DEFAULT '' COMMENT 'Core revision dumped at startup.',
  `core_revision` varchar(120) DEFAULT NULL,
  `db_version` varchar(120) DEFAULT NULL COMMENT 'Version of world DB.',
  `cache_id` int(11) DEFAULT '0',
  PRIMARY KEY (`core_version`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Version Notes';

-- ----------------------------
-- Records of version
-- ----------------------------
INSERT INTO `version` VALUES ('JadeCore rev. rev.7 2015-05-05 00:00:00 +0000 (Archived branch) (Win64, Release)', 'rev.1', 'JCDB 548.07', '07');
