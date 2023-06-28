/*
 * IPWorks Encrypt 2022 C++ Edition - Sample Project
 *
 * This sample project demonstrates the usage of IPWorks Encrypt in a 
 * simple, straightforward way. This is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * Copyright (c) 2023 /n software inc. www.nsoftware.com
 */

#include "../../include/ipworksencrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LEN 100




class MyCertMgr : public CertMgr
{
public:

	MyCertMgr()
	{
		numCerts = 0;
	}
	virtual int FireCertList(CertMgrCertListEventParams *e)
	{
		sprintf(certs[numCerts++], "%s", e->CertSubject);
		return 0;
	}
	virtual int FireError(CertMgrErrorEventParams *e)
	{
		printf ("%i: %s\n", e->ErrorCode, e->Description);
		return 0;
	}
	char certs[100][500];				// storage for 100 cert subjects
	int numCerts;						// number of cert subjects stored in certs[]
};

MyCertMgr CertMgr1;	// global
SMIME			smime;		// global
bool quit = false;

int SelCert()
{

	char myBuf[150];
	*myBuf = 0;
	fflush(stdin);

	CertMgr1.numCerts = 0;
	CertMgr1.SetCertStore("MY", 2);
	CertMgr1.ListStoreCertificates();

	for (int i=0; i<CertMgr1.numCerts; i++)
	{
		printf("%i) %s\n", i, CertMgr1.certs[i]);
	}
	printf("Please select a valid certificate. ");
	fgets(myBuf,LINE_LEN,stdin);
	myBuf[strlen(myBuf)-1] = '\0';

	CertMgr1.SetCertSubject(CertMgr1.certs[atoi(myBuf)]);
	return 0;
}



int Sign()
{
	char* certStore;
	int certStoreLength;
	SelCert();
	//smime.SetCertHandle(CertMgr1.GetCertHandle());
	smime.SetCertSubject(CertMgr1.GetCertSubject());
	CertMgr1.GetCertStore(certStore, certStoreLength);
	smime.SetCertStore(certStore, certStoreLength);
	smime.SetDetachedSignature(true);
	smime.SetIncludeCertificate(true);
	return smime.Sign();

}

int Encrypt()
{

	char* mycert;
	unsigned int len = 0;
	SelCert();
	CertMgr1.GetCertEncoded(mycert, (int &)len);
	smime.AddRecipientCert(mycert, len);
	return smime.Encrypt();

}

int SignAndEncrypt()
{
	char* certStore;
	int certStoreLength;
	char * mycert;
	unsigned int len = 0;
	SelCert();															// cert to sign message with
	smime.SetCertSubject(CertMgr1.GetCertSubject());
	CertMgr1.GetCertStore(certStore, certStoreLength);
	smime.SetCertStore(certStore, certStoreLength);
	smime.SetDetachedSignature(true);
	smime.SetIncludeCertificate(true);
	printf("\n");
	SelCert();															// cert to encrypt message with
	CertMgr1.GetCertEncoded(mycert, (int &)len);
	smime.AddRecipientCert(mycert, len);
	return smime.SignAndEncrypt();

}

int Verify()
{

	int ret_code = smime.VerifySignature();
	if(ret_code) {
		printf("Verify error!!\n");
		return ret_code;
	}

	printf("Verify OK.\n");
	printf("Subject: %s\n"
	       "Issuer:  %s\n"
	       "Serial#: %s\n",
	       smime.GetSignerCertSubject(),
	       smime.GetSignerCertIssuer(),
	       smime.GetSignerCertSerialNumber());
	printf("Press a key to continue.\n");
	getchar();
	return 0;
}

int Decrypt()
{
	int ret_code = smime.Decrypt();
	if(ret_code) {
		printf("Decrypt error\n");
		return ret_code;
	}
	printf("Decrypt OK\n");

	char* p;
	int len = 0;
	smime.GetOutputMessage(p, len);
	printf("%s\n", p);

	return ret_code;
}

int VerifyAndDecrypt()
{

	int ret_code =  smime.DecryptAndVerifySignature();
	if(ret_code) {
		printf("DecryptAndVerifySignature error\n");
		return ret_code;
	}
	printf("DecryptAndVerifySignature OK\n");	

	printf("Subject: %s\n"
	       "Issuer:  %s\n"
	       "Serial#: %s\n",
	       smime.GetSignerCertSubject(),
	       smime.GetSignerCertIssuer(),
	       smime.GetSignerCertSerialNumber());
	printf("Press a key to continue.\n");
	getchar();
	return 0;

}
int SelectEncoding()
{

	char ch;
	printf("\nEncoding choices:\n"
	       "  1) Sign message\n"
	       "  2) Encrypt message\n"
	       "  3) Sign and encrypt message\n"
	       "  4) Verify Signature\n"
	       "  5) Decrypt\n"
	       "  6) Verify and Decrypt\n"
	       "  0) Quit\n");
	ch = getchar();
	fflush(stdin);
	switch(ch)
	{
		case '1': {
			int ret_code  = Sign();
			char* p;
			int len = 0;
			smime.GetOutputMessage(p, len);
			char* h = smime.GetOutputMessageHeadersString();
			return ret_code;
		}
		case '2':
			return Encrypt();
		case '3':
			return SignAndEncrypt();
		case '4':
		{
			char* p;
			int len = 0;
			smime.GetOutputMessage(p, len);
			char* h = smime.GetOutputMessageHeadersString();
			smime.SetInputMessage(p, len);
			smime.SetInputMessageHeadersString(h);
			return Verify();
		}
		case '5': {
			char* p;
			int len = 0;
			smime.GetOutputMessage(p, len);
			char* h = smime.GetOutputMessageHeadersString();
			smime.SetInputMessage(p, len);
			smime.SetInputMessageHeadersString(h);
			return Decrypt();
		}
		case '6': {
			char* p;
			int len = 0;
			smime.GetOutputMessage(p, len);
			char* h = smime.GetOutputMessageHeadersString();
			smime.SetInputMessage(p, len);
			smime.SetInputMessageHeadersString(h);
			return VerifyAndDecrypt();
		}
		case '0':
			quit = true;
		default:
			break;
	}

	return 0;
}


int main()
{
	char buffer[LINE_LEN+1];
	char * ptr;
	unsigned int  len = 0;

	printf("Enter message text to be encoded:\n\n");
	fgets(buffer,LINE_LEN,stdin);
	buffer[strlen(buffer)-1] = '\0';
	smime.SetInputMessage(buffer, strlen(buffer));
	quit = false;
	while (!quit)
	{
		SelectEncoding();
		smime.GetOutputMessage(ptr, (int &)len);
		printf("\n%*s\n", len, ptr);
	}

}



