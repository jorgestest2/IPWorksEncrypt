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

class ezrandDemo
{
  private static Ezrand ezrand = new nsoftware.async.IPWorksEncrypt.Ezrand();

  static async Task Main(string[] args)
  {
    if (args.Length < 4)
    {
      Console.WriteLine("usage: ezrand [/i /f from /t to] /c count [/l length] [/s seed] /alg algorithm\n");
      Console.WriteLine("  /i           whether to generate random integers instead of bytes (optional)");
      Console.WriteLine("  from         the lower bound of the random number to be generated (inclusive) (optional, default 0)");
      Console.WriteLine("  to           the upper bound of the random number to be generated (exclusive) (optional, default 100)");
      Console.WriteLine("  count        the number of random integers or byte arrays to generate");
      Console.WriteLine("  length       the length of the byte array to be generated (optional, default 16)");
      Console.WriteLine("  seed         the seed to use (optional)");
      Console.WriteLine("  algorithm    the random number algorithm to use, chosen from {ISAAC, CryptoAPI, Platform, SecurePlatform, RC4Random}");
      Console.WriteLine("\nExample: ezrand /i /f 0 /t 100 /c 5 /alg ISAAC\n");
    }
    else
    {
      Dictionary<string, string> myArgs = ConsoleDemo.ParseArgs(args);
      bool ints = myArgs.ContainsKey("i");
      int count = int.Parse(myArgs["c"]);

      SelectAlgorithm(myArgs["alg"]);

      // Set up the random integer or byte generation.
      if (myArgs.ContainsKey("l")) ezrand.RandBytesLength = int.Parse(myArgs["l"]);
      if (myArgs.ContainsKey("f")) ezrand.Min = int.Parse(myArgs["f"]);
      if (myArgs.ContainsKey("t")) ezrand.Max = int.Parse(myArgs["t"]);
      if (myArgs.ContainsKey("s")) ezrand.Seed = myArgs["s"];

      // Perform the random integer or byte generation.
      if (ints)
      {
        for (int i = 0; i < count; i++)
        {
          await ezrand.GetNextInt();
          Console.WriteLine(ezrand.RandInt);
        }
      }
      else
      {
        for (int i = 0; i < count; i++)
        {
          await ezrand.GetNextBytes();

          // Display each byte as 2 uppercase hexadecimal characters.
          string result = "";
          foreach (byte myByte in ezrand.RandBytesB)
          {
            result += myByte.ToString("X2") + " ";
          }

          Console.WriteLine(result);
        }
      }
    }
  }

  private static void SelectAlgorithm(string algo)
  {
    switch (algo.ToLower())
    {
      case "isaac":
        ezrand.Algorithm = EzrandAlgorithms.raISAAC;
        break;
      case "cryptoapi":
        ezrand.Algorithm = EzrandAlgorithms.raMSCryptoAPI;
        break;
      case "platform":
        ezrand.Algorithm = EzrandAlgorithms.raPlatform;
        break;
      case "secureplatform":
        ezrand.Algorithm = EzrandAlgorithms.raSecurePlatform;
        break;
      case "rc4random":
        ezrand.Algorithm = EzrandAlgorithms.raRC4Random;
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