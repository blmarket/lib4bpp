<?php
  include 'db_include.php';

  if( ! isset($_POST["logid"]) || ! isset($_POST["tagid"]) || ! isset($_POST["tagged"]))
  {
    print("Invalid input data");
    return;
  }

  $logid = $_POST["logid"];
  $tagid = $_POST["tagid"];
  $tagged = $_POST["tagged"];

  if($tagged == 1)
  {
    $stmt = $pdo->prepare("DELETE FROM tagselect WHERE `logindex`=:logindex AND `tagindex`=:tagindex;");
    $result = $stmt->execute(array(':logindex' => $logid, ':tagindex' => $tagid));
    if($result)
    {
      print("Done");
    }
    else
    {
      print("Something wrong happened");
    }
  }
  else
  {
    $stmt = $pdo->prepare("INSERT INTO tagselect ( `logindex`, `tagindex` ) VALUES ( :logindex , :tagindex );");
    $result = $stmt->execute(array(':logindex' => $logid, ':tagindex' => $tagid));
    if($result)
    {
      print("Tagged successfully");
    }
    else
    {
      print("Something wrong happened");
    }
  }
?>
