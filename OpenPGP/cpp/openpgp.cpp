/*
 * IPWorks Encrypt 2022 C++ Edition - Sample Project
 *
 * This sample project demonstrates the usage of IPWorks Encrypt in a 
 * simple, straightforward way. This is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * Copyright (c) 2023 /n software inc. www.nsoftware.com
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../include/ipworksencrypt.h"
#define LINE_LEN 100
#define MESSAGE_LEN 1024

class MyKeyMgr : public KeyMgr 
{
public:
  virtual int FireKeyList(KeyMgrKeyListEventParams *e) 
  {
    printf("%-58s %-8s %-12s\n", e->UserId, e->KeyId, e->HasSecretKey ? "private" : "");  
    return 0;
  }
};

int main(int argc, char **argv)
{
	OpenPGP pgp;
  MyKeyMgr keymgr;
	int ret_code = 0;
  char command[LINE_LEN];     // user's command
  char keyringDir[LINE_LEN];
  char passphrase[LINE_LEN];
  char privateKey[LINE_LEN];
  char recipientKey[LINE_LEN];
  char signerKey[LINE_LEN];

	printf("Keyring Directory: ");
	fgets(keyringDir, LINE_LEN, stdin);
	keyringDir[strlen(keyringDir)-1] = '\0';
  keymgr.LoadKeyring(keyringDir);

  printf("Create a new key? (y/n) ");
	fgets(command, LINE_LEN, stdin);
	command[strlen(command)-1] = '\0';
	if (tolower(command[0]) == 'y') 
  {
    while (1) 
    {
      printf("\nListing Keys...\n");
      printf("%-58s %-8s %-12s\n", "User Id", "Key Id", "Private Key"); 
      keymgr.ListKeys();
      printf("\nPlease enter a command: (c: create key, d: delete key, s: save keyring, q: cancel) ");
	    fgets(command, LINE_LEN, stdin);
	    command[strlen(command)-1] = '\0';
      if (tolower(command[0]) == 'c') 
      {
        char userid[LINE_LEN];
        printf("User Id: ");
	      fgets(userid, LINE_LEN, stdin);
	      userid[strlen(userid)-1] = '\0';
        printf("Passphrase: ");
	      fgets(passphrase, LINE_LEN, stdin);
	      passphrase[strlen(passphrase)-1] = '\0';
        ret_code = keymgr.CreateKey(userid, passphrase);
        if (ret_code) goto done;
      } 
      else if (tolower(command[0]) == 'd') 
      {
        char userid[LINE_LEN];
        printf("User Id: ");
	      fgets(userid, LINE_LEN, stdin);
	      userid[strlen(userid)-1] = '\0';
        ret_code = keymgr.DeleteKey(userid);
        if (ret_code) goto done;
      }
      else if (tolower(command[0]) == 's') 
      {
        ret_code = keymgr.SaveKeyring(keyringDir);
        if (ret_code) goto done;
        break;
      }
      else if (tolower(command[0]) == 'q') 
      {
        break;
      }
      else 
      {
        printf("Invalid command.");
      }
    }
  }
  
  printf("\nListing Keys...\n");
  printf("%-58s %-8s %-12s\n", "User Id", "Key Id", "Private Key"); 
  keymgr.ListKeys();

  printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
	fgets(privateKey, LINE_LEN, stdin);
	privateKey[strlen(privateKey)-1] = '\0';
  printf("Passphrase: ");
	fgets(passphrase, LINE_LEN, stdin);
	passphrase[strlen(passphrase)-1] = '\0';
  printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
	fgets(recipientKey, LINE_LEN, stdin);
	recipientKey[strlen(recipientKey)-1] = '\0';
  printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
	fgets(signerKey, LINE_LEN, stdin);
	signerKey[strlen(signerKey)-1] = '\0';

  while (1) 
  {
    printf("Please enter a command: (0: quit, 1: encrypt, 2: decrypt, 3: sign, 4: verify, 5: sign and encrypt, 6: decrypt and verify) ");
	  fgets(command, LINE_LEN, stdin);
	  command[strlen(command)-1] = '\0';
    int cmd = atoi(command);

    if (cmd < 0 || cmd > 6) 
    {
      printf("Invalid Command.\n");
      continue;
    }
    if (cmd == 0) 
      break;

    pgp.Reset();
    
    printf("Read from file or string? (f/s) ");
	  fgets(command, LINE_LEN, stdin);
	  command[strlen(command)-1] = '\0';
    if (tolower(command[0]) == 'f') 
    {
      printf("Input File: ");
	    fgets(command, LINE_LEN, stdin);
	    command[strlen(command)-1] = '\0';
      pgp.SetInputFile(command);

      printf("Output File: ");
	    fgets(command, LINE_LEN, stdin);
	    command[strlen(command)-1] = '\0';
      pgp.SetOutputFile(command);
            
      printf("Overwrite file? (y/n) ");
	    fgets(command, LINE_LEN, stdin);
	    command[strlen(command)-1] = '\0';
      pgp.SetOverwrite(tolower(command[0]) == 'y');
    }
    else 
    {
      printf("Please enter the message. When finished enter \":q\" on a line by itself:\n");
      char message[MESSAGE_LEN];
	    message[0] = '\0';
	    while(fgets(command, LINE_LEN, stdin))
	    {
		    command[strlen(command)-1] = '\0';
		    if (strcmp(command, ":q") == 0)
			    break;
		    strcat(message, command);
		    strcat(message, "\n");
	    }
      pgp.SetInputMessage(message, strlen(message));
    }

    if (cmd == 1) //Encrypt
    {
      if (strlen(recipientKey) <= 0) 
      {
        printf("Please select a recipient key.\n");
        break;
      }
      pgp.SetASCIIArmor(true);
      pgp.SetRecipientKeyCount(1);
      pgp.SetRecipientKeyKeyring(0, keyringDir);
      pgp.SetRecipientKeyUserId(0, recipientKey);
      ret_code = pgp.Encrypt();
      if (ret_code) goto done;

      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nEncrypted Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
    else if (cmd == 2) //Decrypt
    {
      if (strlen(privateKey) <= 0) 
      {
        printf("Please select a private key.\n");
        break;
      }

      pgp.SetKeyCount(1);
      pgp.SetKeyKeyring(0, keyringDir);
      pgp.SetKeyUserId(0, privateKey);
      pgp.SetKeyPassphrase(0, passphrase);
      ret_code = pgp.Decrypt();
      if (ret_code) goto done;
      
      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nDecrypted Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
    else if (cmd == 3) //Sign
    {
      if (strlen(privateKey) <= 0) 
      {
        printf("Please select a private key.\n");
        break;
      }

      pgp.SetASCIIArmor(true);
      pgp.SetKeyCount(1);
      pgp.SetKeyKeyring(0, keyringDir);
      pgp.SetKeyUserId(0, privateKey);
      pgp.SetKeyPassphrase(0, passphrase);
      ret_code = pgp.Sign();
      if (ret_code) goto done;
      
      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nSigned Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
    else if (cmd == 4) //Verify
    {
      if (strlen(signerKey) <= 0) 
      {
        printf("Please select a signer key.\n");
        break;
      }

      pgp.SetSignerKeyCount(1);
      pgp.SetSignerKeyKeyring(0, keyringDir);
      pgp.SetSignerKeyUserId(0, signerKey);
      ret_code = pgp.VerifySignature();
      if (ret_code) goto done;
      
      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nVerified Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
    else if (cmd == 5) //Sign and Encrypt
    {
      if (strlen(privateKey) <= 0) 
      {
        printf("Please select a private key.\n");
        break;
      }
      if (strlen(recipientKey) <= 0) 
      {
        printf("Please select a recipient key.\n");
        break;
      }
      if (strlen(signerKey) <= 0) 
      {
        printf("Please select a signer key.\n");
        break;
      }

      pgp.SetASCIIArmor(true);
      pgp.SetKeyCount(1);
      pgp.SetKeyKeyring(0, keyringDir);
      pgp.SetKeyUserId(0, privateKey);
      pgp.SetKeyPassphrase(0, passphrase);
      pgp.SetRecipientKeyCount(1);
      pgp.SetRecipientKeyKeyring(0, keyringDir);
      pgp.SetRecipientKeyUserId(0, recipientKey);
      ret_code = pgp.SignAndEncrypt();
      if (ret_code) goto done;
      
      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nSigned & Encrypted Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
    else if (cmd == 6) //Decrypt and Verify
    {
      if (strlen(privateKey) <= 0) 
      {
        printf("Please select a private key.\n");
        break;
      }

      pgp.SetKeyCount(1);
      pgp.SetKeyKeyring(0, keyringDir);
      pgp.SetKeyUserId(0, privateKey);
      pgp.SetKeyPassphrase(0, passphrase);       
      pgp.SetSignerKeyCount(1);
      pgp.SetSignerKeyKeyring(0, keyringDir);
      pgp.SetSignerKeyUserId(0, signerKey);
      ret_code = pgp.DecryptAndVerifySignature();
      if (ret_code) goto done;
      
      if (strlen(pgp.GetOutputFile()) <= 0) 
      {
        printf("\nDecrypted & Verified Message:\n");
        char* output;
        int len;
        pgp.GetOutputMessage(output, len);
        printf("%s\n", output);
      }
    }
  }

done:
	if (ret_code)     // Got an error.  The user is done.
	{
		printf( "\nError: %d", ret_code );
		if (pgp.GetLastError())
		{
			printf( " \"%s\"\n", pgp.GetLastError() );
		}
	}

	fprintf(stderr, "\npress <return> to continue...\n");
	getchar();
	exit(ret_code);
	return 0;
}



