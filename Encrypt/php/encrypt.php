<?php $sendBuffer = TRUE; ob_start(); ?>
<html>
<head>
<title>IPWorks Encrypt 2022 Demos - Encrypt</title>
<link rel="stylesheet" type="text/css" href="stylesheet.css">
<meta name="description" content="IPWorks Encrypt 2022 Demos - Encrypt">
</head>

<body>

<div id="content">
<h1>IPWorks Encrypt - Demo Pages</h1>
<h2>Encrypt</h2>
<p>Illustrates how to encrypt and decrypt using symmetric algorithms.</p>
<a href="default.php">[Other Demos]</a>
<hr/>

<?php
require_once('../include/ipworksencrypt_aes.php');
require_once('../include/ipworksencrypt_cast.php');
require_once('../include/ipworksencrypt_des.php');
require_once('../include/ipworksencrypt_idea.php');
require_once('../include/ipworksencrypt_rc2.php');
require_once('../include/ipworksencrypt_rc4.php');
require_once('../include/ipworksencrypt_tripledes.php');
require_once('../include/ipworksencrypt_blowfish.php');
require_once('../include/ipworksencrypt_twofish.php');
require_once('../include/ipworksencrypt_ezcrypt.php');
require_once('../include/ipworksencrypt_const.php');

?>

<?php

try{

$decryptedText = "This is a test of IPWorks Encrypt";
$encryptedText = "";
$algorithm = "aes";

if($_SERVER['REQUEST_METHOD'] == "POST") {
  $algorithm = $_POST["algorithm"];
  $ezcrypt = new IPWorksEncrypt_Ezcrypt();
  if ($algorithm == "aes") {
    $ezcrypt->setAlgorithm(0);
  } else if ($algorithm == "cast") {
	$ezcrypt->setAlgorithm(2);
  } else if ($algorithm == "des") {
    $ezcrypt->setAlgorithm(3);
  } else if ($algorithm == "idea") {
    $ezcrypt->setAlgorithm(4);
  } else if ($algorithm == "rc2") {
    $ezcrypt->setAlgorithm(5);
  } else if ($algorithm == "rc4") {
    $ezcrypt->setAlgorithm(6);
  } else if ($algorithm == "tripledes") {
    $ezcrypt->setAlgorithm(8);
  } else if ($algorithm == "blowfish") {
    $ezcrypt->setAlgorithm(1);
  } else if ($algorithm == "twofish") {
    $ezcrypt->setAlgorithm(9);
  }
    
  if (isset($_POST["encrypt"])) {
    $decryptedText = $_POST["decrypted"];
	$ezcrypt->setUseHex(TRUE);
	$ezcrypt->setInputMessage($decryptedText);
	$ezcrypt->setKeyPassword($_POST["keypassword"]);
	$ezcrypt->doEncrypt();
    $encryptedText = $ezcrypt->getOutputMessage();
	$decryptedText = "";
  } else {
    $encryptedText = $_POST["encrypted"];
	$ezcrypt->setUseHex(TRUE);
	$ezcrypt->setInputMessage($encryptedText);
	$ezcrypt->setKeyPassword($_POST["keypassword"]);
	$ezcrypt->doDecrypt();
    $decryptedText = $ezcrypt->getOutputMessage();
    $encryptedText = "";
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
        <option value="aes" <?php echo ($algorithm=="aes")?"selected":""?>>AES</option>
        <option value="cast" <?php echo ($algorithm=="cast")?"selected":""?>>CAST</option>
	    <option value="des" <?php echo ($algorithm=="des")?"selected":""?>>DES</option>
	    <option value="idea" <?php echo ($algorithm=="idea")?"selected":""?>>IDEA</option>
	    <option value="rc2" <?php echo ($algorithm=="rc2")?"selected":""?>>RC2</option>
	    <option value="rc4" <?php echo ($algorithm=="rc4")?"selected":""?>>RC4</option>
	    <option value="tripledes" <?php echo ($algorithm=="tripledes")?"selected":""?>>TripleDES</option>
	    <option value="blowfish" <?php echo ($algorithm=="blowfish")?"selected":""?>>Blowfish</option>
	    <option value="twofish" <?php echo ($algorithm=="twofish")?"selected":""?>>Twofish</option>
      </select>
    </td>
	<td>
	  Key Password: <input type="text" name="keypassword" size="50" value="<?php echo isset($_POST["keypassword"])?$_POST["keypassword"]:"password"; ?>">
	</td>
  </tr>
  <tr>
    <td>Decrypted:</td>
	<td>Encrypted:</td>
  </tr>
  <tr>
    <td>
	  <textarea name="decrypted" cols="55" rows="15"><?php echo $decryptedText; ?></textarea>
	</td>
    <td>
	  <textarea name="encrypted" cols="55" rows="15"><?php echo $encryptedText; ?></textarea>
	</td>
  </tr>
  <tr>
    <td colspan="2">
	<input type="submit" name="encrypt" value="Encrypt">
	<input type="submit" name="decrypt" value="Decrypt">
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
