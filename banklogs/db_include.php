<?php
  $pdo = new PDO('mysql:host=localhost;dbname=banklog',
    'banklog',
    '111111',
    array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8"));
?>
