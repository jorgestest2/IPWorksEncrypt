/*
 * IPWorks Encrypt 2022 JavaScript Edition - Sample Project
 *
 * This sample project demonstrates the usage of IPWorks Encrypt in a 
 * simple, straightforward way. This is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * Copyright (c) 2023 /n software inc. www.nsoftware.com
 */
 
const readline = require("readline");
const ipworksencrypt = require("@nsoftware/ipworksencrypt");

if(!ipworksencrypt) {
  console.error("Cannot find ipworksencrypt.");
  process.exit(1);
}
let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const smime = new ipworksencrypt.smime();

main();

async function main() {

	const recipientCertFile = 'testcert.cer'; //Public key only
	const myCertFile = 'testcert.pfx'; //Has private key

	console.log('\nWelcome to the IPWorks SMIME Demo.');
	console.log('This demo shows how to use the SMIME component to sign/encrypt/decrypt/verify messages.'); 
	console.log('This demo ships with example certificates which are used for simplicity.');
	console.log('------------------------------------------------------------ \n');

	console.log('To begin specify some text to encrypt and/or sign.');

	prompt('inputdata','Input data',':','test');

	rl.on('line', async function(line) {
		switch (lastPrompt) {
			case 'inputdata':
				if(line ==='')
					smime.setInputMessage(lastDefault);
				else
					smime.setInputMessage(line);
				
				displayEncryptOptions();

			break;
			case 'encryptop':
				let choiceEnc = line;
				if (line === '')
					choiceEnc = lastDefault
				switch (choiceEnc) {
					case '1': //Encrypt
						//Specify the recipient's public key
						try {	
							await smime.getRecipientCerts().add(new ipworksencrypt.Certificate(8, recipientCertFile, "", "*"));
							await smime.encrypt();
						} catch (e) {
							console.log(e);
							process.exit();
						}		
						encryptComplete();
					break;
					case '2': //Sign
						//Specify the private key for signing
						try {
							await smime.setCertificate(new ipworksencrypt.Certificate(2, myCertFile, "password", "*"));
							await smime.sign();
						} catch (e) {
							console.log(e);
							process.exit();
						}	
						encryptComplete();
					break;
					case '3': //Sign and Encrypt
						//Specify the recipient's public key
						try {
							await smime.getRecipientCerts().add(new ipworksencrypt.Certificate(8, recipientCertFile, "", "*"));
							await smime.setCertificate(new ipworksencrypt.Certificate(2, myCertFile, "password", "*"));
							await smime.signAndEncrypt();
						} catch (e) {
							console.log(e);
							process.exit();
						}	
						encryptComplete();
					break;
					default:
						console.log('Invalid selection.');
						displayEncryptOptions();
					break; 
				} //line
			break; //encryptop
			case 'decryptop':
				let choiceDec = line;
				if (line === '')
					choiceDec = lastDefault
				switch (choiceDec) {
					case '1': //Decrypt
						//Specify the private key for decryption
						try {
							await smime.setCertificate(new ipworksencrypt.Certificate(2, myCertFile, "password", "*"));
							await smime.decrypt();
						} catch (e) {
							console.log(e);
							process.exit();
						}	
						decryptComplete();      
					case '2': //Verify Only
						//The signer's certificate (if any) is included in the SMIME message already. 
						//It does not need to be specified in order to perform signature verfication.
						
						smime.verifySignature();
						decryptComplete();
					break;
					case '3': //Decrypt And Verify
						try {
							await smime.setCertificate(new ipworksencrypt.Certificate(2, myCertFile, "password", "*"));
							await smime.decryptAndVerifySignature();
						} catch (e) {
							console.log(e);
							process.exit();
						}	
						decryptComplete(); 
					break;
					default:
						console.log('Invalid selection.');
						displayDecryptOptions();
					break; 
				} //line
			break; //decryptop    
		}
	});
}

function displayEncryptOptions()
{
  console.log('\nOperation:');
  console.log(' 1) Encrypt');
  console.log(' 2) Sign');
  console.log(' 3) Sign and Encrypt\n');
  prompt('encryptop','Enter Selection',':','3');
}

function displayDecryptOptions()
{
  console.log('\nOperation:');
  console.log(' 1) Decrypt');
  console.log(' 2) Verify');
  console.log(' 3) Decrypt and Verify\n');
  prompt('decryptop','Enter Selection',':','3');
}

function encryptComplete()
{
	console.log('\n\nOperation Complete. SMIME message:\n\n');
	console.log(smime.getOutputMessageHeadersString() + '\n\n' + smime.getOutputMessage());

	smime.setInputMessage(smime.getOutputMessage());
	smime.setInputMessageHeadersString(smime.getOutputMessageHeadersString());
	
	console.log('\n\nAfter encrypting/signing; the message may now be decrypted and the signature verified.');
	displayDecryptOptions();
}

function decryptComplete()
{
	console.log('\n\nOperation Complete. Decrypted/Verified message:\n\n');
	console.log(smime.getOutputMessage().toString() + '\n');

   process.exit();
}



function prompt(promptName, label, punctuation, defaultVal)
{
  lastPrompt = promptName;
  lastDefault = defaultVal;
  process.stdout.write(`${label} [${defaultVal}] ${punctuation} `);
}
