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
#include <stdlib.h>
#include <cstring>
#include "../../include/ipworksencrypt.h"
#define LINE_LEN 100
#define MESSAGE_LEN 1024

int main(int argc, char **argv)
{
  
  int ret_code = 0;
  Hash hash1;
  char algorithm[LINE_LEN];
  char command[LINE_LEN];
  char encodeHash[LINE_LEN];
  char inputSource[LINE_LEN];
  char inputFile[LINE_LEN];
  char inputString[MESSAGE_LEN];

  printf("******************************************************************************\n");
  printf("* This demo show how to hash a file or string using a variety of algorithms  *\n");
  printf("******************************************************************************\n");

  while (1) 
  {
    printf("Specify an algorithm:\n");
    printf("0)  SHA1 \n");
    printf("1)  SHA-224 \n");
    printf("2)  SHA-256 \n");
    printf("3)  SHA-384 \n");
    printf("4)  SHA-512 \n");
    printf("5)  MD2 \n");
    printf("6)  MD4 \n");
    printf("7)  MD5 \n");
    printf("8)  RIPEMD-160 \n");
    printf("9)  MD5SHA1 \n");
    printf("10) HMAC-MD5 \n");
    printf("11) HMAC-SHA1 \n");
    printf("12) HMAC-SHA224 \n");
    printf("13) HMAC-SHA256 \n");
    printf("14) HMAC-SHA384 \n");
    printf("15) HMAC-SHA512 \n");
    printf("16) HMAC-RIPEMD160 \n");
    printf("17) SHA-3-224 \n");
    printf("18) SHA-3-256 \n");
    printf("19) SHA-3-384 \n");
    printf("20) SHA-3-512 \n");
    printf("\nAlgorithm: ");
    fgets(algorithm, LINE_LEN, stdin);
    algorithm[strlen(algorithm)-1] = '\0';
    hash1.SetAlgorithm(atoi(algorithm));
  
    printf("\nSelect if hash value should be hex encoded:\n");
    printf("0) False\n");
    printf("1) True\n");
    printf("Hex Encode Hash Value: ");
    fgets(encodeHash, LINE_LEN, stdin);
    encodeHash[strlen(encodeHash)-1] = '\0';
    hash1.SetEncodeHash(atoi(encodeHash));

    printf("\nSelect an input source:\n");
    printf("0) String\n");
    printf("1) File\n");
    printf("\nInput Source: ");
    fgets(inputSource, LINE_LEN, stdin);
    inputSource[strlen(inputSource)-1] = '\0';

    int input = atoi(inputSource);
    if (input == 0) //String 
    {    
      printf("Enter the message. To end the message, enter \":q\" on a single line by itself.\n");
      printf("\nInput String:\n");
      inputString[0] = '\0';
      while(fgets(command, LINE_LEN, stdin))
      {
        if (strcmp(command, ":q\n") == 0)
          break;
        strcat(inputString, command);
      }
      hash1.SetInputMessage(inputString, strlen(inputString));
    }
    else 
    {
      printf("Input File: ");
      fgets(inputFile, LINE_LEN, stdin);
      inputFile[strlen(inputFile)-1] = '\0';
      hash1.SetInputFile(inputFile);
    }
    
    printf("\nComputing Hash....\n");
    ret_code = hash1.ComputeHash();
    if (ret_code) goto done;
    char *hashValue;
    int len;
    hash1.GetHashValue(hashValue, len);
    printf("\nHash Value: %s\n", hashValue);
    
    printf("\nDo you wish to hash another message (y/n)? ");
    fgets(command, LINE_LEN, stdin);
    command[strlen(command)-1] = '\0';
    if (strcmp("y", command) != 0 && strcmp("Y", command) != 0)
      break;
  }

done:
  if (ret_code) 
  {
    printf("Error %d: %s\n", hash1.GetLastErrorCode(), hash1.GetLastError());
  }

  fprintf(stderr, "\n\npress <return> to continue...");
  getchar();
  exit(ret_code);
  return 0;
}















