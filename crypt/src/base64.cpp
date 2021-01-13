//
// Created by yili on 2021/1/13.
//

#include "../include/base64.h"


Base64::Base64() {
    mB64Words = new char[64];
    for (auto i = 0; i < 26; i++) {
        mB64Words[i] = 'A' + i;
    }
    for (auto i = 0; i < 26; i++) {
        mB64Words[i+26] = 'a' + i;
    }
    for (auto i = 0; i < 10; i++) {
        mB64Words[i+52] = '0' + i;
    }
    mB64Words[62] = '+';
    mB64Words[63] = '/';

    auto v = 0;
    for (auto i = 'A'; i <= 'Z'; i++, v++) {
        mB64Map[i] = static_cast<char>(v);
    }
    for (auto i = 'a'; i <= 'z'; i++, v++) {
        mB64Map[i] = static_cast<char>(v);
    }
    for (auto i = '0'; i <= '9'; i++, v++) {
        mB64Map[i] = static_cast<char>(v);
    }
    mB64Map['+'] = static_cast<char>(62);
    mB64Map['/'] = static_cast<char>(63);
}

Base64::~Base64() {
    delete []mB64Words;
}

void Base64::b64Encode(vector<unsigned char> &buf, string &out) const {
    auto bufLen = buf.size();
    auto group = bufLen / 3;
    auto left = bufLen % 3;
    auto outLen = group * 4 + (left?4: 0);
    out.resize(outLen);

    auto index = 0ul, i = 0ul;
    for (; i < group*3; i += 3, index += 4) {
        auto a = buf[i] >> 2;
        auto b = ((buf[i] << 4) | (buf[i+1] >> 4)) & 0x3f;
        auto c = ((buf[i+1] << 2) | (buf[i+2] >> 6)) & 0x3f;
        auto d = buf[i+2] & 0x3f;

        out[index] = this->mB64Words[a];
        out[index+1] = this->mB64Words[b];
        out[index+2] = this->mB64Words[c];
        out[index+3] = this->mB64Words[d];
    }

    if (left == 1) {
        auto a = buf[i] >> 2;
        auto b = (buf[i] << 4) & 0x3f;

        out[index] = this->mB64Words[a];
        out[index+1] = this->mB64Words[b];
        out[index+2] = '=';
        out[index+3] = '=';
    }else if (left == 2) {
        auto a = buf[i] >> 2;
        auto b = ((buf[i] << 4) | (buf[i+1] >> 4)) & 0x3f;
        auto c = (buf[i+1] << 2) & 0x3f;

        out[index] = this->mB64Words[a];
        out[index+1] = this->mB64Words[b];
        out[index+2] = this->mB64Words[c];
        out[index+3] = '=';
    }
}

int Base64::b64Decode(string &str, vector<unsigned char> &out) const {
    auto strLen = str.size();
    auto group = strLen / 4;
    auto left = strLen % 4;

    if (left == 1) {
        return -1;
    }
    return 0;
}