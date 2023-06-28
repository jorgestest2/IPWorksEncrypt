/*
 * IPWorks Encrypt 2022 .NET Edition - Sample Project
 *
 * This sample project demonstrates the usage of IPWorks Encrypt in a 
 * simple, straightforward way. This is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * Copyright (c) 2023 /n software inc. www.nsoftware.com
 */

using System.Collections.Generic;
﻿using System;
using System.Threading.Tasks;
using nsoftware.async.IPWorksEncrypt;

class encryptDemo
{
  private static Ezcrypt ezcrypt = new nsoftware.async.IPWorksEncrypt.Ezcrypt();
  
  static async Task Main(string[] args)
  {
    if (args.Length < 8)
    {
      Console.WriteLine("usage: encrypt /a action /f inputfile /o outputfile [/w] /s inputstring /alg algorithm /p keypassword\n");
      Console.WriteLine("  action       chosen from {encrypt, decrypt}");
      Console.WriteLine("  inputfile    the path to the input file (specify this or inputstring, but not both)");
      Console.WriteLine("  outputfile   the path to the output file (specify if inputfile is specified)");
      Console.WriteLine("  /w           whether to overwrite the output file (optional)");
      Console.WriteLine("  inputstring  the message to encrypt or decrypt (if decrypt, must be in hex)");
      Console.WriteLine("  algorithm    the symmetric encryption algorithm to use, chosen from");
      Console.WriteLine("               {AES, Blowfish, CAST, ChaCha, DES, IDEA, RC2, RC4, Rijndael, TEA, TripleDES, Twofish, XSalsa20}");
      Console.WriteLine("  keypassword  the key password used to generate the Key and IV");
      Console.WriteLine("\nExample: encrypt /a encrypt /f c:\\myfile.txt /o c:\\myencryptedfile.dat /w /alg aes /p password\n");
    }
    else
    {
      Dictionary<string, string> myArgs = ConsoleDemo.ParseArgs(args);
      string action = myArgs["a"];

      SelectAlgorithm(myArgs["alg"]);
      ezcrypt.KeyPassword = myArgs["p"];

      // Set up the encryption or decryption.
      if (myArgs.ContainsKey("f")) ezcrypt.InputFile = myArgs["f"];
      if (myArgs.ContainsKey("o")) ezcrypt.OutputFile = myArgs["o"];
      if (myArgs.ContainsKey("s")) ezcrypt.InputMessage = myArgs["s"];
      ezcrypt.Overwrite = myArgs.ContainsKey("w");
      ezcrypt.UseHex = true;

      // Perform the encryption or decryption.
      if (action.Equals("encrypt"))
      {
        await ezcrypt.Encrypt();
      }
      else if (action.Equals("decrypt"))
      {
        await ezcrypt.Decrypt();
      }
      else
      {
        throw new Exception("Invalid action.\n");
      }

      Console.WriteLine("Completed " + action + "ion!");
      if (myArgs.ContainsKey("o"))
      {
        Console.WriteLine("Output file: " + ezcrypt.OutputFile);
      }
      else
      {
        Console.WriteLine("Output message: " + ezcrypt.OutputMessage);
      }
    }
  }
  
  private static void SelectAlgorithm(string algo)
  {
    switch (algo.ToLower())
    {
      case "aes":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezAES;
        break;
      case "blowfish":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezBlowfish;
        break;
      case "cast":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezCAST;
        break;
      case "chacha":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezChaCha;
        break;
      case "des":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezDES;
        break;
      case "idea":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezIDEA;
        break;
      case "rc2":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezRC2;
        break;
      case "rc4":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezRC4;
        break;
      case "rijndael":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezRijndael;
        break;
      case "tea":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezTEA;
        break;
      case "tripledes":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezTripleDES;
        break;
      case "twofish":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezTwofish;
        break;
      case "xsalsa20":
        ezcrypt.Algorithm = EzcryptAlgorithms.ezXSalsa20;
        break;
      default:
        throw new Exception("Invalid algorithm selection.\n");
    }
  }
}


class ConsoleDemo
{
  public static Dictionary<string, string> ParseArgs(string[] args)
  {
    Dictionary<string, string> dict = new Dictionary<string, string>();

    for (int i = 0; i < args.Length; i++)
    {
      // If it starts with a "/" check the next argument.
      // If the next argument does NOT start with a "/" then this is paired, and the next argument is the value.
      // Otherwise, the next argument starts with a "/" and the current argument is a switch.

      // If it doesn't start with a "/" then it's not paired and we assume it's a standalone argument.

      if (args[i].StartsWith("/"))
      {
        // Either a paired argument or a switch.
        if (i + 1 < args.Length && !args[i + 1].StartsWith("/"))
        {
          // Paired argument.
          dict.Add(args[i].TrimStart('/'), args[i + 1]);
          // Skip the value in the next iteration.
          i++;
        }
        else
        {
          // Switch, no value.
          dict.Add(args[i].TrimStart('/'), "");
        }
      }
      else
      {
        // Standalone argument. The argument is the value, use the index as a key.
        dict.Add(i.ToString(), args[i]);
      }
    }
    return dict;
  }
}