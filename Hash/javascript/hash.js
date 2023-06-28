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
	if (process.argv.length === 2) {
		console.log("Usage:\n\tnode .\\hash.js (sha256 | sha1 | ripemd160  | hmacsha1 ...) file <file>")
		console.log("\tnode .\\hash.js <algorithm> <file_or_string> (<file> | <string>) [nohex]")
		
		console.log("\n\tEx: node ./hash.js sha256 file inputfile.xyz")
		console.log("\tEx: node ./hash.js sha256 string test")
		process.exit();
	}

	const hash_obj = new ipworksencrypt.hash();

	switch (process.argv[2]){
		case 'sha1':
				hash_obj.setAlgorithm(0);
				break;
		case 'sha224':
				hash_obj.setAlgorithm(1);
				break;
		case 'sha256':
				hash_obj.setAlgorithm(2);
				break;
		case 'sha384':
				hash_obj.setAlgorithm(3);
				break;
		case 'sha512':
				hash_obj.setAlgorithm(4);
				break;
		case 'md2':
				hash_obj.setAlgorithm(5);
				break;
		case 'md4':
				hash_obj.setAlgorithm(6);
				break;
		case 'md5':
				hash_obj.setAlgorithm(7);
				break;
		case 'ripemd160':
				hash_obj.setAlgorithm(8);
				break;
		case 'md5sha1':
				hash_obj.setAlgorithm(9);
				break;
		case 'hmacmd5':
				hash_obj.setAlgorithm(10);
				break;
		case 'hmacsha1':
				hash_obj.setAlgorithm(11);
				break;
		case 'hmacsha224':
				hash_obj.setAlgorithm(12);
				break;
		case 'hmacsha256':
				hash_obj.setAlgorithm(13);
				break;
		case 'hmacsha384':
				hash_obj.setAlgorithm(14);
				break;
		case 'hmacsha512':
				hash_obj.setAlgorithm(15);
				break;
		case 'hmacripemd160':
				hash_obj.setAlgorithm(16);
				break;
		case 'sha3224':
				hash_obj.setAlgorithm(17);
				break;
		case 'sha3256':
				hash_obj.setAlgorithm(18);
				break;
		case 'sha3384':
				hash_obj.setAlgorithm(19);
				break;
		case 'sha3512':
				hash_obj.setAlgorithm(20);
				break;
		case 'sha512224':
				hash_obj.setAlgorithm(21);
				break;
		case 'sha512256':
				hash_obj.setAlgorithm(22);
				break;
	}

	if (process.argv.length === 6 && process.argv[5] === "nohex"){
		hash_obj.setEncodeHash(false);	
	}
	if (process.argv[3] === 'file'){
		hash_obj.setInputFile(process.argv[4]);
	} else if (process.argv[3] === 'string'){
		hash_obj.setInputMessage(process.argv[4])
	} else {
		console.log("Invalid source type.")
		process.exit()
	}

	try{
		await hash_obj.computeHash();
			
		console.log(hash_obj.getHashValue() + "");

		process.exit();
	} catch (e) {
			console.log(e);
			process.exit();
	}
}



function prompt(promptName, label, punctuation, defaultVal)
{
  lastPrompt = promptName;
  lastDefault = defaultVal;
  process.stdout.write(`${label} [${defaultVal}] ${punctuation} `);
}
