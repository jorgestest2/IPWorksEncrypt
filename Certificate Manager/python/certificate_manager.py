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


def fireCertList(e):
  global i
  i = i + 1
  print(str(i) + ". " + e.cert_subject)

def fireError(e):
  print("ERROR: %s" % e)

def bufferCheck(val):
  temp = input()
  if temp == "":
    temp = val
  return temp

global i
i = 0

print("Welcome to the CertMgr demo. This demo will read the available\ncertificates from a provided certificate store (e.g. PFX, PEM, etc.).\n")

try:
  certmgr1 = CertMgr()

  certmgr1.on_error = fireError
  certmgr1.on_cert_list = fireCertList
  
  buffer = 0
  while buffer not in range(1,4):
    print("Select Certificate Store Type:")
    print("1: PFX File")
    print("2: PEMKey File")
    print("3: Java Key Store File")
    buffer = int(input("Selection: "))
  
  if buffer == 1:
    certmgr1.set_cert_store_type(2)
    print("Please Enter PFX File Path (./100.pfx):"),
    buffer = bufferCheck("./100.pfx")
  elif buffer == 2:
    certmgr1.set_cert_store_type(6)
    print("Please Enter PEMKey File Path:"),
    buffer = bufferCheck("./something.pem")
  else:
    certmgr1.set_cert_store_type(4)
    print("Please Enter JKS File Path:"),
    buffer = bufferCheck("./something.jks")

  certmgr1.set_cert_store(buffer)
  
  print("Please enter store password [password]: "),
  buffer = bufferCheck("test")
  certmgr1.set_cert_store_password(buffer)
  
  certmgr1.list_store_certificates()
  
except IPWorksEncryptError as e:
  print("IPWorksEncrypt Error: %s" %e.message)

except Exception as e:
  fireError(e)

