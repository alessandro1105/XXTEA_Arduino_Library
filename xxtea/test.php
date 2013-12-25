<?php
$str = "abc|'\][+-|~!@$|`123";
$key = "1234567890123456";

xxtea_encrypt($str, $key);
echo $str;
echo "\n\n";

xxtea_decrypt($str, $key);
echo $str;
echo "\n\n";
?>
