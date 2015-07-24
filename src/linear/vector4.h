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
*  abstract:  4d vector
*/

#ifndef __VISUEM_VECTOR4_H__
#define __VISUEM_VECTOR4_H__

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief vector4 type 
   */
  typedef struct 
  {
    float tuples[4];
  } vector4;

  /**
   * /brief blends values with another vector 
   */
  extern void vector4_blend(vector4* target, const vector4* vector, const vector4* other, const float amount); 

  /**
   * /brief sets vector's values as maximum of itself and another vector's values. 
   */
  extern void vector4_ceil(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief returns the middle point of the 2 vectors 
   */
  extern void vector4_center(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief clamps vector's values in given range 
   */
  extern void vector4_clamp(vector4* target, const vector4* vector, const float min, const float max);

  /**
   * /brief copies values into an array 
   */
  extern void vector4_copy_to_array(const vector4* vector, float* array_);

  /**
   * /brief calculates the distance from another vector 
   */
  extern float vector4_distance(const vector4* vector, const vector4* other);

  /**
   * /brief sets vector's values as minimum of itself and another vector's values. 
   */
  extern void vector4_floor(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief loads vector from float tuple values 
   */
  extern void vector4_from_values(vector4* target, const float t0, const float t1, const float t2, const float t3);

  /**
   * /brief loads vector from float array 
   */
  extern void vector4_from_array(vector4* target, const float* array_);

  /**
   * /brief linearly interpolates two vectors into target vector 
   */
  extern void vector4_lerp(vector4* target, const vector4* vector, const vector4* other, float amount);

  /**
   * /brief inverts vector 
   */
  extern void vector4_invert(vector4* target, const vector4* vector);

  /**
   * /brief calculates the squared length of vector 
   */
  extern float vector4_length_square(const vector4* vector);

  /**
   * /brief reflect vector over a normal 
   */
  extern void vector4_reflect(vector4* target, const vector4* vector, const vector4* normal);

  /**
   * /brief resets vector data 
   */
  extern void vector4_reset(vector4* vector);

  /**
   * /brief clamps vector's values between [0, 1] 
   */
  extern void vector4_saturate(vector4* target, const vector4* vector);

  /**
   * /brief Normalizes vector. 
   */
  extern void vector4_normalize(vector4* target, const vector4* vector);

  /**
   * /brief Returns dot product of two vectors. 
   */
  extern float vector4_dot(const vector4* vector, const vector4* other);

  /**
   * /brief Returns the length of a vector 
   */
  extern float vector4_length(const vector4* vector);

  /**
   * /brief Adds two vector 
   */
  extern void vector4_add(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief Adds a vector and a scalar 
   */
  extern void vector4_add_scalar(vector4* target, const vector4* vector, const float scalar);

  /**
   * /brief Subtracts a vector from another 
   */
  extern void vector4_sub(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief Subtracts a scalar from vector 
   */
  extern void vector4_sub_scalar(vector4* target, const vector4* vector, const float scalar);

  /**
   * /brief Multiplies two vectors 
   */
  extern void vector4_mul(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief Multiplies a vector and a scalar
   */
  extern void vector4_mul_scalar(vector4* target, const vector4* vector, const float scalar);

  /**
   * /brief Divides a vector by another 
   */
  extern void vector4_div(vector4* target, const vector4* vector, const vector4* other);

  /**
   * /brief Divides a vector by a scalar 
   */
  extern void vector4_div_scalar(vector4* target, const vector4* vector, const float scalar);

  /**
   * /brief Equality check. 
   */
  extern int vector4_equal(const vector4* vector, const vector4* other);

  /**
   * /brief Vector copy. 
   */
  extern void vector4_copy(vector4* target, const vector4* vector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
