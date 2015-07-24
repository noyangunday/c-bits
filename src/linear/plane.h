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
*  date:      feb 7th, 2006
*  abstract:  3d plane
*/

#ifndef __VISUEM_PLANE_H__
#define __VISUEM_PLANE_H__

#include "vector3.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief defines a plane in 3d space (ax * by * cz * d = 0)
   */
  typedef struct 
  {
    vector3 normal;       /* plane normal */
    float distance;       /* plane distance */
  } plane;

  /**
   * /brief resets the plane 
   */
  extern void plane_reset(plane* plane_);

  /**
   * /brief normalizes the plane 
   */
  extern void plane_normalize(plane* target, const plane* plane_);

  /**
   * /brief load plane from values 
   */
  extern void plane_from_values(plane* plane_, const float a, const float b, const float c, const float d);

  /**
   * /brief load plane from a normal and a distance 
   */
  extern void plane_from_nd(plane* plane_, const vector3* normal, const float distance);

  /**
   * /brief Equality comparison. 
   */
  extern int plane_equal(const plane* plane_, const plane* other);

  /**
   * /brief plane copy. 
   */
  extern void plane_copy(plane* target, const plane* plane_);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
