<?php
  include 'db_include.php';
  $stmt = $pdo->prepare("INSERT INTO tags ( `tag` ) VALUES (:tag);");
  $result = $stmt->execute(array(':tag' => $_POST['tag']));
  if($result)
  {
    print("Tag ".$_POST['tag']." was added");
  }
  else
  {
    print("An Error occured");
  }
?>
