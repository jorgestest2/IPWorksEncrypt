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
		console.log("Usage:\n\tnode .\\ezrand.js int (isaac | platform | rc4) ")
		console.log("\tnode .\\ezrand.js int <algorithm> [min] [max] [seed] [number_to_generate]")
		console.log("\tnode .\\ezrand.js byte <algorithm> <byte_length> [seed] [number_to_generate]")
		
		process.exit();
	}

	const ezrand = new ipworksencrypt.ezrand()

	const ezrandomgenerator = async function(rl, _int_or_byte,  _algorithm, _min, _max, _seed, _num_to_generate) {

		if (!_int_or_byte) {
			console.log('Error: Must specify type (i/b).')
			process.exit() 
		}
		if (!_algorithm) {
			console.log('Error: Must specify algorithm.')
			process.exit()
		}

		switch (_algorithm)
		{
			case 'isaac':     
					ezrand.setAlgorithm(0);
					break;
			case 'platform':          
					ezrand.setAlgorithm(2);
					break;
			case 'rc4':        
					ezrand.setAlgorithm(4);
					break;
			default:
					console.log("Invalid algorithm.");
		} 

	switch (_int_or_byte){
		case 'int':
			// case integer
			if (!_min) { _min = 0 }
			ezrand.setMin(parseInt(_min));

			if (!_max) { _max = 100 }
			ezrand.setMax(parseInt(_max));

			if (!_seed) { _seed = "" }
			ezrand.setSeed(_seed);
			
			if (_num_to_generate){
				var i = 0;
				while (i < _num_to_generate){
					ezrand.getNextInt()
					console.log(ezrand.getRandInt())
					i++
				}
				break;
			} else {
					ezrand.getNextInt()
					console.log(ezrand.getRandInt())
					break;
			}


		case 'byte':
			// since there are fewer required fields for this case, we will access the command
			// line arguments by index instead of variable name
			if (process.argv.length < 4) {
				console.log('Err: Missing required fields')
				process.exit() 
			}
			if (process.argv.length === 5){ _seed = ""}
			else {_seed = process.argv[5]}
			ezrand.setSeed(_seed);

			ezrand.setRandBytesLength(parseInt(_min));

			if (process.argv.length === 7) { 

				let i = 0;
				

				while (i < parseInt(process.argv[6])){
					await ezrand.getNextBytes()
					byte_string = ""
					next_byte = await ezrand.getRandBytes();
					let j = 0;
					while (j < next_byte.length){
						byte_string += next_byte[j].toString(16) + "  " 				 
						j++
					}
					console.log(byte_string)
					i++
				}
				break;
			} else {
					await ezrand.getNextBytes();
					next_byte = await ezrand.getRandBytes();
					var i = 0;
					byte_string = ""
					while (i < next_byte.length){
						byte_string+=next_byte[i].toString(16) + "  "  
						i++
					}
					console.log(byte_string);
					break;
			}
		default:
			console.log("Invalid option.");
	}
		
	}

	await ezrandomgenerator(rl, process.argv[2],process.argv[3],process.argv[4],process.argv[5],process.argv[6],process.argv[7]);
	process.exit();
}


function prompt(promptName, label, punctuation, defaultVal)
{
  lastPrompt = promptName;
  lastDefault = defaultVal;
  process.stdout.write(`${label} [${defaultVal}] ${punctuation} `);
}
