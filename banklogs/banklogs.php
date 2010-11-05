<?php
  include 'db_include.php';
?>

<!DOCTYPE html>
<html>
<head>
        <title>jQuery Mobile: Demos and Documentation</title>
        <link rel="stylesheet" href="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.css" />
        <link rel="stylesheet" href="test.css" />
        <script src="http://code.jquery.com/jquery-1.4.3.js"></script>
        <script src="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.js"></script>
</head> 
<body> 
<div data-role="page" id="initial">
  <div data-role="header">
    <h1>Page Title</h1>
  </div>

  <div data-role="content">
    <ul data-role="listview" data-inset="true">
      <li><img src="logs-images/album-bb.jpg" alt="France" class="ui-li-icon"><a href="index.html">France</a> <span class="ui-li-count">4</span></li>
    </ul>

    <ul data-role="listview" data-inset="true">
      <?php
      /*
SELECT * FROM t1 ORDER BY key_part1 DESC, key_part2 ASC;
      */
        $sql="select * from banklogs order by date desc;";
        $stmt = $pdo->query($sql);

        foreach($stmt as $row)
        {
          $var = $row["income"] - $row["expense"];
          $class;
          switch($row["cat"]) // TODO: 이것좀 어떻게 정리해봐?
          {
            case NULL:
                $class="";
                break;
            case 1:
                $class="ui-bar-e";
                break;
            case 2:
                $class="ui-bar-d";
                break;
          }
          ?>
            <li class="<?=$class?>">
              <img src="logs-images/album-bb.jpg" alt="bb"/>
              <h3><a href="detail_log.php?id=<?=$row["index"]?>">[<?=$row["date"]?>]<?=$var?> : <?=$row["name"]?></a></h3>
              <p><?=$row["memo"]?></p>
              <span class="ui-li-count">4</span>
              <a href="detail_log.php?id=<?=$row["index"]?>">asdf</a>
            </li>
          <?
        }
      ?>


<!-- 다른 items 시안.
      <li>
          <img src="logs-images/album-bb.jpg" />
          <h3><a href="index.html">Broken Bells</a></h3>
          <p>Broken Bells</p>
          <a href="index.html">Purchase album</a>
      </li>
      <li>
        <img src="logs-images/album-bb.jpg" alt="bb"/>
        <h3><a href="#initial">-30000</a></h3>
        <p>지출, 점심, 햄버거</p>
        <h3 class="ui-li-aside">신맥아셈</h3>
      </li>
      <li>
        <img src="logs-images/album-p.jpg" alt="p"/>
        <h3><a href="#initial">asdf</a></h3>
        <p>2000000</p> 
        <p class="ui-li-aside">주식회사</p>
      </li>
      <li>
        <h2>-1000000</h2>
        <p>사이버자</p>
      </li>
      <li>
        <h1>-5000</h1>
        <p>어스윈드</p>
      </li>
-->
    </ul>
  </div>

  <div data-role="footer">
    <h4>footer</h4>
  </div>
</div>
</body>
</html>

