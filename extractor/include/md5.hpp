#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>

namespace MD5 {
    namespace {
        typedef uint32_t uint4;
        typedef uint8_t uint1;

        inline uint4 F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }
        inline uint4 G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }
        inline uint4 H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }
        inline uint4 I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }

        inline uint4 rotate_left(uint4 x, int n) { return (x << n) | (x >> (32 - n)); }

        inline void FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, int s, uint4 ac) {
            a += F(b, c, d) + x + ac;
            a = rotate_left(a, s) + b;
        }

        inline void GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, int s, uint4 ac) {
            a += G(b, c, d) + x + ac;
            a = rotate_left(a, s) + b;
        }

        inline void HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, int s, uint4 ac) {
            a += H(b, c, d) + x + ac;
            a = rotate_left(a, s) + b;
        }

        inline void II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, int s, uint4 ac) {
            a += I(b, c, d) + x + ac;
            a = rotate_left(a, s) + b;
        }
    }

    std::string hash(const std::vector<unsigned char>& input) {
        uint4 a0 = 0x67452301;
        uint4 b0 = 0xefcdab89;
        uint4 c0 = 0x98badcfe;
        uint4 d0 = 0x10325476;

        std::vector<uint1> msg(input.begin(), input.end());
        size_t original_len = msg.size() * 8;
        msg.push_back(0x80);
        while ((msg.size() * 8) % 512 != 448) msg.push_back(0x00);

        for (int i = 0; i < 8; ++i)
            msg.push_back((uint1)((original_len >> (8 * i)) & 0xFF));

        for (size_t offset = 0; offset < msg.size(); offset += 64) {
            uint4 M[16];
            for (int i = 0; i < 16; ++i) {
                M[i] = ((uint4)msg[offset + i * 4 + 0]) |
                       ((uint4)msg[offset + i * 4 + 1] << 8) |
                       ((uint4)msg[offset + i * 4 + 2] << 16) |
                       ((uint4)msg[offset + i * 4 + 3] << 24);
            }

            uint4 A = a0, B = b0, C = c0, D = d0;

            FF(A, B, C, D, M[0], 7, 0xd76aa478);  FF(D, A, B, C, M[1], 12, 0xe8c7b756);
            FF(C, D, A, B, M[2], 17, 0x242070db); FF(B, C, D, A, M[3], 22, 0xc1bdceee);
            FF(A, B, C, D, M[4], 7, 0xf57c0faf);  FF(D, A, B, C, M[5], 12, 0x4787c62a);
            FF(C, D, A, B, M[6], 17, 0xa8304613); FF(B, C, D, A, M[7], 22, 0xfd469501);
            FF(A, B, C, D, M[8], 7, 0x698098d8);  FF(D, A, B, C, M[9], 12, 0x8b44f7af);
            FF(C, D, A, B, M[10],17, 0xffff5bb1); FF(B, C, D, A, M[11],22, 0x895cd7be);
            FF(A, B, C, D, M[12],7, 0x6b901122);  FF(D, A, B, C, M[13],12, 0xfd987193);
            FF(C, D, A, B, M[14],17, 0xa679438e); FF(B, C, D, A, M[15],22, 0x49b40821);

            GG(A, B, C, D, M[1], 5, 0xf61e2562);  GG(D, A, B, C, M[6], 9, 0xc040b340);
            GG(C, D, A, B, M[11],14, 0x265e5a51);GG(B, C, D, A, M[0], 20, 0xe9b6c7aa);
            GG(A, B, C, D, M[5], 5, 0xd62f105d);  GG(D, A, B, C, M[10],9, 0x02441453);
            GG(C, D, A, B, M[15],14, 0xd8a1e681); GG(B, C, D, A, M[4], 20, 0xe7d3fbc8);
            GG(A, B, C, D, M[9], 5, 0x21e1cde6);  GG(D, A, B, C, M[14],9, 0xc33707d6);
            GG(C, D, A, B, M[3], 14, 0xf4d50d87); GG(B, C, D, A, M[8], 20, 0x455a14ed);
            GG(A, B, C, D, M[13],5, 0xa9e3e905);  GG(D, A, B, C, M[2], 9, 0xfcefa3f8);
            GG(C, D, A, B, M[7], 14, 0x676f02d9); GG(B, C, D, A, M[12],20, 0x8d2a4c8a);

            HH(A, B, C, D, M[5], 4, 0xfffa3942);  HH(D, A, B, C, M[8], 11, 0x8771f681);
            HH(C, D, A, B, M[11],16, 0x6d9d6122);HH(B, C, D, A, M[14],23, 0xfde5380c);
            HH(A, B, C, D, M[1], 4, 0xa4beea44);  HH(D, A, B, C, M[4], 11, 0x4bdecfa9);
            HH(C, D, A, B, M[7], 16, 0xf6bb4b60); HH(B, C, D, A, M[10],23, 0xbebfbc70);
            HH(A, B, C, D, M[13],4, 0x289b7ec6);  HH(D, A, B, C, M[0], 11, 0xeaa127fa);
            HH(C, D, A, B, M[3], 16, 0xd4ef3085); HH(B, C, D, A, M[6], 23, 0x04881d05);
            HH(A, B, C, D, M[9], 4, 0xd9d4d039);  HH(D, A, B, C, M[12],11, 0xe6db99e5);
            HH(C, D, A, B, M[15],16, 0x1fa27cf8); HH(B, C, D, A, M[2], 23, 0xc4ac5665);

            II(A, B, C, D, M[0], 6, 0xf4292244);  II(D, A, B, C, M[7], 10, 0x432aff97);
            II(C, D, A, B, M[14],15, 0xab9423a7); II(B, C, D, A, M[5], 21, 0xfc93a039);
            II(A, B, C, D, M[12],6, 0x655b59c3);  II(D, A, B, C, M[3], 10, 0x8f0ccc92);
            II(C, D, A, B, M[10],15, 0xffeff47d); II(B, C, D, A, M[1], 21, 0x85845dd1);
            II(A, B, C, D, M[8], 6, 0x6fa87e4f);  II(D, A, B, C, M[15],10, 0xfe2ce6e0);
            II(C, D, A, B, M[6], 15, 0xa3014314); II(B, C, D, A, M[13],21, 0x4e0811a1);
            II(A, B, C, D, M[4], 6, 0xf7537e82);  II(D, A, B, C, M[11],10, 0xbd3af235);
            II(C, D, A, B, M[2], 15, 0x2ad7d2bb); II(B, C, D, A, M[9], 21, 0xeb86d391);

            a0 += A; b0 += B; c0 += C; d0 += D;
        }

        std::ostringstream result;
        for (uint4 word : {a0, b0, c0, d0}) {
            for (int i = 0; i < 4; ++i)
                result << std::hex << std::setw(2) << std::setfill('0') << ((word >> (8 * i)) & 0xff);
        }
        return result.str();
    }
}