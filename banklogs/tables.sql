-- phpMyAdmin SQL Dump
-- version 2.11.8.1deb5+lenny6
-- http://www.phpmyadmin.net
--
-- 호스트: localhost
-- 처리한 시간: 10-11-11 04:07 
-- 서버 버전: 5.0.51
-- PHP 버전: 5.2.6-1+lenny9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- 데이터베이스: `banklog`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `banklogs`
--

CREATE TABLE IF NOT EXISTS `banklogs` (
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
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=89 ;

-- --------------------------------------------------------

--
-- 테이블 구조 `tags`
--

CREATE TABLE IF NOT EXISTS `tags` (
  `index` int(11) NOT NULL auto_increment,
  `cat` int(11) default NULL,
  `tag` varchar(100) character set utf8 collate utf8_unicode_ci NOT NULL,
  PRIMARY KEY  (`index`),
  UNIQUE KEY `tag` (`tag`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

-- --------------------------------------------------------

--
-- 테이블 구조 `tagselect`
--

CREATE TABLE IF NOT EXISTS `tagselect` (
  `index` int(11) NOT NULL auto_increment,
  `logindex` int(11) NOT NULL,
  `tagindex` int(11) NOT NULL,
  PRIMARY KEY  (`index`),
  KEY `logindex` (`logindex`,`tagindex`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

