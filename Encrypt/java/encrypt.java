/*
 * IPWorks Encrypt 2022 Java Edition - Sample Project
 *
 * This sample project demonstrates the usage of IPWorks Encrypt in a 
 * simple, straightforward way. This is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * Copyright (c) 2023 /n software inc. www.nsoftware.com
 */

import java.io.*;
import ipworksencrypt.*;

public class encrypt extends ConsoleDemo {

  public static void main(String[] args) {
    

    try {
      String algorithm = "";
      String inputFile = "";
      String outputFile = "";
      String operation = "";
      String password = "";
      Ezcrypt ezcrypt;
      
      System.out.println("******************************************************************************");
      System.out.println("* This demo show how to encrypt and decrypt files using symmetric algorithms *");
      System.out.println("* like AES, DES, 3DES, etc. The components can also be used to encrypt and   *");
      System.out.println("* decrypt in memory or to and from streams.                                  *");
      System.out.println("******************************************************************************");
    	
      
      System.out.println("Specify an algorithm:");
      System.out.println("1) AES");
      System.out.println("2) CAST");
      System.out.println("3) DES");
      System.out.println("4) IDEA");
      System.out.println("5) RC2");
      System.out.println("6) RC4");
      System.out.println("7) 3DES");
      System.out.println("8) Blowfish");
      System.out.println("9) Twofish");
      
      algorithm = prompt("\nAlgorithm",":","1");
      
      System.out.println("\nSelect an operation:");
      System.out.println("1) Encrypt");
      System.out.println("2) Decrypt");
      
      operation = prompt("\nOperation",":","1");
      
      //A key password is used to generate the Key and IV. 
      //When using a key password you only need to save this value. 
      //This makes key management much simpler.
      password = prompt("\nPassword");
      
      inputFile = prompt("Input File");
      outputFile = prompt("Output File");
      
      prompt("\nPress enter to begin the operation.\n","");
      
	  ezcrypt = new Ezcrypt();
      switch(Integer.parseInt(algorithm))
      {
    	case 1:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezAES);
    	  break;
        case 2:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezCAST);
    	  break;
    	case 3: 
    	  ezcrypt.setAlgorithm(Ezcrypt.ezDES);
    	  break;
    	case 4:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezIDEA);
    	  break;
    	case 5:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezRC2);
    	  break;
    	case 6:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezRC4);
    	  break;
    	case 7:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezTripleDES);
    	  break;
    	case 8:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezBlowfish);
    	  break;
    	case 9:
    	  ezcrypt.setAlgorithm(Ezcrypt.ezTwofish);
    	  break;
    	default:
    	  System.out.println("Invalid algorithm.");
    	  break;
      }
	  
      if(operation.equals("1")) //Encrypt
      {
    	ezcrypt.setInputFile(inputFile);
    	ezcrypt.setOutputFile(outputFile);
    	ezcrypt.setKeyPassword(password);
    	ezcrypt.encrypt();
    	  
    	System.out.println("Encryption successful!");
      }
      else if(operation.equals("2")) //Decrypt
      {
    	ezcrypt.setInputFile(inputFile);
    	ezcrypt.setOutputFile(outputFile);
    	ezcrypt.setKeyPassword(password);
    	ezcrypt.decrypt();
    	  
    	System.out.println("Decryption successful!");    	  
      }
      else
      {
    	  System.out.println("Invalid operation specified.");
      }
      
   
    } catch (IPWorksEncryptException ex) {
      System.out.println("IPWorksEncryptException exception thrown: " + ex.getCode() + " [" + ex.getMessage() + "].");
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
    }
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




