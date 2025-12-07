#include <iostream>
#include <fstream>
#include "base64/base64.h"
using namespace std;

int main(int argc, char* argv[]){
    Base64 B;
    if(argc < 2){
        cout << "introduce base64 --> https://en.wikipedia.org/wiki/Base64";
        return 0;
    }
    int i = 1;
    string arg = argv[i];
    if(arg == "-e" && argc == 4){
        ifstream plain(argv[++i], std::ios::in | ios::binary);
        ofstream base64code(argv[++i], std::ios::out | ios::binary);
        if(plain.is_open()){
            B.enCoder(plain, base64code);
            if(B.showCode().size() < 1024){
                cout << B.showCode() << endl;
            }else{
                cout << "too large!! see in file --> " << argv[i] << endl;
            }
        }else{
            cout << "no plain file" << endl;
        }
        plain.close();
        base64code.close();
    }else if(arg == "-d" && argc == 4){
        ifstream code(argv[++i], std::ios::in | ios::binary);
        ofstream base64decode(argv[++i], std::ios::out | ios::binary);
        if(code.is_open()){
            if(B.deCoder(code, base64decode)){
                if(B.showPlain().size() < 1024){
                    cout << B.showPlain() << endl;
                }else{
                    cout << "too large!! see in file --> " << argv[i] << endl;
                }
            }else{
                cout << "wrong format!!" << endl;
            }
        }else{
            cout << "no code file" << endl;
        }
        code.close();
        base64decode.close();
    }else{
        cout << "nono para" << endl;
    }
    B.clear();
    return 0;
}