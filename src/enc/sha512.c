#include "sha512.h"
#include <memory.h> /* memset */

#define MAX_UINT64    (0xFFFFFFFFFFFFFFFFULL)
#define MAX_UINT32    (0xFFFFFFFF)
#define MAX_UINT8     (0xFF)

/**
 * 64 bit right shift 
 */
#define shr64(x, n)  (((unsigned long long)(x) & MAX_UINT64) >> ((unsigned long long)(n)))

/**
 * 64 bit left shift 
 */
#define shl64(x, n)  (((unsigned long long)(x) & MAX_UINT64) << ((unsigned long long)(n)))

/**
 * 32 bit right shift 
 */
#define shr32(x, n)  (((unsigned int)((x) >> (n))) & MAX_UINT32) 

/**
 * 8 bit right shift 
 */
#define shr8(x, n)   (((unsigned char)((x) >> (n))) & MAX_UINT8) 

/**
 * 64 bit right rotate 
 */
#define rotr64(x, n) (((((x) & MAX_UINT64) >> ((unsigned long long)(n) & (63ULL))) | ((x) << ((unsigned long long)(64 - ((n) & (63ULL)))))) & MAX_UINT64)

/**
 * operations from spec 
 */
#define ch(x,y,z)    (((x) & (y)) ^ ((~x) & (z)))
#define maj(x,y,z)   (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define s0(x)        (rotr64((x), (28)) ^ rotr64((x), (34)) ^ rotr64((x), (39)))
#define s1(x)        (rotr64((x), (14)) ^ rotr64((x), (18)) ^ rotr64((x), (41)))
#define g0(x)        (rotr64((x), (1))  ^ rotr64((x), (8))  ^ shr64((x), (7)))
#define g1(x)        (rotr64((x), (19)) ^ rotr64((x), (61)) ^ shr64((x), (6)))

/**
 * initial hash values 
 */
static const unsigned long long H[8] = 
{
  0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL, 
  0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
};

/**
 * round constants 
 */
static const unsigned long long K[80] = 
{
  0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 
  0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 
  0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
  0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL, 
  0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 
  0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
  0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 
  0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 
  0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
  0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL, 
  0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 
  0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
  0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 
  0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL, 
  0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
  0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 
  0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
  0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
  0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL, 
  0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

/**
 * processes a chunk 
 */
void sha512_process_chunk(unsigned long long* hash64, const unsigned char *chunk) 
{
  int i;
  unsigned long long W[80], L[8], T1, T2;

  for(i = 0; i < 16; i++) 
  {
    W[i] = shl64(chunk[i * 8], 0x38);
    W[i] |= shl64(chunk[i * 8 + 1], 0x30); 
    W[i] |= shl64(chunk[i * 8 + 2], 0x28);
    W[i] |= shl64(chunk[i * 8 + 3], 0x20); 
    W[i] |= shl64(chunk[i * 8 + 4], 0x18); 
    W[i] |= shl64(chunk[i * 8 + 5], 0x10);
    W[i] |= shl64(chunk[i * 8 + 6], 0x8); 
    W[i] |= (unsigned long long)chunk[i * 8 + 7];
  }
  for (i = 16; i < 80; i++) W[i] = g1(W[i - 2]) + W[i - 7] + g0(W[i - 15]) + W[i - 16];
  for (i = 0; i < 8; i++) L[i] = hash64[i];
  for (i = 0; i < 80; i++) 
  {
    T1 = L[7] + s1(L[4]) + ch(L[4], L[5], L[6]) + K[i] + W[i];
    T2 = s0(L[0]) + maj(L[0], L[1], L[2]);
    L[7] = L[6];
    L[6] = L[5];
    L[5] = L[4];
    L[4] = L[3] + T1;
    L[3] = L[2];
    L[2] = L[1];
    L[1] = L[0];
    L[0] = T1 + T2;
  }

  /* compute intermediate hash value */
  for (i = 0; i < 8; i++) hash64[i] += L[i];
}

void sha512_hash(unsigned int* hash, const unsigned char* plain, unsigned int length)
{
  int i; 
  unsigned int offset = 0;
  unsigned long long hash64[8], bit_length;
  unsigned char chunk[128];
  unsigned int padding_length;

  if (!hash || !plain) return;

  /* preprocess */
  bit_length = length * 8ULL;
  memcpy(hash64, H, sizeof(H));

  /* compute chunks */
  while (length >= 128) 
  {
    memcpy(chunk, plain + offset, 128);
    offset += 128;
    length -= 128;
    sha512_process_chunk(hash64, chunk);
  }

  if (length) memcpy(chunk, plain + offset, length);

  /* append "1" bit at the end of plain message */
  chunk[length] = 0x80;
  length++;

  /* if there's not enough space for bit length go for 1 more chunk */
  if (length > 112) 
  {
    memset(chunk + length, 0, (128 - length));
    sha512_process_chunk(hash64, chunk);
    length = 0;
  }

  /* append padding*/
  padding_length = (120 - length);
  memset(chunk + length, 0, padding_length);

  /* append bit length */
  chunk[120] = shr8(bit_length, 0x38);
  chunk[121] = shr8(bit_length, 0x30);
  chunk[122] = shr8(bit_length, 0x28);
  chunk[123] = shr8(bit_length, 0x20);
  chunk[124] = shr8(bit_length, 0x18);
  chunk[125] = shr8(bit_length, 0x10);
  chunk[126] = shr8(bit_length, 0x8);
  chunk[127] = (unsigned char)(bit_length & MAX_UINT8);

  /* compute final chunk */
  sha512_process_chunk(hash64, chunk);

  for (i = 0; i < 8; i++) 
  {
    hash[i * 2] = shr32(hash64[i], 0x20);
    hash[i * 2 + 1] = (unsigned int)(hash64[i] & MAX_UINT32);
  }

}
