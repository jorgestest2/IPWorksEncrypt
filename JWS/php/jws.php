<?php $sendBuffer = TRUE; ob_start(); ?>
<html>
<head>
<title>IPWorks Encrypt 2022 Demos - JWS</title>
<link rel="stylesheet" type="text/css" href="stylesheet.css">
<meta name="description" content="IPWorks Encrypt 2022 Demos - JWS">
</head>

<body>

<div id="content">
<h1>IPWorks Encrypt - Demo Pages</h1>
<h2>JWS</h2>
<p>Shows how to sign and verify JSON Web Signatures using various algorithms.</p>
<a href="default.php">[Other Demos]</a>
<hr/>

<?php
require_once('../include/ipworksencrypt_jws.php');
require_once('../include/ipworksencrypt_certmgr.php');
require_once('../include/ipworksencrypt_const.php');

?>

<?php
try{
$messageText = "";
$signedText = "";
$algorithm = "HS256";
$keyText = "txAVam2uGT20a+ZJC1VWVGCM8tFYSKyJlw+2fgS/BdA=";

if($_SERVER['REQUEST_METHOD'] == "POST") {
  $algorithm = $_POST["algorithm"];
  $signedText = $_POST["signed"];
  $messageText = $_POST["message"];
  $jws = new IPWorksEncrypt_Jws();
	if ($algorithm == "HS256") {
		$keyText = "txAVam2uGT20a+ZJC1VWVGCM8tFYSKyJlw+2fgS/BdA=";
	} else if ($algorithm == "HS384") {
		$keyText = "5C/iq/SVHc1i++8elF0u3Cg8w1D1Nj8Idrsw2zzIQeLrolmPk5d26f6MxTE3Npy2";
	} else if ($algorithm == "HS512") {
		$keyText = "AGVJSwvgVMU0cspZ7ChlxURcgCcdj7QV6nm0fr0C/rNtuh8F5uA7nCs4efKuWUDBw7/s9ikfTm0Kx4uZ3SYXcA==";
	} 
  if (isset($_POST["sign"])) {
	  if ($algorithm == "HS256") {
		$jws->setAlgorithm(0);
	} else if ($algorithm == "HS384") {
		$jws->setAlgorithm(1);		
	} else if ($algorithm == "HS512") {
		$jws->setAlgorithm(2);
	} 
	$jws->doConfig("KeyEncoding=1"); //Base64 input
	$jws->setKey($keyText);
	$jws->setInputMessage($messageText);
	$jws->doSign();
	$signedText = $jws->getOutputMessage();
	$messageText = "";
  } else if (isset($_POST["verify"])) {
	if ($algorithm == "HS256") {
		$jws->setAlgorithm(0);
	} else if ($algorithm == "HS384") {
		$jws->setAlgorithm(1);		
	} else if ($algorithm == "HS512") {
		$jws->setAlgorithm(2);
	} 
	$jws->doConfig("KeyEncoding=1"); //Base64 input
	$jws->setKey($keyText);
	$jws->setInputMessage($signedText);
	$jws->doVerify();
	$messageText = $jws->getOutputMessage();
	$signedText = "";
  }
  
	/*
	* The JWS component can also sign payloads using RSA algorithms
	* This example code demonstrates how RSA would be used
	$jws->setAlgorithm(3); //jwsRS256
	$jws->setCertStoreType(2); //cstPFX
	$jws->setCertStore("..\\testrsapriv.pfx");
	$jws->setCertStorePassword("test");
	$jws->setCertSubject("*");
	$jws->setInputMessage = "test";
	$jws->doSign();
	*/

	/*
	* The JWS component can also sign payloads using ECDSA algorithms
	* This example code demonstrates how ECDSA would be used
	$jws->setAlgorithm(9); //jwsES256
	$jws->setCertStoreType(6); //cstPEMKeyFile
	$jws->setCertStore("..\\testeccpriv.txt");
	$jws->setCertSubject("*");
	$jws->setInputMessage = "test";
	$jws->doSign();
	*/	
	
	
	
	/*
	* The JWS component can also verify JWS strings using RSA algorithms
	* This example code demonstrates how RSA would be used
	$jws->setAlgorithm(3); //jwsRS256
	$jws->setCertStoreType(6); //cstPEMKeyFile
	$jws->setCertStore("..\\testrsapub.cer");
	$jws->setCertSubject("*");
	$jws->setInputMessage = "test";
	$jws->doVerify();
	*/

	/*
	* The JWS component can also verify JWS strings using ECDSA algorithms
	* This example code demonstrates how ECDSA would be used
	$jws->setAlgorithm(9); //jwsES256
	$jws->setCertStoreType(8); //cstPublicKeyFile
	$jws->setCertStore("..\\testeccpub.txt");
	$jws->setCertSubject("*");
	$jws->setInputMessage = "test";
	$jws->doVerify();
	*/
}
  } catch (Exception $e) {
    echo '<font color="red">Error: ',  $e->getMessage(), "</font><br/>";
  }
?>

<form method=POST name=formJws>
<center>
<table width="90%">
  <tr>
    <td>
	  Algorithm: 
	  <select name="algorithm" onChange="formJws.submit();">
        <option value="HS256" <?php echo ($algorithm=="HS256")?"selected":""?>>HS256</option>
        <option value="HS384" <?php echo ($algorithm=="HS384")?"selected":""?>>HS384</option>
	    <option value="HS512" <?php echo ($algorithm=="HS512")?"selected":""?>>HS512</option>
      </select>
    </td>
	<td>
	  Key: <input type="text" name="key" size="50" value="<?php echo $keyText; ?>">
	</td>
  </tr>
  <tr>
    <td>Payload:</td>
	<td>JWS String:</td>
  </tr>
  <tr>
    <td>
	  <textarea name="message" cols="55" rows="15"><?php echo $messageText; ?></textarea>
	</td>
    <td>
	  <textarea name="signed" cols="55" rows="15"><?php echo $signedText; ?></textarea>
	</td>
  </tr>
  <tr>
    <td>
	<input type="submit" name="sign" value="Sign >>>">
    </td>
	<td>
	<input type="submit" name="verify" value="<<< Verify">
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
