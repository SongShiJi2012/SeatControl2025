#ifndef HEADER_MODES_H
#define HEADER_MODES_H

#include <stddef.h> // size_t

typedef void (*block128_f) ( const void *key, const unsigned char in[16],
                            unsigned char out[16]);

typedef void (*cbc128_f) (const unsigned char *in, unsigned char *out,
                          size_t len, const void *key,
                          unsigned char ivec[16], int enc);

typedef void (*ctr128_f) (const unsigned char *in, unsigned char *out,
                          size_t blocks, const void *key,
                          const unsigned char ivec[16]);
                          
void CRYPTO_cbc128_encrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16], block128_f block);
void CRYPTO_cbc128_decrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16], block128_f block);


#endif /* HEADER_MODES_H */
