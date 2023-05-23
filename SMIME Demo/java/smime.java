/*
 * IPWorks Encrypt 2022 Java Edition- Demo Application
 *
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 *
 */

import java.io.*;

import java.util.*;

import ipworksencrypt.*;

public class smime extends ConsoleDemo {
  boolean quit;
  Smime smime1;
  Certmgr certmgr;
  String buffer;
  int index;
  Vector<String> al;

  public smime() {
    al = new Vector<String>();
    smime1 = new Smime();
    certmgr = new Certmgr();
    try {

      certmgr.addCertmgrEventListener(new CertMgrEvents(this));
      smime1.setInputMessage(prompt("Please enter message text to be encoded", ":", "hello world"));
      quit = false;
      while (!quit) {
        index = 0;
        selectEncoding();
        System.out.println("Encoded message: \r\n"
            + smime1.getOutputMessageHeadersString() + "\r\n\r\n"
            + new String(smime1.getOutputMessage()));
      }
    } catch (IPWorksEncryptException ex) {
      System.out.println("IPWorks exception thrown: " + ex.getCode()
          + " [" + ex.getMessage() + "].");
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
    }
  }

  public void selectEncoding() throws IOException, IPWorksEncryptException {
    char ch;
    System.out.println("\nEncoding choices:\n" + "  1) Sign message\n"
        + "  2) Encrypt message\n" + "  3) Sign and encrypt message\n"
        + "  4) Verify Signature\n" + "  5) Decrypt\n"
        + "  6) Verify and Decrypt\n" + "  0) Quit\n");
    ch = ConsoleDemo.input().charAt(0);

    switch (ch) {
      case '1':
        sign();
        break;
      case '2':
        encrypt();
        break;
      case '3':
        signAndEncrypt();
        break;
      case '4':
        verify();
        break;
      case '5':
        decrypt();
        break;
      case '6':
        decryptAndVerify();
        break;
      case '0':
        quit = true;
        break;
    }
  }

  private void sign() throws IPWorksEncryptException {
    System.out
        .println("Please select a certificate to sign the message with:");
    selectCertificate();
    smime1.setCertificate(certmgr.getCert());

    smime1.setDetachedSignature(true);
    smime1.setIncludeCertificate(true);
    smime1.sign();
  }

  private void encrypt() throws IPWorksEncryptException {
    System.out
        .println("Please select a certificate to encrypt the message with:");
    selectCertificate();
    smime1.addRecipientCert(certmgr.getCert().getEncoded());
    smime1.encrypt();
  }

  private void signAndEncrypt() throws IPWorksEncryptException {
    System.out
        .println("Please select a certificate to sign the message with:");
    selectCertificate();
    smime1.setCertificate(certmgr.getCert());
    smime1.setDetachedSignature(true);
    smime1.setIncludeCertificate(true);
    System.out
        .println("Please select a certificate to encrypt the message with:");
    selectCertificate();
    smime1.addRecipientCert(certmgr.getCert().getEncoded());
    smime1.signAndEncrypt();
  }

  private void verify() throws IPWorksEncryptException {
    // For the purpose of this demo, we assume the public key was included
    // in the signed message
    smime1.verifySignature();
    System.out.println("The message was signed with certificate: "
        + smime1.getSignerCert().getSubject());
  }

  private void decrypt() throws IPWorksEncryptException {
    System.out
        .println("Please select a certificate to decrypt the message with:");
    selectCertificate();
    smime1.setCertificate(certmgr.getCert());
    smime1.decrypt();
  }

  private void decryptAndVerify() throws IPWorksEncryptException {
    // For the purpose of this demo, we assume the public key was included
    // in the signed message
    System.out
        .println("Please select a certificate to decrypt the message with:");
    selectCertificate();
    smime1.setCertificate(certmgr.getCert());
    smime1.decryptAndVerifySignature();
    System.out.println("The message was signed with certificate: "
        + smime1.getSignerCert().getSubject());
  }

  private void selectCertificate() {
    try {
      certmgr.setCertStoreType(Certificate.cstJKSFile);
      certmgr.setCertStore(prompt("Please enter key store path", ":", "testcert.pfx"));
      certmgr.setCertStorePassword(prompt("Please enter store password", ":", "password"));
      System.out.println("Please select a certificate:");
      certmgr.listStoreCertificates();
      int selection = Integer.parseInt(ConsoleDemo.input());
      certmgr.setCert(new Certificate(Certificate.cstJKSFile, certmgr
          .getCertStore(), certmgr.getCertStorePassword(), al
          .get(selection - 1)));
    } catch (IPWorksEncryptException ex) {
      System.out.println("IPWorks exception thrown: " + ex.getCode()
          + " [" + ex.getMessage() + "].");
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
    }
  }

  public static void main(String[] args) {
    new smime();
  }

  public void certList(CertmgrCertListEvent args) {
    al.add(args.certSubject);
    index++;
    System.out.println(index + ". " + args.certSubject);
  }

  public void error(CertmgrErrorEvent args) {
    System.out.println("CertMgr error: " + args.errorCode + " ["
        + args.description + "].");
  }
}

class CertMgrEvents implements CertmgrEventListener {
  smime instance;

  public CertMgrEvents(smime instance) {
    this.instance = instance;
  }

  public void certChain(CertmgrCertChainEvent args) {

  }

  public void certList(CertmgrCertListEvent args) {
    instance.certList(args);
  }

  public void error(CertmgrErrorEvent args) {
    instance.error(args);
  }

  public void keyList(CertmgrKeyListEvent args) {

  }

  public void storeList(CertmgrStoreListEvent args) {

  }
  
  public void log(CertmgrLogEvent args){}
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




