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
#include "../../include/ipworksencrypt.h"
#define LINE_LEN 100
#define MESSAGE_LEN 1024

int main(int argc, char **argv)
{
	
  int ret_code = 0;
  char algorithm[LINE_LEN];
  char inputFile[LINE_LEN];
  char outputFile[LINE_LEN];
  char operation[LINE_LEN];
  char password[LINE_LEN];
  
  EzCrypt ezcrypt;

  printf("******************************************************************************\n");
  printf("* This demo show how to encrypt and decrypt files using symmetric algorithms *\n");
  printf("* like AES, DES, 3DES, etc. The components can also be used to encrypt and   *\n");
  printf("* decrypt in memory.                                                         *\n");
  printf("******************************************************************************\n");

  printf("Specify an algorithm:\n");
  printf("1) AES \n");
  printf("2) CAST \n");
  printf("3) DES \n");
  printf("4) IDEA \n");
  printf("5) RC2 \n");
  printf("6) RC4 \n");
  printf("7) TripleDES \n");
  printf("8) Blowfish \n");
  printf("9) Twofish \n");
  printf("\nAlgorithm: ");
  fgets(algorithm, LINE_LEN, stdin);
  algorithm[strlen(algorithm)-1] = '\0';

  printf("\nSelect an operation:\n");
  printf("1) Encrypt\n");
  printf("2) Decrypt\n");
  printf("\nOperation: ");
  fgets(operation, LINE_LEN, stdin);
  operation[strlen(operation)-1] = '\0';
  
  // A key password is used to generate the Key and IV.
  // When using a key password you only need to save this value.
  // This makes key management much simpler.
  printf("\nPassword: ");
  fgets(password, LINE_LEN, stdin);
  password[strlen(password)-1] = '\0';

  printf("Input File: ");
  fgets(inputFile, LINE_LEN, stdin);
  inputFile[strlen(inputFile)-1] = '\0';

  printf("Output File: ");
  fgets(outputFile, LINE_LEN, stdin);
  outputFile[strlen(outputFile)-1] = '\0';

  int cmd = atoi(algorithm);
  switch(cmd)
  {
  case 1: // AES
    ezcrypt.SetAlgorithm(EZ_AES);
    break;
  case 2: // CAST
    ezcrypt.SetAlgorithm(EZ_CAST);
    break;
  case 3: // DES
    ezcrypt.SetAlgorithm(EZ_DES);
    break;
  case 4: // IDEA
    ezcrypt.SetAlgorithm(EZ_IDEA);
    break;
  case 5: // Rc2
    ezcrypt.SetAlgorithm(EZ_RC2);
    break;
  case 6: // Rc4
    ezcrypt.SetAlgorithm(EZ_RC4);
    break;
  case 7: // TripleDES
    ezcrypt.SetAlgorithm(EZ_TRIPLE_DES);
    break;
  case 8: // Blowfish
    ezcrypt.SetAlgorithm(EZ_BLOWFISH);
    break;
  case 9: // Twofish
    ezcrypt.SetAlgorithm(EZ_TWOFISH);
    break;
  default:
    ret_code = 0;
    printf("\nInvalid algorithm.");
    break;
  }

  int op = atoi(operation);
  if (op == 1) // Encrypt
  {
    ezcrypt.SetInputFile(inputFile);
    ezcrypt.SetOutputFile(outputFile);
    ezcrypt.SetKeyPassword(password);
    ret_code = ezcrypt.Encrypt();
    if (ret_code) // Got an error.
    {
	    printf( "\nError: %d", ret_code );
	    printf( " \"%s\"\n", ezcrypt.GetLastError());
	  }
    else
    {
      printf("\nEncryption successful!");
    }
  } 
  else if (op == 2) // Decrypt
  {
    ezcrypt.SetInputFile(inputFile);
    ezcrypt.SetOutputFile(outputFile);
    ezcrypt.SetKeyPassword(password);
    ret_code = ezcrypt.Decrypt();
    if (ret_code) // Got an error.
    {
	    printf( "\nError: %d", ret_code );
	    printf( " \"%s\"\n", ezcrypt.GetLastError());
	  }
    else
    {
      printf("\nDecryption successful!");
    }
  } 
  else 
  {
    printf("\nInvalid operation specified.");
  }

	fprintf(stderr, "\n\npress <return> to continue...");
	getchar();
	exit(ret_code);
	return 0;
}












