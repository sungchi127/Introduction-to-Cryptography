#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/rsa.h>

#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;

int main(){
    using namespace std;
    using namespace CryptoPP;
    char HEX[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    
    //第1題

    string message_1 = "Hello World!";
    Integer e_1("0x11");
    Integer n_1("0x04823f9fe38141d93f1244be161b20f");
    Integer m_1;
    m_1 = Integer((const byte*)message_1.data(), message_1.size());
    cout << "Ciphertext_1:" << hex << a_exp_b_mod_c(m_1, e_1, n_1) << endl;

    //第2題
    
    string message_2 = "RSA is public key.";
    Integer e_2("0x10001");
    Integer n_2("0x9711ea5183d50d6a91114f1d7574cd52621b35499b4d3563ec95406a994099c9");
    Integer m_2;
    m_2 = Integer((const byte*)message_2.data(), message_2.size());
    cout << "Ciphertext_2:" << hex << a_exp_b_mod_c(m_2, e_2, n_2) << endl;
    
    //第3題
    // Integer n_s("0xc45350fa19fa8d93");
    // Integer c_s("0xa02d51d0e87efe1defc19f3ee899c31d");
    // Integer d_s("0x454a950c5bcbaa41");
    // Integer r_s;
    // string recovered_s;
    // r_s = a_exp_b_mod_c(c_s, d_s, n_s);
    // size_t req_s = r_s.MinEncodedSize();
    // recovered_s.resize(req_s);
    // r_s.Encode((byte*)recovered_s.data(), recovered_s.size());
    // cout << "Message:" << hex << recovered_s << endl;
    
    ///////////////////////////////////////////////////////////////
    string privateKey = "0x53a0a95b089cf23adb5cc73f07XXXXX";
    Integer n("0xc4b361851de35f080d3ca7352cbf372d");
    Integer e("0x1d35");
    Integer c("0xa02d51d0e87efe1defc19f3ee899c31d");
    for (int _a = 0; _a < 16; _a++)
      for (int _b = 0; _b < 16; _b++)
          for (int _c = 0; _c < 16; _c++)
              for (int _d = 0; _d < 16; _d++)
                  for (int _e = 0; _e < 16; _e++) {
    
                      privateKey[privateKey.length() - 5] = HEX[_a];
                      privateKey[privateKey.length() - 4] = HEX[_b];
                      privateKey[privateKey.length() - 3] = HEX[_c];
                      privateKey[privateKey.length() - 2] = HEX[_d];
                      privateKey[privateKey.length() - 1] = HEX[_e];
                      Integer d(privateKey.c_str());           
                      Integer r;
                      string recovered;
                      
                      r = a_exp_b_mod_c(c, d, n);               
                      size_t req = r.MinEncodedSize();
                      recovered.resize(req);
                      r.Encode((byte*)recovered.data(), recovered.size());
                          
                      bool check = true;
                      for (int i = 0; i < recovered.length(); i++)
                          if (!((recovered[i] >= 32) && (recovered[i] <= 127))){
                              check = false;
                              break;
                      }
                      if (check)
                          cout << "privateKey:" << privateKey << '\n' << "recovered:" << recovered << endl;
                  }

    return 0;
}