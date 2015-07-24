/*

  The MIT License (MIT)

  Copyright (c) 2015 VISUEM LTD

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

/*
*  author:    noyan gunday
*  date:      apr 25th, 2006
*  abstract:  256-bit advanced encryption standard implementation with some optimization.
*  spec:      http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
*/

#ifndef __VISUEM_AES256_H__
#define __VISUEM_AES256_H__

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * encrypt a 128-bit block with aes256 
 */
extern void aes256_encrypt_block(const unsigned char* state, const unsigned char* key, unsigned char* out);

/** 
 * decrypt a 128-bit block with aes256 
 */
extern void aes256_decrypt_block(const unsigned char* state, const unsigned char* key, unsigned char* out);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

