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
*  date:      feb 5th, 2008
*  abstract:  png loader
*/

#ifndef __VISUEM_PNG_H__
#define __VISUEM_PNG_H__

#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif

  /** 
   * /brief checks if the file is a valid png 
   */
  extern int png_validate(const char* path);

  /** 
   * /brief loads png from file into an image 
   */
  extern image* png_load_from_file(const char* path);

  /** 
   * /brief saves an image as png 
   */
  extern void png_save_to_file(image* raw, const char* path);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
