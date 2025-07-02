/* md5.h - header file for md5.c */
/* License: Public domain */
#include <stddef.h>

#ifndef MD5_H
#define MD5_H

#include <stdint.h>

typedef struct {
  uint32_t h[4];
  uint32_t data[16];
  uint32_t datalen;
  uint64_t bitlen;
} MD5_CTX;

void md5_init(MD5_CTX *ctx);
void md5_update(MD5_CTX *ctx, const uint8_t *data, size_t len);
void md5_final(MD5_CTX *ctx, uint8_t *hash);
void md5_string(const char *str, char *output);

#endif /* MD5_H */
