<?php $sendBuffer = TRUE; ob_start(); ?>
<html>
<head>
<title>IPWorks Encrypt 2022 Demos - Hash</title>
<link rel="stylesheet" type="text/css" href="stylesheet.css">
<meta name="description" content="IPWorks Encrypt 2022 Demos - Hash">
</head>

<body>

<div id="content">
<h1>IPWorks Encrypt - Demo Pages</h1>
<h2>Hash</h2>
<p>Shows how to use the Hash component with various algorithms.</p>
<a href="default.php">[Other Demos]</a>
<hr/>

<?php
require_once('../include/ipworksencrypt_hash.php');
require_once('../include/ipworksencrypt_const.php');

?>

<?php

try{

$inputString = "This is a test of IPWorks Encrypt";
$hashValue = "";
$algorithm = "sha1";

if($_SERVER['REQUEST_METHOD'] == "POST") {
  $algorithm = $_POST["algorithm"];
  $hash = new IPWorksEncrypt_Hash();
  if ($algorithm == "sha1") {
    $hash->setAlgorithm(0);
  } else if ($algorithm == "sha224") {
    $hash->setAlgorithm(1);
  } else if ($algorithm == "sha256") {
    $hash->setAlgorithm(2);
  } else if ($algorithm == "sha384") {
    $hash->setAlgorithm(3);
  } else if ($algorithm == "sha512") {
    $hash->setAlgorithm(4);
  } else if ($algorithm == "md2") {
    $hash->setAlgorithm(5);
  } else if ($algorithm == "md4") {
    $hash->setAlgorithm(6);
  } else if ($algorithm == "md5") {
    $hash->setAlgorithm(7);
  } else if ($algorithm == "ripemd") {
    $hash->setAlgorithm(8);
  } else if ($algorithm == "md5sha1") {
    $hash->setAlgorithm(9);
  } else if ($algorithm == "hmacmd5") {
    $hash->setAlgorithm(10);
  } else if ($algorithm == "hmacsha1") {
    $hash->setAlgorithm(11);
  } else if ($algorithm == "hmacsha224") {
    $hash->setAlgorithm(12);
  } else if ($algorithm == "hmacsha256") {
    $hash->setAlgorithm(13);
  } else if ($algorithm == "hmacsha384") {
    $hash->setAlgorithm(14);
  } else if ($algorithm == "hmacsha512") {
    $hash->setAlgorithm(15);
  } else if ($algorithm == "hmacripemd") {
    $hash->setAlgorithm(16);
  } else if ($algorithm == "sha3224") {
    $hash->setAlgorithm(17);
  } else if ($algorithm == "sha3256") {
    $hash->setAlgorithm(18);
  } else if ($algorithm == "sha3384") {
    $hash->setAlgorithm(19);
  } else if ($algorithm == "sha3512") {
    $hash->setAlgorithm(20);
  } 
    
  if (isset($_POST["hash"])) {
    $inputString = $_POST["inputString"];
	$hash->setEncodeHash(TRUE);
	$hash->setInputMessage($inputString);
	$hash->doComputeHash();
    $hashValue = $hash->getHashValue();
  }
}
  } catch (Exception $e) {
    echo '<font color="red">Error: ',  $e->getMessage(), "</font><br/>";
  }
?>

<form method=POST>
<center>
<table width="90%">
  <tr>
    <td>
	  Algorithm: 
	  <select name="algorithm">
	    <option value="sha1" <?php echo ($algorithm=="sha1")?"selected":""?>>SHA1</option>
        <option value="sha224" <?php echo ($algorithm=="sha224")?"selected":""?>>SHA-224</option>
	    <option value="sha256" <?php echo ($algorithm=="sha256")?"selected":""?>>SHA-256</option>
	    <option value="sha384" <?php echo ($algorithm=="sha384")?"selected":""?>>SHA-384</option>
	    <option value="sha512" <?php echo ($algorithm=="sha512")?"selected":""?>>SHA-512</option>
	    <option value="md2" <?php echo ($algorithm=="md2")?"selected":""?>>MD2</option>
	    <option value="md4" <?php echo ($algorithm=="md4")?"selected":""?>>MD4</option>
	    <option value="md5" <?php echo ($algorithm=="md5")?"selected":""?>>MD5</option>
	    <option value="ripemd" <?php echo ($algorithm=="ripemd")?"selected":""?>>RIPEMD-160</option>
		<option value="md5sha1" <?php echo ($algorithm=="md5sha1")?"selected":""?>>MD5SHA1</option>
		<option value="hmacmd5" <?php echo ($algorithm=="hmacmd5")?"selected":""?>>HMAC-MD5</option>
		<option value="hmacsha1" <?php echo ($algorithm=="hmacsha1")?"selected":""?>>HMAC-SHA1</option>
		<option value="hmacsha224" <?php echo ($algorithm=="hmacsha224")?"selected":""?>>HMAC-SHA224</option>
		<option value="hmacsha256" <?php echo ($algorithm=="hmacsha256")?"selected":""?>>HMAC-SHA256</option>
		<option value="hmacsha384" <?php echo ($algorithm=="hmacsha384")?"selected":""?>>HMAC-SHA384</option>
		<option value="hmacsha512" <?php echo ($algorithm=="hmacsha512")?"selected":""?>>HMAC-SHA512</option>
		<option value="hmacripemd" <?php echo ($algorithm=="hmacripemd")?"selected":""?>>HMAC-RIPEMD160</option>
		<option value="sha3224" <?php echo ($algorithm=="sha3224")?"selected":""?>>SHA-3-224</option>
		<option value="sha3256" <?php echo ($algorithm=="sha3256")?"selected":""?>>SHA-3-256</option>
		<option value="sha3384" <?php echo ($algorithm=="sha3384")?"selected":""?>>SHA-3-384</option>
		<option value="sha3512" <?php echo ($algorithm=="sha3512")?"selected":""?>>SHA-3-512</option>
      </select>
    </td>
	<td></td>
  </tr>
  <tr>
    <td>Input String:</td>
	<td>Hash Value:</td>
  </tr>
  <tr>
    <td>
	  <textarea name="inputString" cols="55" rows="15"><?php echo $inputString; ?></textarea>
	</td>
    <td>
	  <textarea name="hash" cols="55" rows="15"><?php echo $hashValue; ?></textarea>
	</td>
  </tr>
  <tr>
    <td colspan="2">
	<input type="submit" name="hash" value="Compute Hash">
    </td>
  </tr>
</table>
</center>
</form>


<br/>
<br/>
<br/>
<hr/>
NOTE: These pages are simple demos, and by no means complete applications.  They
are intended to illustrate the usage of the IPWorks Encrypt objects in a simple,
straightforward way.  What we are hoping to demonstrate is how simple it is to
program with our components.  If you want to know more about them, or if you have
questions, please visit <a href="http://www.nsoftware.com/?demopg-IEPHA" target="_blank">www.nsoftware.com</a> or
contact our technical <a href="http://www.nsoftware.com/support/">support</a>.
<br/>
<br/>
Copyright (c) 2023 /n software inc.
<br/>
<br/>
</div>

<div id="footer">
<center>
IPWorks Encrypt 2022 - Copyright (c) 2023 /n software inc. - For more information, please visit our website at <a href="http://www.nsoftware.com/?demopg-IEPHA" target="_blank">www.nsoftware.com</a>.
</center>
</div>

</body>
</html>

<?php if ($sendBuffer) ob_end_flush(); else ob_end_clean(); ?>
