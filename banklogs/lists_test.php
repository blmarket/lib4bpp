<?php
  include 'db_include.php';

  $stmt = $pdo->query("SELECT * FROM tags ORDER by `index`");
?>

<!DOCTYPE html>
<html>
<head>
    <title>가계부 Mobile : Hell on Earth</title>
    <link rel="stylesheet" href="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.css" />
    <link rel="stylesheet" href="test.css" />
    <script src="http://code.jquery.com/jquery-1.4.3.js"></script>
    <script src="http://code.jquery.com/mobile/1.0a1/jquery.mobile-1.0a1.js"></script>
    <script src="test.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
</head> 
<body> 
<div data-role="page" id="lists_test">
  <div data-role="header">
    <h1>Test</h1>
  </div>

  <!-- it works
  <form action="javascript:alert('succ');" role="search" class="ui-listview-filter ui-bar-c"><div class="ui-input-search ui-shadow-inset ui-btn-corner-all ui-body-c ui-btn-shadow ui-icon-search"><input class="ui-input-text ui-body-c" data-type="search" placeholder="Filter results..."><a data-theme="c" href="#" class="ui-input-clear ui-btn ui-btn-icon-notext ui-btn-corner-all ui-shadow ui-btn-up-c ui-input-clear-hidden" title="clear text"><span class="ui-btn-inner ui-btn-corner-all"><span class="ui-icon ui-icon-delete ui-icon-shadow"></span><span class="ui-btn-text">clear text</span></span></a></div></form>
  -->

  <div data-role="content">
    <ul id="taglist" data-role="listview" data-filter="true"> <!-- TODO: 여기를 true로 바꾸면 됩니다 -->
      <?
        foreach($stmt as $row)
        {
          ?>
            <li><a href="#"><?=$row["tag"]?></a></li>
          <?
        }
      ?>
      <!--
      <li><a href="index.html">Acura</a></li>
      <li><a href="index.html">Audi</a></li>
      <li><a href="index.html">BMW</a></li>

      <li><a href="index.html">Cadillac</a></li>
      <li><a href="index.html">Chrysler</a></li>
      <li><a href="index.html">Dodge</a></li>
      <li><a href="index.html">Ferrari</a></li>
      <li><a href="index.html">Ford</a></li>
      <li><a href="index.html">GMC</a></li>

      <li><a href="index.html">Honda</a></li>
      <li><a href="index.html">Hyundai</a></li>
      <li><a href="index.html">Infiniti</a></li>
      <li><a href="index.html">Jeep</a></li>
      <li><a href="index.html">Kia</a></li>
      <li><a href="index.html">Lexus</a></li>

      <li><a href="index.html">Mini</a></li>
      <li><a href="index.html">Nissan</a></li>
      <li><a href="index.html">Porsche</a></li>
      <li><a href="index.html">Subaru</a></li>
      <li><a href="index.html">Toyota</a></li>
      <li><a href="index.html">Volkswagon</a></li>

      <li><a href="index.html">Volvo</a></li>
      -->
    </ul>
  </div> <!-- content -->

  <div data-role="footer">
    <h4>footer</h4>
  </div>
</div>
</body>
</html>

