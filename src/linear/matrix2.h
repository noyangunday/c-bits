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
*  abstract:  2x2 matrix
*/ 

#ifndef __VISUEM_MATRIX2_H__
#define __VISUEM_MATRIX2_H__

#include "vector2.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief matrix2 type 
   */
  typedef struct 
  {
    float tuples[4];
  } matrix2;

  /**
   * /brief copies matrix into an array 
   */
  extern void matrix2_copy_to_array(const matrix2* matrix, float* array_);

  /**
   * /brief loads matrix from float tuple values 
   */
  extern void matrix2_from_values(matrix2* target, const float t0, const float t1, const float t2, const float t3);

  /**
   * /brief loads matrix from float array 
   */
  extern void matrix2_from_array(matrix2* target, const float* array_);

  /**
   * /brief Loads identity matrix. 
   */
  extern void matrix2_identity(matrix2* matrix);

  /**
   * /brief Adds two matrices 
   */
  extern void matrix2_add(matrix2* target, const matrix2* matrix, const matrix2* other);

  /**
   * /brief Subtracts a matrix from another 
   */
  extern void matrix2_sub(matrix2* target, const matrix2* matrix, const matrix2* other);

  /**
   * /brief Multiplies two matrices 
   */
  extern void matrix2_mul(matrix2* target, const matrix2* matrix, const matrix2* other);

  /**
   * /brief Multiplies a matrix and a scalar 
   */
  extern void matrix2_mul_scalar(matrix2* target, const matrix2* matrix, const float scalar);

  /**
   * /brief Multiplies a matrix and a vector 
   */
  extern void matrix2_mul_vector(vector2* target, const matrix2* matrix, const vector2* vector);

  /**
   * /brief Equality check. 
   */
  extern int matrix2_equal(const matrix2* matrix, const matrix2* other);

  /**
   * /brief Matrix copy. 
   */
  extern void matrix2_copy(matrix2* target, const matrix2* matrix);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
