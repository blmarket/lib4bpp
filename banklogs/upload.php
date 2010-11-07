<?php
  include 'db_include.php';
?>

<!DOCTYPE html>
<html>
<head>
    <title>가계부 Mobile : Hell on Earth</title>
    <script src="http://code.jquery.com/jquery-1.4.3.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
</head> 
<body> 

<?
  print_r($_FILES);
  if( is_uploaded_file( $_FILES['uploaded_file']['tmp_name'] ) )
  {
    $fileData = file_get_contents($_FILES['uploaded_file']['tmp_name']);
    ?>
    $('div').html('<?=mb_convert_encoding($fileData, "utf-8", "euc-kr")?>').appendTo('form');
    <?
  }
  else
  {
    print("Error occured");
  }
?>

  <form enctype="multipart/form-data" action="upload.php" method="post">
    <input type="file" name="uploaded_file" />
    <input type="submit" value="Upload" />
  </form>
</body>
</html>

