-- MySQL dump 10.13  Distrib 5.5.24, for Win32 (x86)
--
-- Host: localhost    Database: mg
-- ------------------------------------------------------
-- Server version	5.5.24-log

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
-- Table structure for table `actions`
--

DROP TABLE IF EXISTS `actions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `actions` (
  `aid` varchar(255) NOT NULL DEFAULT '0' COMMENT 'Primary Key: Unique actions ID.',
  `type` varchar(32) NOT NULL DEFAULT '' COMMENT 'The object that that action acts on (node, user, comment, system or custom types.)',
  `callback` varchar(255) NOT NULL DEFAULT '' COMMENT 'The callback function that executes when the action runs.',
  `parameters` longblob NOT NULL COMMENT 'Parameters to be passed to the callback function.',
  `label` varchar(255) NOT NULL DEFAULT '0' COMMENT 'Label of the action.',
  PRIMARY KEY (`aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores action information.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `actions`
--

LOCK TABLES `actions` WRITE;
/*!40000 ALTER TABLE `actions` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `actions` VALUES ('comment_publish_action','comment','comment_publish_action','','Publish comment'),('comment_save_action','comment','comment_save_action','','Save comment'),('comment_unpublish_action','comment','comment_unpublish_action','','Unpublish comment'),('node_make_sticky_action','node','node_make_sticky_action','','Make content sticky'),('node_make_unsticky_action','node','node_make_unsticky_action','','Make content unsticky'),('node_promote_action','node','node_promote_action','','Promote content to front page'),('node_publish_action','node','node_publish_action','','Publish content'),('node_save_action','node','node_save_action','','Save content'),('node_unpromote_action','node','node_unpromote_action','','Remove content from front page'),('node_unpublish_action','node','node_unpublish_action','','Unpublish content'),('og_membership_delete_action','og_membership','og_membership_delete_action','','Remove from group'),('pathauto_node_update_action','node','pathauto_node_update_action','','Update node alias'),('pathauto_taxonomy_term_update_action','taxonomy_term','pathauto_taxonomy_term_update_action','','Update taxonomy term alias'),('pathauto_user_update_action','user','pathauto_user_update_action','','Update user alias'),('system_block_ip_action','user','system_block_ip_action','','Ban IP address of current user'),('user_block_user_action','user','user_block_user_action','','Block current user'),('views_bulk_operations_archive_action','file','views_bulk_operations_archive_action','','Create an archive of selected files'),('views_bulk_operations_argument_selector_action','entity','views_bulk_operations_argument_selector_action','','Pass ids as arguments to a page'),('views_bulk_operations_delete_item','entity','views_bulk_operations_delete_item','','Delete item'),('views_bulk_operations_delete_revision','entity','views_bulk_operations_delete_revision','','Delete revision'),('views_bulk_operations_modify_action','entity','views_bulk_operations_modify_action','','Modify entity values');
/*!40000 ALTER TABLE `actions` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `authmap`
--

DROP TABLE IF EXISTS `authmap`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `authmap` (
  `aid` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Primary Key: Unique authmap ID.',
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT 'User’s users.uid.',
  `authname` varchar(128) NOT NULL DEFAULT '' COMMENT 'Unique authentication name.',
  `module` varchar(128) NOT NULL DEFAULT '' COMMENT 'Module which is controlling the authentication.',
  PRIMARY KEY (`aid`),
  UNIQUE KEY `authname` (`authname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores distributed authentication mapping.';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authmap`
--

LOCK TABLES `authmap` WRITE;
/*!40000 ALTER TABLE `authmap` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `authmap` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `batch`
--

DROP TABLE IF EXISTS `batch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `batch` (
  `bid` int(10) unsigned NOT NULL COMMENT 'Primary Key: Unique batch ID.',
  `token` varchar(64) NOT NULL COMMENT 'A string token generated against the current user’s session id and the batch id, used to ensure that only the user who submitted the batch can effectively access it.',
  `timestamp` int(11) NOT NULL COMMENT 'A Unix timestamp indicating when this batch was submitted for processing. Stale batches are purged at cron time.',
  `batch` longblob COMMENT 'A serialized array containing the processing data for the batch.',
  PRIMARY KEY (`bid`),
  KEY `token` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Stores details about batches (processes that run in...';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `batch`
--

LOCK TABLES `batch` WRITE;
/*!40000 ALTER TABLE `batch` DISABLE KEYS */;
set autocommit=0;
/*!40000 ALTER TABLE `batch` ENABLE KEYS */;
UNLOCK TABLES;
commit;

--
-- Table structure for table `block`
--

