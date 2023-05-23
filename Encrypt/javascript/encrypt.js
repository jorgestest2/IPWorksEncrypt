/*
 * IPWorks Encrypt 2022 JavaScript Edition - Demo Application
 *
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 *
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
	const ezcrypt = new ipworksencrypt.ezcrypt();
	let operation = "";

	console.log("***************************************************************");
	console.log("* This demo shows how to encrypt and decrypt files            *");
	console.log("* using symmetric algorithms like AES ,DES, 3DES, etc.        *");
	console.log("* The components can also be used to work with data in memory.*");
	console.log("***************************************************************");

	console.log("Specify an algorithm:");
	console.log("1) AES");
	console.log("2) Blowfish");
	console.log("3) CAST");
	console.log("4) DES");
	console.log("5) IDEA");
	console.log("6) RC2");
	console.log("7) RC4");
	console.log("8) TEA");
	console.log("9) 3DES");
	console.log("10) Twofish");
	prompt("algorithm","Algorithm",":","1");

	await rl.on('line', async function(line)
	{
			switch(lastPrompt)
			{
				case "algorithm":
					if(line === "")
						ezcrypt.setAlgorithm(lastDefault - 1);
					else
						ezcrypt.setAlgorithm(line - 1);

					console.log("Select an operation:");
					console.log("1) Encrypt");
					console.log("2) Decrypt");
					prompt("operation","Operation",":","1");
				break;  
				case "operation":
					if(line === "")
						operation = lastDefault;
					else
						operation = line;

					prompt("password","Password",":","test");
				break;
				case "password":
					if(line === "")
						ezcrypt.setKeyPassword(lastDefault);
					else
						ezcrypt.setKeyPassword(line);

					prompt("inputfile","Input File",":","encrypt.js");
				break;
				case "inputfile":
					if(line === "")
						ezcrypt.setInputFile(lastDefault);
					else
						ezcrypt.setInputFile(line);

					prompt("outputfile","Output File",":","encrypt.js.enc.txt");
				break;
				case "outputfile":
					if(line === "")
						ezcrypt.setOutputFile(lastDefault);
					else
						ezcrypt.setOutputFile(line);

					console.log("Performing operation ...");
					if(operation === "1") //Encrypt
						await ezcrypt.encrypt().catch((e) => {
							console.error(e);
							process.exit();
						});
					else //Decrypt
						await ezcrypt.decrypt().catch((e) => {
							console.error(e);
							process.exit();
						});
					console.log("Operation complete!");
					process.exit();
			}

	});
}


function prompt(promptName, label, punctuation, defaultVal)
{
  lastPrompt = promptName;
  lastDefault = defaultVal;
  process.stdout.write(`${label} [${defaultVal}] ${punctuation} `);
}
