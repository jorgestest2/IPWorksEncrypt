# 
# IPWorks Encrypt 2022 Python Edition - Sample Project
# 
# This sample project demonstrates the usage of IPWorks Encrypt in a 
# simple, straightforward way. This is not intended to be a complete 
# application. Error handling and other checks are simplified for clarity.
# 
# Copyright (c) 2023 /n software inc. www.nsoftware.com
# 

import sys
import string
from ipworksencrypt import *

input = sys.hexversion<0x03000000 and raw_input or input

smime = SMIME()
certmgr = CertMgr()
certSubjects = []
certCount = -1
inSrc = ""
outSrc = ""

def promptWithDefault(prompt, val):
  temp = input(prompt)
  return val if(temp == "") else temp

def fireCertList(e):
  global certCount, certSubjects
  certCount += 1
  certSubjects = certSubjects[:] + [e.cert_subject]
  print(str(certCount) + ". " + e.cert_subject)

def selectCertificate():
  global certCount
  certCount = -1
  prompt = "Select Certificate Store Type:"
  prompt += "\n  0) PFX File"
  prompt += "\n  1) PEMKey File"
  prompt += "\n  2) Java Key Store (JKS) File"
  prompt += "\nChoice: [0] "
  certTypeChoice = promptWithDefault(prompt, "0")
  if certTypeChoice == "0":
    certmgr.set_cert_store_type(2)
    certStorePath = promptWithDefault("Enter PFXFile Path: [./testcert.pfx] ", "./testcert.pfx")
  elif certTypeChoice == "1":
    certStorePath = promptWithDefault("Enter PEMKeyFile Path: [./testcert.pem] ", "./testcert.pem")
    certmgr.set_cert_store_type(6)
  elif certTypeChoice == "2":
    certStorePath = promptWithDefault("Enter JKS Path: [./testcert.jks] ", "./testcert.jks")
    certmgr.set_cert_store_type(4)
  else:
    print("Not a valid choice. Please try again.")
    selectCertificate()
  
  certmgr.set_cert_store_password(promptWithDefault("Enter store password: [password] ", "password"))
  certmgr.set_cert_store(certStorePath)
  
  print("Please select a certificate:")
  certmgr.list_store_certificates()
  certmgr.set_cert_subject(certSubjects[int(promptWithDefault("\nChoice: [0] ", "0"))])

def doEncrypt():
  getIOSources()
  print("Please select a certificate for encryption.")
  selectCertificate()
  smime.add_recipient_cert(certmgr.get_cert_encoded())
  smime.encrypt()
  
def doDecrypt():
  getIOSources()
  print("Please select a certificate for decryption.")
  selectCertificate()
  
  smime.set_cert_store_type(certmgr.get_cert_store_type())
  smime.set_cert_store(certmgr.get_cert_store())
  smime.set_cert_store_password(certmgr.get_cert_store_password())
  smime.set_cert_subject(certmgr.get_cert_subject())
  smime.decrypt()
  
def doSign():
  getIOSources()
  print("Please select a certificate for signing.")
  selectCertificate()
  smime.set_cert_store_type(certmgr.get_cert_store_type())
  smime.set_cert_store(certmgr.get_cert_store())
  smime.set_cert_store_password(certmgr.get_cert_store_password())
  smime.set_cert_subject(certmgr.get_cert_subject())
  smime.sign()
  
def doVerify():
  getIOSources()
  print("Please select a certificate for verification.")
  selectCertificate()
  smime.set_signer_cert_encoded(certmgr.get_cert_encoded())
  smime.verify_signature()
  
def doSignAndEncrypt():
  getIOSources()
  print("Please select a certificate for signing.")
  selectCertificate()
  smime.set_cert_store_type(certmgr.get_cert_store_type())
  smime.set_cert_store(certmgr.get_cert_store())
  smime.set_cert_store_password(certmgr.get_cert_store_password())
  smime.set_cert_subject(certmgr.get_cert_subject())
  print("Please select a certificate for encryption.")
  selectCertificate()
  smime.add_recipient_cert(certmgr.get_cert_encoded())
  smime.sign_and_encrypt()
  
def doDecryptAndVerify():
  getIOSources()
  print("Please select a certificate for verification.")
  selectCertificate()
  smime.set_signer_cert_encoded(certmgr.get_cert_encoded())
  print("Please select a certificate for decryption.")
  selectCertificate()
  smime.set_cert_store_type(certmgr.get_cert_store_type())
  smime.set_cert_store(certmgr.get_cert_store())
  smime.set_cert_store_password(certmgr.get_cert_store_password())
  smime.set_cert_subject(certmgr.get_cert_subject())
  smime.decrypt_and_verify_signature()

def getIOSources():
  global inSrc, outSrc
  inSrc = promptWithDefault("Read from a file or string? (f/s): ", "f")
  if(inSrc == "s"):
    smime.set_input_message(input("Please enter the input string: "))
  else:
    smime.set_input_file(input("Please enter the input file path: "))
  outSrc = promptWithDefault("Write to a file or string? (f/s): ", "f")
  if(outSrc == "f"):
    smime.set_output_file(input("Please enter the output file path: "))

def main():
  print("\nWelcome to the /n software S/MIME demo.\n")
  prompt = "What would you like to do?"
  prompt += "\n  0) Quit"
  prompt += "\n  1) Encrypt"
  prompt += "\n  2) Decrypt"
  prompt += "\n  3) Sign"
  prompt += "\n  4) Verify"
  prompt += "\n  5) Sign & Encrypt"
  prompt += "\n  6) Decrypt & Verify"
  prompt += "\nChoice: "
  op = input(prompt)
  
  if(op == "0"):
    sys.exit(0)
  elif(op == "1"):
    doEncrypt()
  elif(op == "2"):
    doDecrypt()
  elif(op == "3"):
    doSign()
  elif(op == "4"):
    doVerify()
  elif(op == "5"):
    doSignAndEncrypt()
  elif(op == "6"):
    doDecryptAndVerify()
  else:
    print("Not a valid choice.")
    main()

# By including headers with the output message, 
# it can be passed directly back into this demo.
smime.config("IncludeHeaders=true")
certmgr.on_cert_list = fireCertList
try:
  main()
except IPWorksEncryptError as e:
  print("IPWorksEncrypt Error:\n\n" + e)

if(outSrc == "s"):
  print("OutputMessage: %s\n" %(smime.get_output_message()))
print("\nThe demo has finished running.")

