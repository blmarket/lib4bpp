<?php
  $pdo = new PDO('mysql:host=localhost;dbname=blmarket',
    'blmarket',
    'tnfqkrtm');
  $pdo->exec('SET CHARACTER SET utf8');

  $sql="select * from banklogs;";
  $stmt = $pdo->query($sql);

  foreach($stmt as $row)
  {
    print_r($row);
  }
?>
