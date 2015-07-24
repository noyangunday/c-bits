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
 *  abstract:  image loader
 */
#ifndef __VISUEM_IMAGE_IO_H__
#define __VISUEM_IMAGE_IO_H__

#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif

  /** 
   * /brief specifies loader types
   */
  typedef enum 
  {
    il_png,           /* use png loader to load image */
    il_jpeg,          /* use jpeg loader to load image */
    il_unknown,       /* unknown format. can't load. */
  } image_loader;

  /**
   * /brief loads an image with auto detected format from file
   */
  extern image* io_load_image(const char* path);

  /** 
   * /brief loads an image with specified format from file
   */
  extern image* io_load_image_with_type(const char* path, image_loader type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif