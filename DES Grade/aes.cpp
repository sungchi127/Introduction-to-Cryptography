#include<bits/stdc++.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    using namespace CryptoPP;

    std::string plain = "AES is the US block cipher standard.";
    std::string str = "keyis84932731830";
    std::string cipher;
    HexEncoder encoder(new FileSink(std::cout));

    byte k[16];
    byte iv0[16];
    byte iv9[16];
    for (int i = 0; i < 16; i++)
    {
        k[i] = str[i];
    }  
   
   
    str = "0000000000000000";
    for (int i = 0; i < 16; i++)
    {
        iv0[i] = str[i];
    }


    str = "9999999999999999";
    for (int i = 0; i < 16; i++)    
    {
        iv9[i] = str[i];
    }

    SecByteBlock tmp_1(k, sizeof(k));
    SecByteBlock key((const byte*)tmp_1.data(), tmp_1.size());
    SecByteBlock tmp_2(iv0, sizeof(iv0));
    SecByteBlock iv_0((const byte*)tmp_2.data(), tmp_2.size());
    SecByteBlock tmp_3(iv9, sizeof(iv9));
    SecByteBlock iv_9((const byte*)tmp_3.data(), tmp_3.size());





    AESEncryption aese(key, key.size());
    CFB_Mode_ExternalCipher::Encryption cfb(aese, iv0, 4);
    StringSource CFB(plain, true, new StreamTransformationFilter(cfb, new StringSink(cipher), StreamTransformationFilter::NO_PADDING));
    std::cout << "CFB cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();
 


    
    CBC_Mode< AES >::Encryption e_0;
    e_0.SetKeyWithIV(key, key.size(), iv_0);
    StringSource cbc_0(plain, true, new StreamTransformationFilter(e_0, new StringSink(cipher), StreamTransformationFilter::ZEROS_PADDING)); 
    std::cout << "CBC cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();



    
    CBC_Mode< AES >::Encryption e_9;
    e_9.SetKeyWithIV(key, key.size(), iv_9);
    StringSource cbc_9(plain, true, new StreamTransformationFilter(e_9, new StringSink(cipher)));
    std::cout << "CBC2 cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();




    ECB_Mode< AES >::Encryption e;
    e.SetKey(key, key.size());
    StringSource ecb(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
    std::cout << "ECB cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    cipher.clear();


    return 0;
}