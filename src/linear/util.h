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
*  date:      feb 6th, 2006
*  abstract:  math utils
*/ 

#ifndef __VISUEM_MATH_UTIL_H__
#define __VISUEM_MATH_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define math_grad_pi    0.0174532925f
#define math_grad_pi2   57.2957795131f
#define math_epsilon    0.000001f

  /** 
   * /brief compares equality between two float values. 
   */
  extern int math_fequal(const float float1, const float float2, const float epsilon);

  /** 
   * /brief converts a radian value to degrees. 
   */
  extern float math_radian_to_degree(const float radian);

  /** 
   * /brief converts a degree value to radians. 
   */
  extern float math_degree_to_radian(const float degree);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
