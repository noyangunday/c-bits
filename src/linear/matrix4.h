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
*  abstract:  4x4 matrix
*/

#ifndef __VISUEM_MATRIX4_H__
#define __VISUEM_MATRIX4_H__

#include "vector4.h"
#include "vector3.h"
#include "matrix3.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief matrix4 type 
   */
  typedef struct 
  {
    float tuples[16];   /* elements of matrix */
  } matrix4;

  /**
   * /brief copies matrix into an array 
   */
  extern void matrix4_copy_to_array(const matrix4* matrix, float* array_);

  /**
   * /brief loads matrix from float tuple values 
   */
  extern void matrix4_from_values(matrix4* target, const float t0, const float t1, const float t2, const float t3, const float t4, const float t5, const float t6, const float t7, const float t8, const float t9, const float t10, const float t11, const float t12, const float t13, const float t14, const float t15);

  /**
   * /brief loads matrix from float array 
   */
  extern void matrix4_from_array(matrix4* target, const float* array_);

  /**
   * /brief expands a 3x3 matrix to a 4x4 matrix 
   */
  extern void matrix4_from_matrix3(matrix4* target, const matrix3* matrix);

  /**
   * /brief Loads the identity matrix. 
   */
  extern void matrix4_identity(matrix4* matrix);

  /**
   * /brief Adds two matrices 
   */
  extern void matrix4_add(matrix4* target, const matrix4* matrix, const matrix4* other);

  /**
   * /brief Subtracts a matrix from another 
   */
  extern void matrix4_sub(matrix4* target, const matrix4* matrix, const matrix4* other);

  /**
   * /brief Multiplies two matrices 
   */
  extern void matrix4_mul(matrix4* target, const matrix4* matrix, const matrix4* other);

  /**
   * /brief Multiplies a matrix and a scalar 
   */
  extern void matrix4_mul_scalar(matrix4* target, const matrix4* matrix, const float scalar);

  /**
   * /brief Multiplies a matrix and a vector 
   */
  extern void matrix4_mul_vector(vector4* target, const matrix4* matrix, const vector4* vector);

  /**
   * /brief transposes a matrix 
   */
  extern void matrix4_transpose(matrix4* target, const matrix4* matrix);

  /**
   * /brief inverses a matrix 
   */
  extern void matrix4_invert(matrix4* target, const matrix4* matrix);

  /**
   * /brief calculates determinant of a matrix 
   */
  extern float matrix4_determinant(matrix4* matrix);

  /**
   * /brief translates matrix according to given translation vector 
   */
  extern void matrix4_translate(matrix4* target, const matrix4* matrix, const vector3* translation);

  /**
   * /brief translates matrix according to given translation vector 
   */
  extern void matrix4_translate_f(matrix4* target, const matrix4* matrix, const float translation_x, const float translation_y, const float translation_z);

  /**
   * /brief makes a translation matrix according to given translation value 
   */
  extern void matrix4_make_translation(matrix4* matrix, const vector3* translation);

  /**
   * /brief makes a translation matrix according to given translation value 
   */
  extern void matrix4_make_translation_f(matrix4* matrix, const float translation_x, const float translation_y, const float translation_z);

  /**
   * scales matrix according to given scale vector 
   */
  extern void matrix4_scale(matrix4* target, const matrix4* matrix, const vector3* scale);

  /**
   * /brief scales matrix according to given scale values 
   */
  extern void matrix4_scale_f(matrix4* target, const matrix4* matrix, const float scale_x, const float scale_y, const float scale_z);

  /**
   * /brief makes a scale matrix according to given scale vector 
   */
  extern void matrix4_make_scale(matrix4* matrix, const vector3* scale);

  /**
   * /brief makes a scale matrix according to given scale values 
   */
  extern void matrix4_make_scale_f(matrix4* matrix, const float scale_x, const float scale_y, const float scale_z);

  /**
   * /brief makes a perspective projection matrix 
   */
  extern void matrix4_make_perspective(matrix4* matrix, const float field_of_view, const float aspect_ratio, const float near_plane, const float far_plane);

  /**
   * /brief makes an orthographic projection matrix 
   */
  extern void matrix4_make_ortho(matrix4* matrix, const float left_plane, const float right_plane, const float bottom_plane, const float top_plane, const float near_plane, const float far_plane);

  /**
   * /brief defines a viewing transformation similar to glu's glulookat 
   */
  extern void matrix4_view(matrix4* matrix, const vector3* viewer, const vector3* target, const vector3* up);
  
  /**
   * /brief defines a viewing transformation similar to GLU's gluLookAt using float values 
   */
  extern void matrix4_view_f(matrix4* matrix, const float viewer_x, const float viewer_y, const float viewer_z, const float target_x, const float target_y, const float target_z, const float up_x, const float up_y, const float up_z);

  /**
   * /brief extracts a 3x3 matrix from a 4x4 matrix 
   */
  extern void matrix4_to_matrix3(matrix3* target, const matrix4* matrix);
  
  /**
   * /brief Equality check. 
   */
  extern int matrix4_equal(const matrix4* matrix, const matrix4* other);

  /**
   * /brief Matrix copy. 
   */
  extern void matrix4_copy(matrix4* target, const matrix4* matrix);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
