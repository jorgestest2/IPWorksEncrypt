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

main();

async function main() {
	const pgp = new ipworksencrypt.openpgp();
	const keymgr = new ipworksencrypt.keymgr();
	
	let keyringDir = "";
	let operation = "";
	
	console.log("********************************************************************");
	console.log("* This demo shows how to sign, encrypt, decrypt, and verify data   *");
	console.log("* using OpenPGP. While this demo is configured to work with files  *");
	console.log("* the components can also be used to work with data in memory.     *");
	console.log("********************************************************************");

	prompt("keyring","Keyring directory (enter 'create' to automatically create one)",":","create");

	rl.on('line', async function(line)
	{
		switch(lastPrompt)
		{
			case "keyring":
				if(line === "create" || line === "")
				{
					//Create a keyring directory
					await keymgr.createKey("test@nsoftware.com","test").catch((e) => {
							console.error(e);
							process.exit();
					});
						
					await keymgr.saveKeyring(".").catch((e) => {
							console.error(e);
							process.exit();
					});

					keyringDir = ".";
					promptPrivateKey();
				}
				else { //Use the provided keyring
					keyringDir = line;
					promptPrivateKey();
				}
			
			break;
			case "privkey":
				if(line === "")
					pgp.getKeys().add(await new ipworksencrypt.Key(keyringDir, lastDefault));
				else
					pgp.getKeys().add(await new ipworksencrypt.Key(keyringDir, line));

				prompt("passphrase","Passphrase",":","test");
			break;
			case "passphrase":
				if(line === "")
					pgp.getKeys().get(0).setPassphrase(lastDefault);
				else
					pgp.getKeys().get(0).setPassphrase(line);

				prompt("recipientkey","Recipient key user Id (used for encrypting)",":","test@nsoftware.com");
			break;
			case "recipientkey":
				if(line === "")
					pgp.getRecipientKeys().add(new ipworksencrypt.Key(keyringDir, lastDefault));
				else
					pgp.getRecipientKeys().add(new ipworksencrypt.Key(keyringDir, line));

				prompt("signerkey","Signer key user Id (used for signature verification)",":","test@nsoftware.com");
			break;
			case "signerkey":
				if(line === "")
					pgp.getSignerKeys().add(new ipworksencrypt.Key(keyringDir, lastDefault));
				else
					pgp.getSignerKeys().add(new ipworksencrypt.Key(keyringDir, line));

				prompt("inputfile","Input file",":","openpgp.js");
			break; 
			case "inputfile":
				if(line === "")
					pgp.setInputFile(lastDefault);
				else
					pgp.setInputFile(line);

				prompt("outputfile","Output file",":","openpgp.js.asc");
			break;
			case "outputfile":
				if(line === "")
					pgp.setOutputFile(lastDefault);
				else
					pgp.setOutputFile(line);
		
				displayOptions();
			break;
			case "operation":
				pgp.setASCIIArmor(true);
				switch(line){
					case "":
					case "1":
						await pgp.encrypt().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					case "2":
						await pgp.sign().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					case "3":
						await pgp.signAndEncrypt().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					case "4":
						await pgp.decrypt().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					case "5":
						await pgp.verifySignature().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					case "6":
						await pgp.decryptAndVerifySignature().catch((e) => {
							console.error(e);
							process.exit();
						});
					break;
					default:
						console.log('Invalid Selection.');
						process.exit();
					break;
				}
				console.log('Operation Complete.');
				process.exit();
			break;

		}
	});
}

function promptPrivateKey()
{
  prompt("privkey","Private key user Id (used for signing and decrypting)",":","test@nsoftware.com");
}

function displayOptions()
{
  console.log("Operations: ");
  console.log("1) Encrypt");
  console.log("2) Sign");
  console.log("3) Sign and Encrypt");
  console.log("4) Decrypt");
  console.log("5) Verify");
  console.log("6) Decrypt and Verify");
  prompt("operation","Choose an operation",":","1");
}



function prompt(promptName, label, punctuation, defaultVal)
{
  lastPrompt = promptName;
  lastDefault = defaultVal;
  process.stdout.write(`${label} [${defaultVal}] ${punctuation} `);
}
