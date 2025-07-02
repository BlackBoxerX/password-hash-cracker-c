/* md5.c - implementation of MD5 */
/* License: Public domain */

#include "md5.h"
#include <string.h>
#include <stdio.h>

#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

static const uint32_t k[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static const uint32_t r[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

void md5_transform(MD5_CTX *ctx, const uint8_t data[]) {
    uint32_t a, b, c, d, m[16], i, f, g, temp;
    for (i = 0; i < 16; ++i)
        m[i] = (uint32_t)data[i * 4] | ((uint32_t)data[i * 4 + 1] << 8) |
               ((uint32_t)data[i * 4 + 2] << 16) | ((uint32_t)data[i * 4 + 3] << 24);

    a = ctx->h[0];
    b = ctx->h[1];
    c = ctx->h[2];
    d = ctx->h[3];

    for (i = 0; i < 64; ++i) {
        if (i < 16) {
            f = F(b, c, d);
            g = i;
        } else if (i < 32) {
            f = G(b, c, d);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(b, c, d);
            g = (3 * i + 5) % 16;
        } else {
            f = I(b, c, d);
            g = (7 * i) % 16;
        }
        temp = d;
        d = c;
        c = b;
        b = b + LEFTROTATE((a + f + k[i] + m[g]), r[i]);
        a = temp;
    }
    ctx->h[0] += a;
    ctx->h[1] += b;
    ctx->h[2] += c;
    ctx->h[3] += d;
}

void md5_init(MD5_CTX *ctx) {
    ctx->datalen = 0;
    ctx->bitlen = 0;
    ctx->h[0] = 0x67452301;
    ctx->h[1] = 0xefcdab89;
    ctx->h[2] = 0x98badcfe;
    ctx->h[3] = 0x10325476;
}

void md5_update(MD5_CTX *ctx, const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        ((uint8_t *)ctx->data)[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            md5_transform(ctx, (uint8_t *)ctx->data);
            ctx->bitlen += 512;
            ctx->datalen = 0;
        }
    }
}

void md5_final(MD5_CTX *ctx, uint8_t *hash) {
    uint32_t i = ctx->datalen;

    // Pad whatever data is left in the buffer.
    ((uint8_t *)ctx->data)[i++] = 0x80;
    while (i < 56)
        ((uint8_t *)ctx->data)[i++] = 0x00;

    // Append to the padding the total message's length in bits and transform.
    ctx->bitlen += ctx->datalen * 8;
    ctx->data[14] = (uint32_t)(ctx->bitlen);
    ctx->data[15] = (uint32_t)(ctx->bitlen >> 32);

    md5_transform(ctx, (uint8_t *)ctx->data);

    // Since MD5 uses little endian order, and SHA uses big endian, reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i]      = (ctx->h[0] >> (8 * i)) & 0xff;
        hash[i + 4]  = (ctx->h[1] >> (8 * i)) & 0xff;
        hash[i + 8]  = (ctx->h[2] >> (8 * i)) & 0xff;
        hash[i + 12] = (ctx->h[3] >> (8 * i)) & 0xff;
    }
}

void md5_string(const char *str, char *output) {
    uint8_t hash[16];
    MD5_CTX ctx;
    md5_init(&ctx);
    md5_update(&ctx, (const uint8_t *)str, strlen(str));
    md5_final(&ctx, hash);
    for (int i = 0; i < 16; i++)
        sprintf(output + i * 2, "%02x", hash[i]);
    output[32] = '\0';
}
