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
*  date:      feb 4th, 2008
*  abstract:  image
*/

#ifndef __VISUEM_IMAGE_H__
#define __VISUEM_IMAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief specifies supported color formats 
   */
  typedef enum 
  {
    cf_alpha,         /* 8bits single channel alpha */
    cf_gray,          /* 8bits single channel luminence */
    cf_gray_alpha,    /* 16bits grey and alpha */
    cf_rgb_24,        /* R8G8B8 */
    cf_rgba_32,       /* R8G8B8A8 */
    cf_bgr_24,        /* B8G8R8 */
    cf_bgra_32,       /* B8G8R8A8 */
    cf_depth,         /* 32 bits depth component */
  } color_format;

  /** 
   * /brief image structure
   */
  typedef struct 
  {   
    int               width;        /* width of the image canvas */
    int               height;       /* height of the image canvas */
    color_format      format;       /* color format of image */
    unsigned char*    buffer;       /* image data */               
  } image; 

  /**
   * /brief creates an image 
   */
  extern image* image_alloc(int width, int height, color_format format);

  /**
   * /brief deletes an image 
   */
  extern void image_free(image* image_);

  /** 
   * /brief updates an image with specified buffer 
   */
  extern void image_update(image* image_, int x, int y, int width, int height, unsigned char* data);

  /**
   * /brief returns a pixel of image
   */
  extern char image_get_pixel(image* image_, int x, int y);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
