import SwiftUI
import IPWorksEncrypt

struct ContentView: View, SMIMEDelegate {
    func onError(errorCode: Int32, description: String) {}    
    func onRecipientInfo(issuer: String, serialNumber: String, subjectKeyIdentifier: String, encryptionAlgorithm: String) {}    
    func onSignerCertInfo(issuer: String, serialNumber: String, subjectKeyIdentifier: String, certEncoded: Data) {}
    
    var smime = SMIME()
    var certmgr = CertMgr()
    
    func setCert() {
        smime.certStoreType = SmimeCertStoreTypes.cstPFXFile
        smime.certStore = "/Applications/IPWorks Encrypt 2022 macOS Edition/demos/SMIME/testcert.pfx"
        smime.certStorePassword = "password"
        
        do{
            try smime.setCertSubject(certSubject: "*")
        } catch {
            print("Error loading certificate: \(error)")
        }
        certmgr.certStoreType = CertStoreTypes.cstPublicKeyFile
        certmgr.certStore = "/Applications/IPWorks Encrypt 2022 macOS Edition/demos/SMIME/testcert.cer"
        certmgr.certStorePassword = "password"
        
        do{
            try certmgr.setCertSubject(certSubject: "*")
            print(certmgr.certEncodedB)
            try smime.addRecipientCert(certEncoded: certmgr.certEncodedB)
        } catch {
            print("Error loading certificate: \(error)")
        }
    }

    var documentsPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0] + "/"
    @State private var inputheaders: String = ""
    @State private var inputmessage: String = "This message is used for testing the /n software SMIME Control for iPhone!  Digital signing and encryption are provided by sample certificates. Please replace these with your own certificates for security."
    @State private var outputheaders: String = ""
    @State private var outputmessage: String = ""
        
    var body: some View {
        VStack(alignment: .leading)
      {
          Text("This demo shows how to use the SMIME component to sign, encrypt, decrypt, and verify data.")
              .foregroundColor(Color.blue)
        Text("Original Message Headers:")

        TextEditor(text: $inputheaders)
            .border(Color.black, width: 1)
        
        Text("Original Message:")

        TextEditor(text: $inputmessage)
            .border(Color.black, width: 1)
  
        HStack {
          signButton()              
          encryptButton()          
          signAndEncryptButton()            
        }
        HStack
        {
          verifyButton()          
          decryptButton()          
          decryptAndVerifyButton()
        }
          Group{
              Text("Output Headers:")
              TextEditor(text: $outputheaders)
                  .border(Color.black, width: 1)
              Text("Output Message:")
              TextEditor(text: $outputmessage)
                  .border(Color.black, width: 1)
          }
      }
      .padding(/*@START_MENU_TOKEN@*/.all, 8.0/*@END_MENU_TOKEN@*/)
    }

  @ViewBuilder
  private func signButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        self.setCert()
        try smime.sign()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
      }
    })
    {
      Text("Sign").font(.system(size: 20))
        .frame(minWidth: 120, minHeight: 40)
        .background(RoundedRectangle(cornerRadius: 8)
        .fill(Color.gray))
    }
    .buttonStyle(PlainButtonStyle())
    
  }

  @ViewBuilder
  private func encryptButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""
      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        self.setCert()
        try smime.encrypt()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
    }
    }, label: {
      Text("Encrypt")
        .font(.system(size: 20))
        .frame(minWidth: 120, minHeight: 40)
        .background(RoundedRectangle(cornerRadius: 8)
        .fill(Color.gray))
    })
    .buttonStyle(PlainButtonStyle())
    
  }

  @ViewBuilder
  private func signAndEncryptButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        self.setCert()
        try smime.signAndEncrypt()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
      }
    }, label: {
      Text("Sign & Encrypt")
        .font(.system(size: 20))
        .frame(minWidth: 140, minHeight: 40)
        .background(RoundedRectangle(cornerRadius: 8)
        .fill(Color.gray))
    })
    .buttonStyle(PlainButtonStyle())
    
  }

  @ViewBuilder
  private func verifyButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        self.setCert()
        try smime.verifySignature()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
      }
    }, label: {
      Text("Verify")
        .font(.system(size: 20))
        .frame(minWidth: 120, minHeight: 40)
        .background(RoundedRectangle(cornerRadius: 8)
        .fill(Color.gray))
    })
    .buttonStyle(PlainButtonStyle())
    
  }

  @ViewBuilder
  private func decryptButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        self.setCert()
        try smime.decrypt()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
      }
    }, label: {
      Text("Decrypt")
      .font(.system(size: 20))
      .frame(minWidth: 120, minHeight: 40)
      .background(RoundedRectangle(cornerRadius: 8)
      .fill(Color.gray))
    })
    .buttonStyle(PlainButtonStyle())
    
  }

  @ViewBuilder
  private func decryptAndVerifyButton() -> some View {
    Button(action:
    {
      //client.runtimeLicense = ""
      smime.delegate = self
      outputheaders = ""
      outputmessage = ""      
      do
      {
        try smime.reset()
        smime.inputMessageHeadersString = inputheaders
        smime.inputMessage = inputmessage
        let certmgr = CertMgr()
        try certmgr.readCertificate(fileName: "../testcert.cer")
        try smime.addRecipientCert(certEncoded: certmgr.certEncodedB)
        self.setCert()
        try smime.decryptAndVerifySignature()
        outputheaders += smime.outputMessageHeadersString
        outputmessage += smime.outputMessage
      }
      catch
      {
        print(error)
        return
      }
    }, label: {
      Text("Decrypt & Verify")
        .font(.system(size: 20))
        .frame(minWidth: 160, minHeight: 40)
        .background(RoundedRectangle(cornerRadius: 8)
        .fill(Color.gray))
    })
    .buttonStyle(PlainButtonStyle())
    
  }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()            
    }
}
