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
  if( is_uploaded_file( $_FILES['uploaded_file']['tmp_name'] ) )
  {  
    print_r($_FILES);

    $handle = @fopen($_FILES['uploaded_file']['tmp_name'], "r");

    if( ! $handle)
    {
        print("Error Occured");
        return;
    }

    while( ! feof($handle))
    {
        $buffer = mb_convert_encoding(fgets($handle, 8192), "utf-8", "euc-kr");

        if(strpos($buffer, "메모") != FALSE)
        {
            print("Memo Found asdf<br/>");
            $bmt = "<table>" . mb_convert_encoding(fread($handle, $_FILES['uploaded_file']['size']), "utf-8", "euc-kr");

            $dom = new domDocument;
            $dom->loadHTML($bmt);

            print($dom->actualEncoding . "<br/>");

            $dom->preserveWhiteSpace = false;

            $tables = $dom->getElementsByTagName('table');

            $table = $tables->item(0);

            /*** get all rows from the table ***/
            $rows = $table->getElementsByTagName('tr');

            /*** loop over the table rows ***/
            foreach ($rows as $row)
            {
                /*** get each column by tag name ***/
                $cols = $row->getElementsByTagName('td');
                /*** echo the values ***/
                echo mb_convert_encoding($cols->item(0)->nodeValue, "euc-kr", "utf-8").'<br />';
                echo $cols->item(1)->nodeValue.'<br />';
                echo $cols->item(2)->nodeValue;
                echo '<hr />'; 
            }
        }
    }

    fclose($handle);
    
    $fileData = file_get_contents($_FILES['uploaded_file']['tmp_name']);

    /*
    ?>
    $('div').html('<?=mb_convert_encoding($fileData, "utf-8", "euc-kr")?>').appendTo('form');
    <?
    */
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

