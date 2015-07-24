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
*  abstract:  3x3 matrix
*/ 

#ifndef __VISUEM_MATRIX3_H__
#define __VISUEM_MATRIX3_H__

#include "vector3.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief matrix3 type 
   */
  typedef struct 
  {
    float tuples[9];    /* elements of matrix */
  } matrix3;

  /**
   * /brief copies matrix into an array 
   */
  extern void matrix3_copy_to_array(const matrix3* matrix, float* array_);

  /**
   * /brief loads matrix from float tuple values 
   */
  extern void matrix3_from_values(matrix3* target, const float t0, const float t1, const float t2, const float t3, const float t4, const float t5, const float t6, const float t7, const float t8);

  /**
   * /brief loads matrix from float array 
   */
  extern void matrix3_from_array(matrix3* target, const float* array_);

  /**
   * /brief Loads identity matrix. 
   */
  extern void matrix3_identity(matrix3* matrix);

  /**
   * /brief Adds two matrices 
   */
  extern void matrix3_add(matrix3* target, const matrix3* matrix, const matrix3* other);

  /**
   * /brief Subtracts a matrix from another 
   */
  extern void matrix3_sub(matrix3* target, const matrix3* matrix, const matrix3* other);

  /**
   * /brief Multiplies two matrices 
   */
  extern void matrix3_mul(matrix3* target, const matrix3* matrix, const matrix3* other);

  /**
   * /brief Multiplies a matrix and a scalar 
   */
  extern void matrix3_mul_scalar(matrix3* target, const matrix3* matrix, const float scalar);

  /**
   * /brief Multiplies a matrix and a vector 
   */
  extern void matrix3_mul_vector(vector3* target, const matrix3* matrix, const vector3* vector);

  /**
   * /brief Equality check. 
   */
  extern int matrix3_equal(const matrix3* matrix, const matrix3* other);

  /**
   * /brief Matrix copy. 
   */
  extern void matrix3_copy(matrix3* target, const matrix3* matrix);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
