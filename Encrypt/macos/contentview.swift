import SwiftUI
import IPWorksEncrypt

struct ContentView: View, EzCryptDelegate {
  func onError(errorCode: Int32, description: String) {}
  func onProgress(bytesProcessed: Int64, percentProcessed: Int32) {}
  
  var encrypt = EzCrypt()
  var documentsPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0] + "/"
  @State private var password: String = ""
  @State private var input: String = ""
  @State private var output: String = ""
  
  var body: some View {
    VStack(alignment: .center)
    {
      Text("Input password and input text. Click Encrypt to encrypt to Output and Decrypt to decrypt to Output.").foregroundColor(Color.blue)
      HStack{
        Text("Password:")
        TextField("Enter password...", text: $password)
      }
      HStack{
        Text("Input:")
        TextField("Input text...", text: $input)
      }
      
      HStack {
        encryptButton()
        decryptButton()
      }
      
      Text("Output:")
      TextEditor(text: $output)
    }
    .padding(/*@START_MENU_TOKEN@*/.all, 8.0/*@END_MENU_TOKEN@*/)
  }
  
  @ViewBuilder
  private func encryptButton() -> some View {
    Button(action:
            {
      //client.runtimeLicense = ""
      encrypt.delegate = self
      output = ""
      do
      {
        encrypt.useHex = true
        encrypt.inputMessage = input
        encrypt.keyPassword = password
        try encrypt.encrypt()
        output = encrypt.outputMessage
        input = ""
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
  private func decryptButton() -> some View {
    Button(action:
            {
      encrypt.delegate = self
      output = ""
      do
      {
        encrypt.useHex = true
        encrypt.inputMessage = input
        encrypt.keyPassword = password
        try encrypt.decrypt()
        output = encrypt.outputMessage
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
}  

struct ContentView_Previews: PreviewProvider {
  static var previews: some View {
    ContentView()
  }
}
