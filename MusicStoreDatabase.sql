-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jun 25, 2017 at 10:52 PM
-- Server version: 10.1.19-MariaDB
-- PHP Version: 7.0.13
-- Music Store Manangement System in C++ Design and Developed by CodeWithC.com

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cpp_musicstore_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `musicinfo_tb`
--

CREATE DATABASE MusicStore;

USE MusicStore;

CREATE TABLE musicinfo_tb (
  m_id int NOT NULL auto_increment PRIMARY KEY,
  m_category varchar(100) DEFAULT '0',
  m_type varchar(100) DEFAULT '0',
  m_name varchar(100) NOT NULL DEFAULT '0',
  m_artist varchar(100) NOT NULL DEFAULT '0',
  m_price INT NOT NULL DEFAULT 0,
  m_quantity INT NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `musicinfo_tb`
--

INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES
('Popular ', 'Jazz', "WU-TANG CLAN DON'T STOP", 'WU-TANG CLAN', 10, 14),
('Old', 'Remix', 'Ak Teri Yaad', 'Bilal Sayeed', 200, 0),
('Old', 'Pop', 'O Bondhu Lal Golapi', 'Shahabuddin', 100, 2),
('New', 'Chill', 'Chasma Kala', 'Nil Mitin', 20.22, 20);

-- --------------------------------------------------------

--
-- Table structure for table `solditem_tb`
--

CREATE TABLE solditem_tb (
  m_id int NOT NULL auto_increment PRIMARY KEY,
  m_category varchar(100) DEFAULT '0',
  m_type varchar(100) DEFAULT '0',
  m_name varchar(100) NOT NULL DEFAULT '0',
  m_artist varchar(100) NOT NULL DEFAULT '0',
  m_price int NOT NULL DEFAULT 0,
  m_quantity int NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `solditem_tb`
--

INSERT INTO solditem_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES
('Popular ', 'Jazz', "WU-TANG CLAN DON'T STOP", 'WU-TANG CLAN', 10, 1),
('Old', 'Pop', 'O Bondhu Lal Golapi', 'Shahabuddin', 100, 1);


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
