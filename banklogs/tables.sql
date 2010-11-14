-- MySQL dump 10.11
--
-- Host: localhost    Database: banklog
-- ------------------------------------------------------
-- Server version	5.0.51a-24+lenny4

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `banklogs`
--

DROP TABLE IF EXISTS `banklogs`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `banklogs` (
  `index` int(11) NOT NULL auto_increment,
  `date` datetime NOT NULL,
  `dateindex` int(11) NOT NULL default '0',
  `category` varchar(20) character set utf8 collate utf8_unicode_ci NOT NULL,
  `name` varchar(20) character set utf8 collate utf8_unicode_ci NOT NULL,
  `expense` int(11) NOT NULL,
  `income` int(11) NOT NULL,
  `bank` varchar(20) character set utf8 collate utf8_unicode_ci NOT NULL,
  `memo` varchar(100) character set utf8 collate utf8_unicode_ci NOT NULL,
  `cat` int(11) default NULL,
  PRIMARY KEY  (`index`),
  UNIQUE KEY `date` (`date`,`dateindex`)
) ENGINE=MyISAM AUTO_INCREMENT=89 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `tags`
--

DROP TABLE IF EXISTS `tags`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `tags` (
  `index` int(11) NOT NULL auto_increment,
  `tag` varchar(100) character set utf8 collate utf8_unicode_ci NOT NULL,
  PRIMARY KEY  (`index`),
  UNIQUE KEY `tag` (`tag`)
) ENGINE=MyISAM AUTO_INCREMENT=18 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `tagselect`
--

DROP TABLE IF EXISTS `tagselect`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `tagselect` (
  `index` int(11) NOT NULL auto_increment,
  `logindex` int(11) NOT NULL,
  `tagindex` int(11) NOT NULL,
  PRIMARY KEY  (`index`),
  KEY `logindex` (`logindex`,`tagindex`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;
SET character_set_client = @saved_cs_client;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2010-11-10 18:50:31
