/*
 * IPWorks Encrypt 2022 C++ Edition - Demo Application
 *
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/ipworksencrypt.h"

void displayHelp(char *message) {
	printf("Invalid arguments entered. ");
	printf("%s", message);
	printf("\nUsage: jws.exe action algorithm key input [keyPassword]");
	printf("\n\taction          the action to perform - 'sign' or 'verify'");
	printf(
		"\n\talgorithm       the HMAC or RSA algorithm - 'HS256', 'HS384', 'HS512', 'RS256', 'RS384', 'RS512', 'PS256', 'PS384', or 'PS512'");
	printf(
		"\n\tkey             HMAC - Base64 key or '0' to generate key; RSA - filename of key certificate (private cert for sign, public cert for verify)");
	printf("\n\tinput           the payload string to sign or JWS string to verify");
	printf(
		"\n\tkeyPassword     key certificate password if necessary (required only for private certificates with passwords)");
	printf("\nExamples: jws.exe sign HS256 txAVam2uGT20a+ZJC1VWVGCM8tFYSKyJlw+2fgS/BdA= \"Test message\"");
	printf("\n          jws.exe sign HS512 0 \"Test message\"");
	printf("\n          jws.exe sign RS384 .\\testrsapriv.pfx \"Test message\" test");
	printf("\n          jws.exe sign ES256 .\\testeccpriv.txt \"Test message\"");
	printf(
		"\n          jws.exe verify HS256 ygIg4/Ut0KwUK2nS6fnflj1C5pAhgiXmVzqRqR2WTyU= eyJhbGciOiJIUzI1NiJ9.SGVsbG8.Deg4sWY8OL1pbXh6zVy7Wkr2brjVUrMBrIzeY5WlxM4");
	printf(
		"\n          jws.exe verify PS256 .\\testrsapub.cer eyJhbGciOiJQUzI1NiJ9.SGVsbG8.AqVXRmp7nmy74WQSoFrpY-Y4flb60n2e_XTjl51t0P1l-BqSCFj79wfaNf9-MJxCYbHkuFPjwkBq9-vvzxse0V-Bd0cjlXA9RY-LRn_wRHXRZUqParsZhsvWSqHY8MC4xAkXWCJuiDPWIuvDnd8mJDr_7vVbjIRipfifPkMMn3ePSvRSXWSBobalZxM320sYhReDgCZi5Mjb21cMSdowWj048AXFM86yL50UTh5rl2op3dG5JB9JbqBwVPDybdG7TK9r_84LYAajbTF7MepyMGWMAP7oSV1G-zBnBqpUC-HpTMRC-9xt9G3H0t1lUPePOBwB5ZdMeABrkFOSTwcIbQ");
	printf("\n          jws.exe verify ES512 .\\testeccpub.txt eyJhbGciOiJFUzI1NiJ9.SGVsbG8.uGClu2T59y6gi5GBmkLNOsXTa8F_uxxo0mSo7nZ9wbisOuFrjkXnVL-_j9L2uRe7vhrOqfxRcQFoEwR9Empx8g");
}

int getNewKey(char *&newKey, int &lenRandBytes, char *alg) {
		// Generate key
		EzRand ezrand;
		if (strcmp(alg, "HS256")==0) {
			lenRandBytes = 32;
		}
		else if (strcmp(alg, "HS384")==0) {
			lenRandBytes = 48;
		}
		else if (strcmp(alg, "HS512")==0) {
			lenRandBytes = 64;
		}
		else {
			printf("Error: HMAC algorithm must be selected to generate HMAC key.");
			return 1;
		}
		ezrand.SetRandBytesLength(lenRandBytes);
		ezrand.GetNextBytes();
		ezrand.GetRandBytes(newKey, lenRandBytes);
}

int sign(char *alg, char *key, char *message, char *password) {
	JWS jws;
	int ret_code = 0;
	if (strcmp(alg, "HS256")==0) {
		jws.SetAlgorithm(JWS_HS256);
		if (strcmp(key, "0") == 0) {
			char *newKey;
			int lenRandBytes;
			getNewKey(newKey, lenRandBytes, alg);
			jws.SetKey(newKey, lenRandBytes);
		}
		else {
			jws.Config("KeyEncoding=1"); //Base64 input
			jws.SetKey(key, strlen(key));
		}		
	} else if (strcmp(alg, "HS384")==0) {
		jws.SetAlgorithm(JWS_HS384);
		if (strcmp(key, "0") == 0) {
			char *newKey;
			int lenRandBytes;
			getNewKey(newKey, lenRandBytes, alg);
			jws.SetKey(newKey, lenRandBytes);
		}
		else {
			jws.Config("KeyEncoding=1"); //Base64 input
			jws.SetKey(key, strlen(key));
		}
	}
	else if(strcmp(alg, "HS512")==0) {
		jws.SetAlgorithm(JWS_HS512);
		if (strcmp(key, "0") == 0) {
			char *newKey;
			int lenRandBytes;
			getNewKey(newKey, lenRandBytes, alg);
			jws.SetKey(newKey, lenRandBytes);
		}
		else {
			jws.Config("KeyEncoding=1");
			jws.SetKey(key, strlen(key));
		}
	}
	else if (strcmp(alg, "RS256")==0) {
		jws.SetAlgorithm(JWS_RS256);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "RS384")==0) {
		jws.SetAlgorithm(JWS_RS384);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "RS512")==0) {
		jws.SetAlgorithm(JWS_RS512);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "PS256")==0) {
		jws.SetAlgorithm(JWS_PS256);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "PS384")==0) {
		jws.SetAlgorithm(JWS_PS384);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "PS512")==0) {
		jws.SetAlgorithm(JWS_PS512);
		jws.SetCertStoreType(CST_PFXFILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "ES256")==0) {
		jws.SetAlgorithm(JWS_ES256);
		jws.SetCertStoreType(CST_PEMKEY_FILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "ES384")==0) {
		jws.SetAlgorithm(JWS_ES384);
		jws.SetCertStoreType(CST_PEMKEY_FILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "ES512")==0) {
		jws.SetAlgorithm(JWS_ES512);
		jws.SetCertStoreType(CST_PEMKEY_FILE);
		jws.SetCertStore(key, strlen(key));
		jws.SetCertStorePassword(password);
		ret_code = jws.SetCertSubject("*");
	}
	else {
		printf("Unsupported algorithm inputted.");
		return 1;
	}
	if (ret_code) {
		return ret_code;
	}
	jws.SetInputMessage(message, strlen(message));
	ret_code = jws.Sign();
	if (ret_code) {
		return ret_code;
	}
	char *output;
	int lenOut;
	jws.GetOutputMessage(output, lenOut);
	printf("Payload signed:\n%s", output);
	return ret_code;
}

int verify(char *alg, char *key, char *payload) {
	JWS jws;
	int ret_code = 0;
	if (strcmp(alg, "HS256") == 0 || strcmp(alg, "HS384") == 0 || strcmp(alg, "HS512") == 0) {
		jws.Config("KeyEncoding=1");
		ret_code = jws.SetKey(key, strlen(key));
	}
	else if (strcmp(alg, "RS256") == 0 || strcmp(alg, "RS384") == 0 || strcmp(alg, "RS512") == 0 || strcmp(alg, "PS256") == 0 || strcmp(alg, "PS384") == 0 || strcmp(alg, "PS512") == 0) {
		jws.SetCertStoreType(CST_PEMKEY_FILE);
		jws.SetCertStore(key, strlen(key));
		ret_code = jws.SetCertSubject("*");
	}
	else if (strcmp(alg, "ES256") == 0 || strcmp(alg, "ES384") == 0 || strcmp(alg, "ES512") == 0) {
		jws.SetCertStoreType(CST_PUBLIC_KEY_FILE);
		jws.SetCertStore(key, strlen(key));
		ret_code = jws.SetCertSubject("*");
	}
	else {
		printf("Unsupported algorithm inputted.");
		return 1;
	}
	if (ret_code) {
		return ret_code;
	}
	jws.SetInputMessage(payload, strlen(payload));
	ret_code = jws.Verify();
	if (ret_code) {
		return ret_code;
	}
	char *output;
	int lenOut;
	jws.GetOutputMessage(output, lenOut);
	printf("JWS string verified:\n%s", output);
	return ret_code;
}

int main(int argc, char **argv)
{
	int ret_code = 0;
	if (argc == 5 || argc == 6) {
		if (strcmp(argv[1],"sign")==0) {
			if (argc == 6) {
				ret_code = sign(argv[2], argv[3], argv[4], argv[5]);
			}
			else { // length == 5
				 ret_code = sign(argv[2], argv[3], argv[4], ""); // no password
			}
		}
		else if (strcmp(argv[1], "verify")==0) {
			ret_code = verify(argv[2], argv[3], argv[4]);
		}
		else {
			displayHelp("First argument must be either 'sign' or 'verify'.");
		}
	}
	else {
		displayHelp("5 or 6 arguments expected.");
	}
	if (ret_code) {
		printf("Error: %d", ret_code);
	}

	printf("\n\nPress any key to continue...");
	getchar();

	return ret_code;
}




