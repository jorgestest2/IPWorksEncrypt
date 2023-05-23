/*
 * IPWorks Encrypt 2022 .NET Edition - Demo Application
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 */

using System.Collections.Generic;
﻿using System;
using System.Threading.Tasks;
using nsoftware.async.IPWorksEncrypt;

class openpgpDemo
{
  private static Openpgp openpgp = new nsoftware.async.IPWorksEncrypt.Openpgp();

  static async Task Main(string[] args)
  {
    if (args.Length < 6)
    {
      Console.WriteLine("usage: openpgp /k keyringdir /p passphrase /a action /f inputfile /o outputfile [/w] /s inputstring\n");
      Console.WriteLine("  keyringdir   the path to the keyring, which must contain the files secring.gpg and pubring.gpg");
      Console.WriteLine("  passphrase   required to sign or decrypt");
      Console.WriteLine("  action       chosen from {sign, encrypt, signencrypt, decrypt, verify, decryptverify}");
      Console.WriteLine("  inputfile    the path to the input file (specify this or inputstring, but not both)");
      Console.WriteLine("  outputfile   the path to the output file (specify if inputfile is specified)");
      Console.WriteLine("  /w           whether to overwrite the output file (optional)");
      Console.WriteLine("  inputstring  the message to sign, encrypt, decrypt, or verify");
      Console.WriteLine("\nExample: openpgp /k c:\\pubring /p password /a signencrypt /f c:\\myfile.txt /o c:\\myencryptedfile.dat /w\n");
    }
    else
    {
      Dictionary<string, string> myArgs = ConsoleDemo.ParseArgs(args);
      string action = myArgs["a"].ToLower();

      Keymgr keymgr = new Keymgr();
      await keymgr.LoadKeyring(myArgs["k"]);

      // Set up the action.
      if (myArgs.ContainsKey("f")) openpgp.InputFile = myArgs["f"];
      if (myArgs.ContainsKey("o")) openpgp.OutputFile = myArgs["o"];
      if (myArgs.ContainsKey("s")) openpgp.InputMessage = myArgs["s"];
      openpgp.Overwrite = myArgs.ContainsKey("w");
      openpgp.ASCIIArmor = true;

      // Perform the action.
      switch (action)
      {
        case "sign":
          // Need the private key to sign.
          keymgr.Key.Passphrase = myArgs["p"];
          openpgp.Keys.Add(keymgr.Key);

          await openpgp.Sign();
          break;
        case "encrypt":
          // Need the recipient key to encrypt.
          openpgp.RecipientKeys.Add(keymgr.Key);

          await openpgp.Encrypt();
          break;
        case "signencrypt":
          // Need the private key to sign.
          keymgr.Key.Passphrase = myArgs["p"];
          openpgp.Keys.Add(keymgr.Key);

          // Need the recipient key to encrypt.
          openpgp.RecipientKeys.Add(keymgr.Key);

          await openpgp.SignAndEncrypt();
          break;
        case "decrypt":
          // Need the private key to decrypt.
          keymgr.Key.Passphrase = myArgs["p"];
          openpgp.Keys.Add(keymgr.Key);

          await openpgp.Decrypt();
          break;
        case "verify":
          // Need the signer key to verify a signature.
          openpgp.SignerKeys.Add(keymgr.Key);

          await openpgp.VerifySignature();
          break;
        case "decryptverify":
          // Need the private key to decrypt.
          keymgr.Key.Passphrase = myArgs["p"];
          openpgp.Keys.Add(keymgr.Key);

          // Need the signer key to verify a signature.
          openpgp.SignerKeys.Add(keymgr.Key);

          await openpgp.DecryptAndVerifySignature();
          break;
        default:
          throw new Exception("Invalid action.\n");
      }

      Console.WriteLine("Completed " + action + " action.");
      if (myArgs.ContainsKey("o"))
      {
        Console.WriteLine("Output file: " + openpgp.OutputFile);
      }
      else
      {
        Console.WriteLine("Output message: " + openpgp.OutputMessage);
      }
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
        if (i + 1 < args.Length & !args[i + 1].StartsWith("/"))
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