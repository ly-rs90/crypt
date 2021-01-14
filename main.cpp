#include <iostream>
#include "crypt/include/base64.h"

int main() {
    vector<unsigned char> buf;
    buf.push_back('H');
    buf.push_back('e');
    buf.push_back('l');
    buf.push_back('l');
    buf.push_back('o');
    buf.push_back(',');
    buf.push_back('W');
    buf.push_back('o');
    buf.push_back('r');
    buf.push_back('l');
    buf.push_back('d');

    Base64 base64;
    string out;
    base64.b64Encode(buf, out);
    cout << "Hello,World: " << out << endl;

    string s("5L2g5aW977yM5LiW55WM");
    vector<unsigned char> out1;

    base64.b64Decode(s, out1);
    string s1;
    for (auto &c: out1) {
        s1.push_back(c);
    }
    cout << s << ": " << s1 << endl;
    return 0;
}
