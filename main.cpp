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
    cout << out << endl;
    return 0;
}
