//
// Created by yili on 2021/1/13.
//

#ifndef CRYPT_BASE64_H
#define CRYPT_BASE64_H
#define IN
#define OUT
#include <string>
#include <map>
#include <vector>
using namespace std;

class Base64 {
private:
    char *mB64Words;
    map<char, char> mB64Map;
public:
    explicit Base64();
    virtual ~Base64();

    void b64Encode(IN vector<unsigned char> &buf, OUT string &out) const;
    int b64Decode(IN string &str, OUT vector<unsigned char> &out) const;
};

#endif //CRYPT_BASE64_H