DROP TABLE IF EXISTS `block`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `block` (
  `bid` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Primary Key: Unique block ID.',
  `module` varchar(64) NOT NULL DEFAULT '' COMMENT 'The module from which the block originates; for example, ’user’ for the Who’s Online block, and ’block’ for any custom blocks.',
  `delta` varchar(32) NOT NULL DEFAULT '0' COMMENT 'Unique ID for block within a module.',
  `theme` varchar(64) NOT NULL DEFAULT '' COMMENT 'The theme under which the block settings apply.',
  `status` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'Block enabled status. (1 = enabled, 0 = disabled)',
  `weight` int(11) NOT NULL DEFAULT '0' COMMENT 'Block weight within region.',
  `region` varchar(64) NOT NULL DEFAULT '' COMMENT 'Theme region within which the block is set.',
  `custom` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'Flag to indicate how users may control visibility of the block. (0 = Users cannot control, 1 = On by default, but can be hidden, 2 = Hidden by default, but can be shown)',
  `visibility` tinyint(4) NOT NULL DEFAULT '0' COMMENT 'Flag to indicate how to show blocks on pages. (0 = Show on all pages except listed pages, 1 = Show only on listed pages, 2 = Use custom PHP code to determine visibility)',
  `pages` text NOT NULL COMMENT 'Contents of the "Pages" block; contains either a list of paths on which to include/exclude the block or PHP code, depending on "visibility" setting.',
  `title` varchar(64) NOT NULL DEFAULT '' COMMENT 'Custom title for the block. (Empty string will use block default title, <none> will remove the title, text will cause block to use specified title.)',
  `cache` tinyint(4) NOT NULL DEFAULT '1' COMMENT 'Binary flag to indicate block cache mode. (-2: Custom cache, -1: Do not cache, 1: Cache per role, 2: Cache per user, 4: Cache per page, 8: Block cache global) See DRUPAL_CACHE_* constants in ../includes/common.inc for more detailed information.',
  PRIMARY KEY (`bid`),
  UNIQUE KEY `tmd` (`theme`,`module`,`delta`),
  KEY `list` (`theme`,`status`,`region`,`weight`,`module`)
) ENGINE=InnoDB AUTO_INCREMENT=184 DEFAULT CHARSET=utf8 COMMENT='Stores block settings, such as region and visibility...';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `block`
--

