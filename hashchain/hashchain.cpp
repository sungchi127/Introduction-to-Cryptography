#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include<bits/stdc++.h>
using namespace std;


char alpha[16] = {'0', '1', '2', '3', '4' , '5', '6' ,'7' , '8', '9' , 'A', 'B', 'C', 'D', 'E', 'F'};
int main ()
{
    using namespace CryptoPP;
    HexEncoder encoder(new FileSink(std::cout));
    HexEncoder encode;
    std::string msg = "109550127";
    std::string digest,pre;

    SHA256 hash;
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);

    //std::cout << "Message: " << msg << std::endl;
    
    //std::cout << "Digest: ";
    //StringSource(digest, true, new Redirector(encoder));
    //std::cout << std::endl;

    StringSource(digest, true, new HexEncoder(new StringSink(pre)));
    string temp,temp1,nonce="00000000",result,hv,hv1;
    for(int i=0;i<9;i++){
        int flag=0;
        if(i==0){
            temp="",temp1="",hv="",hv1="";
            StringSource(nonce, true, new HexDecoder(new StringSink(temp)));
            StringSource(pre, true, new HexDecoder(new StringSink(temp1)));
            cout<<i<<"\n"<<pre<<"\n"<<nonce<<"\n";
            pre="";
            hv=temp1+temp;

            hash.Update((const byte*)hv.data(), hv.size());
            hv1.resize(hash.DigestSize());
            hash.Final((byte*)&hv1[0]);

            StringSource(hv1, true, new HexEncoder(new StringSink(result)));
            cout<<result<<endl;
            pre=result;
            continue;
        }
        cout<<i<<"\n"<<pre<<"\n";
        for(int a = 0; a < 16; a ++) {
            for(int b = 0; b < 16; b ++) {
                for(int c = 0; c < 16; c ++) {
                    for(int d = 0; d < 16; d ++) {
                        for(int e = 0; e < 16; e ++) {
                            for(int f = 0; f < 16; f ++) {
                                for(int g = 0; g < 16; g ++) {
                                    for(int h = 0; h < 16; h ++) {
                                            flag=0;
                                            nonce[0]=alpha[a],nonce[1]=alpha[b],nonce[2]=alpha[c],nonce[3]=alpha[d];
                                            nonce[4]=alpha[e],nonce[5]=alpha[f],nonce[6]=alpha[g],nonce[7]=alpha[h];
                                            //cout<<nonce<<endl;
                                            result="",temp="",temp1="",hv="",hv1="";
                                            StringSource(nonce, true, new HexDecoder(new StringSink(temp)));
                                            StringSource(pre, true, new HexDecoder(new StringSink(temp1)));
                                    
                                            hv=temp1+temp;

                                            hash.Update((const byte*)hv.data(), hv.size());
                                            hv1.resize(hash.DigestSize());
                                            hash.Final((byte*)&hv1[0]);

                                            StringSource(hv1, true, new HexEncoder(new StringSink(result)));
                                            //cout<<result<<endl;

                                            for(int j=0;j<i;j++){
                                                if(result[j]=='0') flag++;
                                            }
                                            if(flag==i){
                                                break;
                                            }
                                    }
                                    if(flag==i) break;
                                }
                                if(flag==i) break;
                            }
                            if(flag==i) break;
                        }
                        if(flag==i) break;
                    }
                    if(flag==i) break;
                }
                if(flag==i) break;
            }
            if(flag==i) break;
        }
        pre="";
        pre=result;
        cout<<nonce<<"\n"<<result<<"\n";

    }

    return 0;
}
