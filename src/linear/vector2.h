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
*  abstract:  2d vector
*/

#ifndef __VISUEM_VECTOR2_H__
#define __VISUEM_VECTOR2_H__

#ifdef __cplusplus
extern "C" {
#endif

  /** 
   * /brief vector2 type 
   */
  typedef struct 
  {
    float tuples[2];
  } vector2;

  /** 
   * /brief blends values with another vector 
   */
  extern void vector2_blend(vector2* target, const vector2* vector, const vector2* other, const float amount); 

  /** 
   * /brief sets vector's values as maximum of itself and another vector's values. 
   */
  extern void vector2_ceil(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief returns the middle point of the 2 vectors 
   */
  extern void vector2_center(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief clamps vector's values in given range 
   */
  extern void vector2_clamp(vector2* target, const vector2* vector, const float min, const float max);

  /** 
   * /brief copies values into an array 
   */
  extern void vector2_copy_to_array(const vector2* vector, float* array_);

  /** 
   * /brief calculates the distance from another vector 
   */
  extern float vector2_distance(const vector2* vector, const vector2* other);

  /** 
   * /brief sets vector's values as minimum of itself and another vector's values. 
   */
  extern void vector2_floor(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief loads vector from polar coordinates 
   */
  extern void vector2_from_polar(vector2* target, const float length, const float angle);

  /** 
   * /brief loads vector from float tuple values 
   */
  extern void vector2_from_values(vector2* target, const float t0, const float t1);

  /** 
   * /brief loads vector from float array
   */
  extern void vector2_from_array(vector2* target, const float* array_);

  /** 
   * /brief linearly interpolates two vectors into this one 
   */
  extern void vector2_lerp(vector2* target, const vector2* vector, const vector2* other, float amount);

  /** 
   * /brief inverts vector 
   */
  extern void vector2_invert(vector2* target, const vector2* vector);

  /** 
   * /brief calculates the squared length of vector 
   */
  extern float vector2_length_square(const vector2* vector);

  /** 
   * /brief reflect vector over a normal 
   */
  extern void vector2_reflect(vector2* target, const vector2* vector, const vector2* normal);

  /** 
   * /brief resets vector data 
   */
  extern void vector2_reset(vector2* vector);

  /** 
   * /brief clamps vector's values between [0, 1] 
   */
  extern void vector2_saturate(vector2* target, const vector2* vector);

  /** 
   * /brief Normalizes vector. 
   */
  extern void vector2_normalize(vector2* target, const vector2* vector);

  /** 
   * /brief Returns dot product of two vectors. 
   */
  extern float vector2_dot(const vector2* vector, const vector2* other);

  /** 
   * /brief Returns perpendicular dot product of two vectors. 
   */
  extern float vector2_perpendicular_dot(const vector2* vector, const vector2* other);

  /** 
   * /brief Returns the angle between two vectors. 
   */
  extern float vector2_angle(const vector2* vector, const vector2* other);

  /** 
   * /brief Returns the length of a vector 
   */
  extern float vector2_length(const vector2* vector);

  /** 
   * /brief Adds two vector 
   */
  extern void vector2_add(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief Adds a vector and a scalar 
   */
  extern void vector2_add_scalar(vector2* target, const vector2* vector, const float scalar);

  /** 
   * /brief Subtracts a vector from another 
   */
  extern void vector2_sub(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief Subtracts a scalar from vector 
   */
  extern void vector2_sub_scalar(vector2* target, const vector2* vector, const float scalar);

  /** 
   * /brief Multiplies two vectors 
   */
  extern void vector2_mul(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief Multiplies a vector and a scalar 
   */
  extern void vector2_mul_scalar(vector2* target, const vector2* vector, const float scalar);

  /** 
   * /brief Divides a vector by another 
   */
  extern void vector2_div(vector2* target, const vector2* vector, const vector2* other);

  /** 
   * /brief Divides a vector by a scalar 
   */
  extern void vector2_div_scalar(vector2* target, const vector2* vector, const float scalar);

  /** 
   * /brief Rotates vector over origin 
   */
  extern void vector2_rotate(vector2* target, const vector2* vector, const float angle);

  /** 
   * /brief Equality check. 
   */
  extern int vector2_equal(const vector2* vector, const vector2* other);

  /** 
   * /brief Vector copy. 
   */
  extern void vector2_copy(vector2* target, const vector2* vector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