LOCK TABLES `block` WRITE;
/*!40000 ALTER TABLE `block` DISABLE KEYS */;
set autocommit=0;
INSERT INTO `block` VALUES (1,'system','main','bartik',1,0,'content',0,0,'','',-1),(2,'search','form','bartik',1,-1,'sidebar_first',0,0,'','',-1),(3,'node','recent','seven',1,10,'dashboard_main',0,0,'','',-1),(4,'user','login','bartik',1,0,'sidebar_first',0,0,'','',-1),(5,'system','navigation','bartik',1,0,'sidebar_first',0,0,'','',-1),(6,'system','powered-by','bartik',1,10,'footer',0,0,'','',-1),(7,'system','help','bartik',1,0,'help',0,0,'','',-1),(8,'system','main','seven',1,0,'content',0,0,'','',-1),(9,'system','help','seven',1,0,'help',0,0,'','',-1),(10,'user','login','seven',1,10,'content',0,0,'','',-1),(11,'user','new','seven',1,0,'dashboard_sidebar',0,0,'','',-1),(12,'search','form','seven',1,-10,'dashboard_sidebar',0,0,'','',-1),(13,'comment','recent','bartik',0,0,'-1',0,0,'','',1),(14,'node','syndicate','bartik',0,0,'-1',0,0,'','',-1),(15,'node','recent','bartik',0,0,'-1',0,0,'','',1),(16,'shortcut','shortcuts','bartik',0,0,'-1',0,0,'','',-1),(17,'system','management','bartik',0,0,'-1',0,0,'','',-1),(18,'system','user-menu','bartik',0,0,'-1',0,0,'','',-1),(19,'system','main-menu','bartik',0,0,'-1',0,0,'','',-1),(20,'user','new','bartik',0,0,'-1',0,0,'','',1),(21,'user','online','bartik',0,0,'-1',0,0,'','',-1),(22,'comment','recent','seven',1,0,'dashboard_inactive',0,0,'','',1),(23,'node','syndicate','seven',0,0,'-1',0,0,'','',-1),(24,'shortcut','shortcuts','seven',0,0,'-1',0,0,'','',-1),(25,'system','powered-by','seven',0,10,'-1',0,0,'','',-1),(26,'system','navigation','seven',0,0,'-1',0,0,'','',-1),(27,'system','management','seven',0,0,'-1',0,0,'','',-1),(28,'system','user-menu','seven',0,0,'-1',0,0,'','',-1),(29,'system','main-menu','seven',0,0,'-1',0,0,'','',-1),(30,'user','online','seven',1,0,'dashboard_inactive',0,0,'','',-1),(31,'boost','status','bartik',0,0,'-1',0,0,'','',-1),(32,'gmap_location','0','bartik',0,0,'-1',0,0,'','',-1),(33,'gmap_location','1','bartik',0,0,'-1',0,0,'','',-1),(34,'locale','language','bartik',0,0,'-1',0,0,'','',-1),(35,'locale','language_content','bartik',0,0,'-1',0,0,'','',-1),(36,'menu','features','bartik',0,0,'-1',0,0,'','',-1),(42,'print','print-links','bartik',0,0,'-1',0,0,'','',4),(43,'print','print-top','bartik',0,0,'-1',0,0,'','',8),(44,'sharethis','sharethis_block','bartik',0,0,'-1',0,0,'','',1),(45,'simplenews','0','bartik',0,0,'-1',0,0,'','',1),(46,'simplenews','1','bartik',0,0,'-1',0,0,'','',-1),(47,'tagclouds','2','bartik',0,0,'-1',0,0,'','',8),(48,'tagclouds','1','bartik',0,0,'-1',0,0,'','',8),(49,'print_mail','print_mail-top','bartik',0,0,'-1',0,0,'','',8),(50,'print_pdf','print_pdf-top','bartik',0,0,'-1',0,0,'','',8),(51,'views','og_members-block_1','bartik',0,0,'-1',0,0,'','',-1),(52,'boost','status','seven',0,0,'-1',0,0,'','',-1),(53,'gmap_location','0','seven',0,0,'-1',0,0,'','',-1),(54,'gmap_location','1','seven',0,0,'-1',0,0,'','',-1),(55,'locale','language','seven',0,0,'-1',0,0,'','',-1),(56,'locale','language_content','seven',0,0,'-1',0,0,'','',-1),(57,'menu','features','seven',0,0,'-1',0,0,'','',-1),(63,'print','print-links','seven',0,0,'-1',0,0,'','',4),(64,'print','print-top','seven',0,0,'-1',0,0,'','',8),(65,'sharethis','sharethis_block','seven',0,0,'-1',0,0,'','',1),(66,'simplenews','0','seven',0,0,'-1',0,0,'','',1),(67,'simplenews','1','seven',0,0,'-1',0,0,'','',-1),(68,'tagclouds','2','seven',0,0,'-1',0,0,'','',8),(69,'tagclouds','1','seven',0,0,'-1',0,0,'','',8),(70,'print_mail','print_mail-top','seven',0,0,'-1',0,0,'','',8),(71,'print_pdf','print_pdf-top','seven',0,0,'-1',0,0,'','',8),(72,'views','og_members-block_1','seven',0,0,'-1',0,0,'','',-1),(73,'boost','status','minorite',0,0,'-1',0,0,'','',-1),(74,'comment','recent','minorite',0,0,'-1',0,0,'','',1),(75,'gmap_location','0','minorite',0,0,'-1',0,0,'','',-1),(76,'gmap_location','1','minorite',0,0,'-1',0,0,'','',-1),(77,'locale','language','minorite',0,0,'-1',0,0,'','',-1),(78,'locale','language_content','minorite',0,0,'-1',0,0,'','',-1),(79,'menu','features','minorite',0,0,'-1',0,0,'','',-1),(85,'node','recent','minorite',0,0,'-1',0,0,'','',1),(86,'node','syndicate','minorite',0,0,'-1',0,0,'','',-1),(87,'print','print-links','minorite',0,0,'-1',0,0,'','',4),(88,'print','print-top','minorite',0,0,'-1',0,0,'','',8),(89,'print_mail','print_mail-top','minorite',0,0,'-1',0,0,'','',8),(90,'print_pdf','print_pdf-top','minorite',0,0,'-1',0,0,'','',8),(91,'search','form','minorite',0,-1,'-1',0,0,'','',-1),(92,'sharethis','sharethis_block','minorite',0,0,'-1',0,0,'','',1),(93,'shortcut','shortcuts','minorite',0,0,'-1',0,0,'','',-1),(94,'simplenews','0','minorite',0,0,'-1',0,0,'','',1),(95,'simplenews','1','minorite',0,0,'-1',0,0,'','',-1),(96,'system','help','minorite',0,0,'-1',0,0,'','',-1),(97,'system','main','minorite',1,0,'content',0,0,'','',-1),(98,'system','main-menu','minorite',0,0,'-1',0,0,'','',-1),(99,'system','management','minorite',0,0,'-1',0,0,'','',-1),(100,'system','navigation','minorite',0,0,'-1',0,0,'','',-1),(101,'system','powered-by','minorite',0,10,'-1',0,0,'','',-1),(102,'system','user-menu','minorite',1,0,'top',0,0,'','',-1),(103,'tagclouds','1','minorite',0,0,'-1',0,0,'','',8),(104,'tagclouds','2','minorite',0,0,'-1',0,0,'','',8),(105,'user','login','minorite',0,0,'-1',0,0,'','',-1),(106,'user','new','minorite',0,0,'-1',0,0,'','',1),(107,'user','online','minorite',0,0,'-1',0,0,'','',-1),(108,'views','og_members-block_1','minorite',0,0,'-1',0,0,'','',-1),(130,'menu','footer','bartik',0,0,'-1',0,0,'','',-1),(131,'menu','game','bartik',0,0,'-1',0,0,'','',-1),(132,'menu','headlines','bartik',0,0,'-1',0,0,'','',-1),(133,'menu','life','bartik',0,0,'-1',0,0,'','',-1),(134,'menu','my-company','bartik',0,0,'-1',0,0,'','',-1),(135,'menu','my-team','bartik',0,0,'-1',0,0,'','',-1),(136,'menu','voyage','bartik',0,0,'-1',0,0,'','',-1),(137,'menu','footer','minorite',1,-10,'bottom',0,0,'','',-1),(138,'menu','game','minorite',0,0,'-1',0,0,'','',-1),(139,'menu','headlines','minorite',0,0,'-1',0,0,'','',-1),(140,'menu','life','minorite',0,0,'-1',0,0,'','',-1),(141,'menu','my-company','minorite',0,0,'-1',0,0,'','',-1),(142,'menu','my-team','minorite',0,0,'-1',0,0,'','',-1),(143,'menu','voyage','minorite',0,0,'-1',0,0,'','',-1),(144,'menu','footer','seven',0,0,'-1',0,0,'','',-1),(145,'menu','game','seven',0,0,'-1',0,0,'','',-1),(146,'menu','headlines','seven',0,0,'-1',0,0,'','',-1),(147,'menu','life','seven',0,0,'-1',0,0,'','',-1),(148,'menu','my-company','seven',0,0,'-1',0,0,'','',-1),(149,'menu','my-team','seven',0,0,'-1',0,0,'','',-1),(150,'menu','voyage','seven',0,0,'-1',0,0,'','',-1),(163,'mini_menu','primary','bartik',0,0,'-1',0,0,'','',1),(164,'mini_menu','secondary','bartik',0,0,'-1',0,0,'','',1),(165,'mini_menu','navigation','bartik',0,0,'-1',0,0,'','',1),(166,'mini_search','header','bartik',0,0,'-1',0,0,'','',8),(167,'mini_search','bottom','bartik',0,0,'-1',0,0,'','',8),(168,'mini_user','legal_terms','bartik',0,0,'-1',0,0,'','Read and accept the terms and conditions',8),(169,'mini_menu','primary','minorite',1,-57,'navigation',0,0,'','',1),(170,'mini_menu','secondary','minorite',1,0,'left',0,0,'','',1),(171,'mini_menu','navigation','minorite',1,0,'footer',0,0,'','',1),(172,'mini_search','header','minorite',1,0,'header',0,0,'','',8),(173,'mini_search','bottom','minorite',1,0,'bottom',0,0,'','',8),(174,'mini_user','legal_terms','minorite',0,0,'-1',0,0,'','Read and accept the terms and conditions',8),(175,'mini_menu','primary','seven',0,0,'-1',0,0,'','',1),(176,'mini_menu','secondary','seven',0,0,'-1',0,0,'','',1),(177,'mini_menu','navigation','seven',0,0,'-1',0,0,'','',1),(178,'mini_search','header','seven',0,0,'-1',0,0,'','',8),(179,'mini_search','bottom','seven',0,0,'-1',0,0,'','',8),(180,'mini_user','legal_terms','seven',0,0,'-1',0,0,'','Read and accept the terms and conditions',8),(181,'mini_carrousel','carrousel','bartik',0,0,'-1',0,0,'','',1),(182,'mini_carrousel','carrousel','minorite',0,0,'-1',0,0,'','',1),(183,'mini_carrousel','carrousel','seven',0,0,'-1',0,0,'','',1);
/*!40000 ALTER TABLE `block` ENABLE KEYS */;
UNLOCK TABLES;
commit;
