/*
 * IPWorks Encrypt 2022 Java Edition- Demo Application
 *
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 *
 */

import java.io.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import ipworksencrypt.*;

public class openpgp extends ConsoleDemo {
  Openpgp pgp = new Openpgp();
  Keymgr keymgr = new Keymgr();

  public openpgp(){
    try
    {
      String keyringDir = "";
    	
      System.out.println("************************************************************");
      System.out.println("IPWorks Encrypt Java Edition - OpenPGP Demo Application.  ");
      System.out.println("This demo shows how to use the OpenPGP component encrypt or ");
      System.out.println("decrpyt a message and to sign or verify a message.          ");
      System.out.println("************************************************************\n");

      keymgr.addKeymgrEventListener(new DefaultKeymgrEventListener() {
        public void keyList(KeymgrKeyListEvent e) {
          System.out.println(String.format("%-80s [%-8s] %-12s", e.userId, e.keyId, (e.hasSecretKey ? "private" : "")));
        }
      });

      
      boolean keyringLoaded = false;
      while(!keyringLoaded) {
    	try {
          keyringDir = prompt("Keyring Directory (Enter \":q\" to exit)");
          if(keyringDir.equalsIgnoreCase(":q"))
        	System.exit(0);
          keymgr.loadKeyring(keyringDir);
          keyringLoaded = true;
    	} catch(Exception ex) {
        	System.out.println("Error: " + ex.getMessage());      
          }
      }
      
      if (ask("Create a new key", "?", "(y/n)") == 'y') {
        System.out.println("\nListing keys...\n");
        System.out.println(String.format("%-80s %-10s %-12s", "User ID", "Key ID", "Private Key"));
        keymgr.listKeys();
        System.out.println();

        while (true) {
          char command =  ask("Please enter a command", ":", "(c: create key, d: delete key, s: save keyring, q: cancel)");
          if (command == 'c') {
            keymgr.createKey(prompt("User ID"), prompt("Passphrase"));
            System.out.println();
            keymgr.listKeys();
            System.out.println();
          } else if (command == 'd') {
            keymgr.deleteKey(prompt("User ID"));
            System.out.println();
            keymgr.listKeys();
            System.out.println();
          } else if (command == 's') {
            keymgr.saveKeyring(keyringDir);
            break;
          } else if (command == 'q') {
            break;
          } else {
            System.out.println("Invalid command.");
          }
        }
      }

      System.out.println("\nListing keys...\n");
      System.out.println(String.format("%-80s %-10s %-12s", "User ID", "Key ID", "Private Key"));
      keymgr.listKeys();
      System.out.println();

      String privateKey = prompt("Private Key User ID (Used to sign outgoing messages and decrypt incoming messages)");
      String passphrase = "";
      if (privateKey.length() > 0) passphrase = prompt("Passphrase");
      String recipientKey = prompt("Recipient Key User ID (Used to encrypt outgoing messages)");
      String signerKey = prompt("Signer Key User ID (Used to verify the signature of an incoming message)");

      while (true) {
        System.out.println();
        int command = Character.getNumericValue(ask("Please enter a command", ":", "(0: quit, 1: encrypt, 2: decrypt, 3: sign, 4: verify, 5: sign and encrypt, 6: decrypt and verify)"));
        if (command < 0 || command > 6) {
          System.out.println("Invalid Command.");
          continue;
        }
        if (command == 0) {
          break;
        }
        try {
          pgp.reset();
          pgp.setASCIIArmor(true);
          if (ask("Read from file or string", "?", "(f/s)") == 'f') {
            pgp.setInputFile(prompt("Input File", ":", pgp.getInputFile()));
            pgp.setOutputFile(prompt("Output File", ":", pgp.getOutputFile()));
            pgp.setOverwrite(ask("Overwrite file", "?", "(y/n)") == 'y');
          } else {
            System.out.println("Please enter the message. When finished enter \":q\" on a line by itself:");
            BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
            String temp = "";
            while (!(temp = bf.readLine()).equalsIgnoreCase(":q")) {
              temp += "\n";
              byte[] bytes = new byte[pgp.getInputMessage().length + temp.getBytes().length];
              System.arraycopy(pgp.getInputMessage(), 0, bytes, 0, pgp.getInputMessage().length);
              System.arraycopy(temp.getBytes(), 0, bytes, pgp.getInputMessage().length, temp.getBytes().length);
              pgp.setInputMessage(bytes);
            }
          }

          if (command == 1) { //Encrypt
            if (recipientKey.length() <= 0) {
              System.out.println("Please select a recipient key.");
              break;
            }
            pgp.getRecipientKeys().add(new Key(keyringDir, recipientKey));
            pgp.encrypt();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }
          } else if (command == 2) { //Decrypt
            if (privateKey.length() <= 0) {
              System.out.println("Please select a private key.");
              break;
            }
            pgp.getKeys().add(new Key(keyringDir, privateKey));
            pgp.getKeys().item(0).setPassphrase(passphrase);
            pgp.setASCIIArmor(true);
            pgp.decrypt();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }
          } else if (command == 3) { //Sign
            if (privateKey.length() <= 0) {
              System.out.println("Please select a private key.");
              break;
            }
            pgp.getKeys().add(new Key(keyringDir, privateKey));
            pgp.getKeys().item(0).setPassphrase(passphrase);
            pgp.sign();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }
          } else if (command == 4) { //Verify
            if (signerKey.length() <= 0) {
              System.out.println("Please select a signer key.");
              break;
            }
            pgp.getSignerKeys().add(new Key(keyringDir, signerKey));
            pgp.verifySignature();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }
          } else if (command == 5) { //Sign and Encrypt
            if (privateKey.length() <= 0) {
              System.out.println("Please select a private key.");
              break;
            }
            if (recipientKey.length() <= 0) {
              System.out.println("Please select a recipient key.");
              break;
            }
            pgp.getKeys().add(new Key(keyringDir, privateKey));
            pgp.getKeys().item(0).setPassphrase(passphrase);
            pgp.getRecipientKeys().add(new Key(keyringDir, recipientKey));
            pgp.signAndEncrypt();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }
          } else if (command == 6) { //Decrypt and Verify
            if (privateKey.length() <= 0) {
              System.out.println("Please select a private key.");
              break;
            }
            if (signerKey.length() <= 0) {
              System.out.println("Please select a signer key.");
              break;
            }
            pgp.getKeys().add(new Key(keyringDir, privateKey));
            pgp.getKeys().item(0).setPassphrase(passphrase);
            pgp.getSignerKeys().add(new Key(keyringDir, signerKey));
            pgp.decryptAndVerifySignature();
            if (pgp.getOutputFile().length() <= 0) {
              System.out.println("\nOutput Message:\n");
              System.out.println(new String(pgp.getOutputMessage()));
            }        
          }
        } catch(Exception ex) {
          System.out.println("Error: " + ex.getMessage());
        }
      }

    } catch(IPWorksEncryptException ex) {
      displayError(ex);
    } catch(Exception ex) {
      displayError(ex);
    }
  }

  public static void main(String[] args) {
    new openpgp();
  }
}


class ConsoleDemo {
  private static BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));

  static String input() {
    try {
      return bf.readLine();
    } catch (IOException ioe) {
      return "";
    }
  }
  static char read() {
    return input().charAt(0);
  }

  static String prompt(String label) {
    return prompt(label, ":");
  }
  static String prompt(String label, String punctuation) {
    System.out.print(label + punctuation + " ");
    return input();
  }

  static String prompt(String label, String punctuation, String defaultVal)
  {
	System.out.print(label + " [" + defaultVal + "] " + punctuation + " ");
	String response = input();
	if(response.equals(""))
		return defaultVal;
	else
		return response;
  }

  static char ask(String label) {
    return ask(label, "?");
  }
  static char ask(String label, String punctuation) {
    return ask(label, punctuation, "(y/n)");
  }
  static char ask(String label, String punctuation, String answers) {
    System.out.print(label + punctuation + " " + answers + " ");
    return Character.toLowerCase(read());
  }

  static void displayError(Exception e) {
    System.out.print("Error");
    if (e instanceof IPWorksEncryptException) {
      System.out.print(" (" + ((IPWorksEncryptException) e).getCode() + ")");
    }
    System.out.println(": " + e.getMessage());
    e.printStackTrace();
  }
}




