#include<string>
#include <fstream>
#include<vector>
using namespace std;

class Base64{
    private:
        const char* BASE64_CHARS = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        vector<unsigned char> code;
        vector<unsigned char> plain;
    public:
    
        string showCode();
        string showPlain();
        // to encode file to base64
        void enCoder(ifstream& input, ofstream& output);
        // to decode base64 code to original file
        bool deCoder(ifstream& input, ofstream& output);
        // deprecated mothod
        void enCoder_deprecated(ifstream& input, ofstream& output);
        // clear code and plain
        void clear();
};