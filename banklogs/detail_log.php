<?php
  include 'db_include.php';

  $sql = "SELECT * FROM `banklogs` WHERE `index`=:index";
  $stmt = $pdo->prepare($sql);
  $stmt->bindParam(':index', $_GET["id"]);
  $stmt->execute();

  $row = $stmt->fetch();
?>

<!DOCTYPE html>
<html>
<head>
        <title>Detail of banklogs</title>
        <link rel="stylesheet" href="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.css" />
        <link rel="stylesheet" href="test.css" />
        <script src="http://code.jquery.com/jquery-1.4.3.js"></script>
        <script src="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.js"></script>
</head> 
<body> 
<div data-role="page" id="initial">
  <div data-role="header">
    <h1><?=$row["date"]?></h1>
  </div>

  <div data-role="content">
    <div class="ui-bar ui-bar-a" data-inset="true">
      Summary
    </div>
    <div class="ui-bar ui-bar-d" data-inset="true">
      <table>
        <tr>
          <th scope="row" width=80px>거래일시</th>
          <td><?=$row["date"]?></td>
        </tr>
        <tr>
          <th scope="row">개요</th>
          <td><?=$row["category"]?></td>
        </tr>
        <tr>
          <th scope="row">취급점</th>
          <td><?=$row["bank"]?></td>
        </tr>
        <tr>
          <th scope="row">기재내용</th>
          <td><?=$row["name"]?></td>
        </tr>
        <tr>
          <th scope="row">입금액</th>
          <td><?=$row["income"]?></td>
        </tr>
        <tr>
          <th scope="row">출금액</th>
          <td><?=$row["expense"]?></td>
        </tr>
        <tr>
          <th scope="row">메모</th>
          <td><?=$row["memo"]?></td>
        </tr>
        <?
          if($row["cat"] != NULL)
          {
            ?>
            <tr>
              <th scope="row">카테고리</th>
              <td><?=$row["cat"]?></td>
            </tr>
            <?
          }
        ?>
      </table>
    </div>

    <ul id="tagselectlist" data-inset="true" data-role="listview" data-filter="false" data-theme="c" data-dividertheme="a">
      <li data-role="list-divider">Tags</li>
      <?
        $tagstmt = $pdo->prepare("SELECT t.index,t.tag,ts.logindex
          FROM tags AS t LEFT OUTER JOIN tagselect AS ts 
            ON (t.index = ts.tagindex) 
          WHERE ts.logindex=:index OR ts.logindex IS NULL ORDER by t.index;");
        $tagstmt->bindParam(':index', $_GET["id"]);
        $tagstmt->execute();
        foreach($tagstmt as $tag)
        {
          if($tag[2] != NULL)
          {
            ?>
              <li class="ui-bar-e"><a href="#" data-tagged=1 data-logid="<?=$_GET['id']?>" data-tagid="<?=$tag[0]?>"><?=$tag[1]?></a></li>
            <?
          }
          else
          {
            ?>
              <li class="ui-bar-d"><a href="#" data-tagged=0 data-logid="<?=$_GET['id']?>" data-tagid="<?=$tag[0]?>"><?=$tag[1]?></a></li>
            <?
          }
        }
      ?>
    </ul>
  </div>

  <div data-role="footer">
    <h4>footer</h4>
  </div>
</div>
</body>
</html>

