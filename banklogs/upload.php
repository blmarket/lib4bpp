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
    $handle = @fopen($_FILES['uploaded_file']['tmp_name'], "r");

    if( ! $handle)
    {
        print("Error Occured");
        return;
    }

    $query = "INSERT INTO `banklogs` (`date`,`dateindex`,`category`,`name`,`expense`,`income`,`bank`,`memo`,`cat`) VALUES (:date,:dateindex,:category,:name,:expense,:income,:bank,:memo,:cat);";
    $stmt = $pdo->prepare($query);

    while( ! feof($handle))
    {
        // read one line
        $buffer = fgets($handle, 8192); //, "utf-8", "euc-kr");

        if(preg_match("/memo_array\[[0-9]*\].*Array\('(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)','(.*)'/", $buffer, $matches))
        {
            $stmt->execute(array(
                ':date' => $matches[2],
                ':dateindex' => $matches[3],
                ':category' => $matches[4],
                ':name' => $matches[5],
                ':expense' => strtr($matches[6],array("," => "")),
                ':income' => strtr($matches[7],array(","=>"")),
                ':bank' => $matches[9],
                ':memo' => $matches[10],
                ':cat' => (int)$matches[6] != 0 ? 1 : 2,
                ));
        }
        /*
            $query = "INSERT INTO `banklogs` (`date`,`category`,`name`,`expense`,`income`,`bank`,`memo`) VALUES (:date,:category,:name,:expense,:income,:bank,:memo);";
            $stmt = $pdo->prepare($query);

            foreach ($rows as $row)
            {
                $cols = $row->getElementsByTagName('td');

                $stmt->execute(array(
                    ':date' => $cols->item(0)->nodeValue,
                    ':category' => $cols->item(1)->nodeValue,
                    ':name' => $cols->item(2)->nodeValue,
                    ':expense' => strtr($cols->item(3)->nodeValue,array("," => "")),
                    ':income' => strtr($cols->item(4)->nodeValue,array(","=>"")),
                    ':bank' => $cols->item(6)->nodeValue,
                    ':memo' => $cols->item(7)->nodeValue,
                    ));
            }
        }
        */
    }

    fclose($handle);
    
    $fileData = file_get_contents($_FILES['uploaded_file']['tmp_name']);

    echo "Done";

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

