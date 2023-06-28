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

int main(int argc, char **argv)
{
	
  int ret_code = 0;
  char algorithm[LINE_LEN];
  char minValue[LINE_LEN];
  char maxValue[LINE_LEN];
  char seed[LINE_LEN];
  char bytesLen[LINE_LEN];
  char command[LINE_LEN];
  
  EzRand ezrand;

  printf("*****************************************************************************\n");
  printf("* This demo show how to get random numbers and bytes using algorithms like  *\n");
  printf("* ISAAC, MS Crypto API, etc.                                                *\n");
  printf("*****************************************************************************\n");

  while (true)
  {
    printf("\nSpecify an algorithm:\n");
    printf("1) ISAAC \n");
    printf("2) MS Crypto API \n");
    printf("3) Platform \n");
    printf("\nAlgorithm: ");
    fgets(algorithm, LINE_LEN, stdin);
    algorithm[strlen(algorithm)-1] = '\0';
    switch(atoi(algorithm)) 
    {
    case 1 : 
      ezrand.SetAlgorithm(RA_ISAAC);
      break;
    case 2 :
      ezrand.SetAlgorithm(RA_MSCRYPTO_API);
      break;
    case 3 :
      ezrand.SetAlgorithm(RA_PLATFORM);
      break;
    default :
      printf("\nInvalid algorithm.");
      continue;
    }

  ask:
    printf("\nGet random Integers(i) or Bytes(b)? ");
    fgets(command, LINE_LEN, stdin);

    if (tolower(command[0]) == 'i') //int
    {
      printf("\nMin Value [0]: ");
      fgets(minValue, LINE_LEN, stdin);
      minValue[strlen(minValue)-1] = '\0';
      if (strlen(minValue) == 0) strcat(minValue,"0");
      ret_code = ezrand.SetMin(atoi(minValue));
      if (ret_code) goto done;

      printf("\nMax Value [100]: ");
      fgets(maxValue, LINE_LEN, stdin);
      maxValue[strlen(maxValue)-1] = '\0';
      if (strlen(maxValue) == 0) strcat(maxValue,"100");
      ret_code = ezrand.SetMax(atoi(maxValue));
      if (ret_code) goto done;

      printf("Seed: ");
      fgets(seed, LINE_LEN, stdin);
      seed[strlen(seed)-1] = '\0';
      ret_code = ezrand.SetSeed(seed, strlen(seed));
      if (ret_code) goto done;

      printf("\nGetting random integers...\n");
      printf("Press <enter> to get next int or q to quit\n\n");

      do
      {
        ret_code = ezrand.GetNextInt();
        if (ret_code) goto done;
        
        printf("%d\n", ezrand.GetRandInt());
      } while (tolower(fgets(command, LINE_LEN, stdin)[0]) != 'q'); 
    }
    else if (tolower(command[0]) == 'b') //byte
    {
      printf("\nBytes Length [16]: ");
      fgets(bytesLen, LINE_LEN, stdin);
      bytesLen[strlen(bytesLen)-1] = '\0';
      if (strlen(bytesLen) == 0) strcat(bytesLen,"16");
      ret_code = ezrand.SetRandBytesLength(atoi(bytesLen));
      if (ret_code) goto done;

      printf("Seed: ");
      fgets(seed, LINE_LEN, stdin);
      seed[strlen(seed)-1] = '\0';
      ret_code = ezrand.SetSeed(seed, strlen(seed));
      if (ret_code) goto done;

      printf("\nGetting %d random bytes...\n", ezrand.GetRandBytesLength());
      printf("Press <enter> to get next bytes or q to quit\n\n");

      do 
      {
        ret_code = ezrand.GetNextBytes();
        if (ret_code) goto done;

        char *randBytes;
        int len;
        ret_code = ezrand.GetRandBytes(randBytes, len);
        if (ret_code) goto done;

        for (int i = 0; i < len; i++) 
        {
          printf("%02X ", (unsigned char)randBytes[i]);
        }
        printf("\n");
      } while (tolower(fgets(command, LINE_LEN, stdin)[0]) != 'q');
    }
    else {
      printf("Invalid Option");
      continue;
    }

    printf("\nDo you wish to generate another set of random integers or bytes? (y/n) ");
    if (tolower(fgets(command, LINE_LEN, stdin)[0] != 'y')) 
      break;
  }

done: 
  if (ret_code) // Got an error.  The user is done.
  {
    printf("\nError %d", ret_code);
    if (strlen(ezrand.GetLastError()) > 0) 
      printf(": %s\n", ezrand.GetLastError());
  }

	fprintf(stderr, "\n\npress <return> to continue...");
	getchar();
	exit(ret_code);
	return 0;
}

