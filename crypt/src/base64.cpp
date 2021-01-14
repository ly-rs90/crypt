//
// Created by yili on 2021/1/13.
//

#include "../include/base64.h"


Base64::Base64() {
    static char b64Words[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3',
            '4', '5', '6', '7', '8', '9', '+', '/'
    };
    mB64Words = b64Words;

    static bool initTable = false;
    static unsigned char b64Table[256];
    mB64Table = b64Table;

    if (!initTable) {
        for (auto & i : b64Table) {
            i = -1;
        }

        for (auto i = 0; i < 64; i++) {
            b64Table[b64Words[i]] = i;
        }
        initTable = true;
    }
}

Base64::~Base64() = default;

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

        out[index] = mB64Words[a];
        out[index+1] = mB64Words[b];
        out[index+2] = mB64Words[c];
        out[index+3] = mB64Words[d];
    }

    if (left == 1) {
        auto a = buf[i] >> 2;
        auto b = (buf[i] << 4) & 0x3f;

        out[index] = mB64Words[a];
        out[index+1] = mB64Words[b];
        out[index+2] = '=';
        out[index+3] = '=';
    }else if (left == 2) {
        auto a = buf[i] >> 2;
        auto b = ((buf[i] << 4) | (buf[i+1] >> 4)) & 0x3f;
        auto c = (buf[i+1] << 2) & 0x3f;

        out[index] = mB64Words[a];
        out[index+1] = mB64Words[b];
        out[index+2] = mB64Words[c];
        out[index+3] = '=';
    }
}

void Base64::b64Decode(string &str, vector<unsigned char> &out) const {
    out.clear();

    int temp = 0;
    int bitLen = 0;

    for (auto & c : str) {
        if (c == '=' or mB64Table[c] == 0xff) break;
        temp <<= 6;
        bitLen += 6;
        temp |= mB64Table[c];

        while (bitLen >= 8) {
            out.push_back(static_cast<char>(temp >> (bitLen - 8)));
            bitLen -= 8;
        }
    }
}