/*
 * IPWorks Encrypt 2022 .NET Edition - Demo Application
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 */

using System.Collections.Generic;
﻿using System;
using System.Threading.Tasks;
using nsoftware.async.IPWorksEncrypt;

class hashDemo
{
  private static Hash hash = new nsoftware.async.IPWorksEncrypt.Hash();

  static async Task Main(string[] args)
  {
    if (args.Length < 4)
    {
      Console.WriteLine("usage: hash /f inputfile /s inputstring [/hex] /alg algorithm\n");
      Console.WriteLine("  inputfile    the path to the input file (specify this or inputstring, but not both)");
      Console.WriteLine("  inputstring  the message to hash");
      Console.WriteLine("  /hex         whether to hex encode the hash value (optional)");
      Console.WriteLine("  algorithm    the hash algorithm to use, chosen from");
      Console.WriteLine("               {SHA1, SHA224, SHA256, SHA384, SHA512, MD2, MD4, MD5, RIPEMD160, MD5SHA1, HMACMD5, HMACSHA1,");
      Console.WriteLine("                HMACSHA224, HMACSHA256, HMACSHA384, HMACSHA512, HMACRIPEMD160, SHA3-224, SHA3-256, SHA3-384, SHA3-512}");
      Console.WriteLine("\nExample: hash /f c:\\myfile.txt /hex /alg sha1\n");
    }
    else
    {
      Dictionary<string, string> myArgs = ConsoleDemo.ParseArgs(args);

      SelectAlgorithm(myArgs["alg"]);

      // Set up the hash.
      if (myArgs.ContainsKey("f")) hash.InputFile = myArgs["f"];
      if (myArgs.ContainsKey("s")) hash.InputMessage = myArgs["s"];
      hash.EncodeHash = myArgs.ContainsKey("hex");

      // Perform the hash.
      await hash.ComputeHash();
      Console.WriteLine("Hash complete! Hash value: " + hash.HashValue);
    }
  }
  
  private static void SelectAlgorithm(string algo)
  {
    switch (algo.ToLower())
    {
      case "sha1":
        hash.Algorithm = HashAlgorithms.haSHA1;
        break;
      case "sha224":
        hash.Algorithm = HashAlgorithms.haSHA224;
        break;
      case "sha256":
        hash.Algorithm = HashAlgorithms.haSHA256;
        break;
      case "sha384":
        hash.Algorithm = HashAlgorithms.haSHA384;
        break;
      case "sha512":
        hash.Algorithm = HashAlgorithms.haSHA512;
        break;
      case "md2":
        hash.Algorithm = HashAlgorithms.haMD2;
        break;
      case "md4":
        hash.Algorithm = HashAlgorithms.haMD4;
        break;
      case "md5":
        hash.Algorithm = HashAlgorithms.haMD5;
        break;
      case "ripemd160":
        hash.Algorithm = HashAlgorithms.haRIPEMD160;
        break;
      case "md5sha1":
        hash.Algorithm = HashAlgorithms.haMD5SHA1;
        break;
      case "hmacmd5":
        hash.Algorithm = HashAlgorithms.haHMACMD5;
        break;
      case "hmacsha1":
        hash.Algorithm = HashAlgorithms.haHMACSHA1;
        break;
      case "hmacsha224":
        hash.Algorithm = HashAlgorithms.haHMACSHA224;
        break;
      case "hmacsha256":
        hash.Algorithm = HashAlgorithms.haHMACSHA256;
        break;
      case "hmacsha384":
        hash.Algorithm = HashAlgorithms.haHMACSHA384;
        break;
      case "hmacsha512":
        hash.Algorithm = HashAlgorithms.haHMACSHA512;
        break;
      case "hmacripemd160":
        hash.Algorithm = HashAlgorithms.haHMACRIPEMD160;
        break;
      case "sha3-224":
        hash.Algorithm = HashAlgorithms.haSHA3_224;
        break;
      case "sha3-256":
        hash.Algorithm = HashAlgorithms.haSHA3_256;
        break;
      case "sha3-384":
        hash.Algorithm = HashAlgorithms.haSHA3_384;
        break;
      case "sha3-512":
        hash.Algorithm = HashAlgorithms.haSHA3_512;
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