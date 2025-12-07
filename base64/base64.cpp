#define ENCODELENGTH 3
#define DECODELENGTH 4
#define ENCODEMASK 0x3F
#define DECODEMASK 0xFF

#include<string>
#include <fstream>
#include <iostream>
#include "base64.h"

using namespace std;

void Base64::enCoder(ifstream& input, ofstream& output){
    // buf 放二進制讀取緩衝
    char buf[ENCODELENGTH];
    // 存放分組後的資料
    unsigned int group = 0;
    // 存放 6bit 資料
    unsigned char bit6 = 0;
    while(input.read(buf,ENCODELENGTH)){
        for(int i = 0; i < 3; i++){
            group = group << 8;
            group += (unsigned char)buf[i];
        }
        for(int i = 3; i >= 0; i--){
            bit6 = ((group >> (6*i)) & ENCODEMASK);
            this-> code.push_back(BASE64_CHARS[bit6]);
        }
        group = 0;
    }
    streamsize r = input.gcount();
    if(r > 0){
        group = 0;
        for(int i = 0; i < 3; i++){
            group = group << 8;
            group += r > i ? buf[i] : 0;
        }
        for(int i = 3; i >= 3-r; i--){
            bit6 = ((group >> (6*i)) & ENCODEMASK);
            this-> code.push_back(BASE64_CHARS[bit6]);
        }
        for(int i = r; i < ENCODELENGTH; i++){
            this-> code.push_back('=');
        }
    }
    output.write(this-> showCode().data(), this-> code.size());
}

bool Base64::deCoder(ifstream& input, ofstream& output){
    // buf 放二進制讀取緩衝
    char buf[DECODELENGTH];
    // 存放分組後的資料
    unsigned int group = 0;
    // 存放 8bit 資料
    unsigned char bit8 = 0;
    // padding 數量
    int pad = 0;
    while(input.read(buf,DECODELENGTH)){
        for(int i = 0; i < 4; i++){
            group = group << 6;
            unsigned char unsignbuf = buf[i];
            if(unsignbuf >= 'A' && unsignbuf <= 'Z'){
                group += unsignbuf-'A';
            }else if(unsignbuf >= 'a' && unsignbuf <= 'z'){
                group += unsignbuf-'a'+26;
            }else if(unsignbuf >= '0' && unsignbuf <= '9'){
                group += unsignbuf-'0'+52;
            }else if(unsignbuf == '+'){
                group += 62;
            }else if(unsignbuf == '/'){
                group += 63;
            }else if(unsignbuf == '='){
                pad += 1;
            }else{
                return false;
            }
        }
        for(int i = 2; i >= pad; i--){
            bit8 = ((group >> (8*i)) & DECODEMASK);
            this-> plain.push_back(bit8);
        }
        group = 0;
    }
    output.write(this-> showPlain().data() , this->plain.size());
    return true;
}

string Base64::showCode(){
    if(!this->code.empty()){
        string s(this->code.begin(), this->code.end());
        return s;
    }else{
        return "Oops!! something wrong!!";
    }
}
string Base64::showPlain(){
    if(!this->plain.empty()){
        string s(this->plain.begin(), this->plain.end());
        return s;
    }else{
        return "Oops!! something wrong!!";
    }
}

void Base64::clear(){
    this-> code.clear();
    this-> plain.clear();
}


// 棄用 (以一個位元一個位元處理 要率差)
void Base64::enCoder_deprecated(ifstream& input, ofstream& output){
    // byte6 放從檔案中讀取的6bit, mask 放取得位元流的遮罩
    unsigned char byte6 = 0x00, mask = 0x80;
    // buf 放二進制讀取緩衝
    char buf[1];
    // c 紀錄讀取的位元數 = count
    int c = 6;

    while(input.read(buf,1)){
        // 讀取位元 如果讀到字元底部 或 集滿6bit 就做整理
        while(mask){
            byte6 = byte6 << 1;
            byte6 += bool(mask & (*buf));
            mask = mask >> 1;
            if(--c <= 0){
                cout << BASE64_CHARS[byte6];
                this-> code.push_back(BASE64_CHARS[byte6]);
                c = 6;
                byte6 = 0x00;
            }
        }
        mask = 0x80;
    }
    // 如果不夠6bit整除 補0
    if(c != 6){
        byte6 = byte6 << c;
        cout << BASE64_CHARS[byte6];
        this-> code.push_back(BASE64_CHARS[byte6]);
    }
}