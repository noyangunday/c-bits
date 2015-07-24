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
*  abstract:  3d vector
*/

#ifndef __VISUEM_VECTOR3_H__
#define __VISUEM_VECTOR3_H__

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief vector3 type 
   */
  typedef struct 
  {
    float tuples[3];
  } vector3;

  /**
   * /brief blends values with another vector 
   */
  extern void vector3_blend(vector3* target, const vector3* vector, const vector3* other, const float amount); 

  /**
   * /brief sets vector's values as maximum of itself and another vector's values. 
   */
  extern void vector3_ceil(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief returns the middle point of the 2 vectors 
   */
  extern void vector3_center(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief clamps vector's values in given range 
   */
  extern void vector3_clamp(vector3* target, const vector3* vector, const float min, const float max);

  /**
   * /brief copies values into an array 
   */
  extern void vector3_copy_to_array(const vector3* vector, float* array_);

  /**
   * /brief calculates the distance from another vector 
   */
  extern float vector3_distance(const vector3* vector, const vector3* other);

  /**
   * /brief sets vector's values as minimum of itself and another vector's values. 
   */
  extern void vector3_floor(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief loads vector from float tuple values 
   */
  extern void vector3_from_values(vector3* target, const float t0, const float t1, const float t2);

  /**
   * /brief loads vector from float array 
   */
  extern void vector3_from_array(vector3* target, const float* array_);

  /**
   * /brief linearly interpolates two vectors into this one 
   */
  extern void vector3_lerp(vector3* target, const vector3* vector, const vector3* other, float amount);

  /**
   * /brief inverts vector 
   */
  extern void vector3_invert(vector3* target, const vector3* vector);

  /**
   * /brief calculates the squared length of vector 
   */
  extern float vector3_length_square(const vector3* vector);

  /**
   * /brief reflect vector over a normal 
   */
  extern void vector3_reflect(vector3* target, const vector3* vector, const vector3* normal);

  /**
   * /brief resets vector data 
   */
  extern void vector3_reset(vector3* vector);

  /**
   * /brief clamps vector's values between [0, 1] 
   */
  extern void vector3_saturate(vector3* target, const vector3* vector);

  /**
   * /brief Normalizes vector. 
   */
  extern void vector3_normalize(vector3* target, const vector3* vector);

  /**
   * /brief Returns dot product of two vectors. 
   */
  extern float vector3_dot(const vector3* vector, const vector3* other);

  /**
   * /brief Returns cross product of two vectors. 
   */
  extern void vector3_cross(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief Returns the length of a vector 
   */
  extern float vector3_length(const vector3* vector);

  /**
   * /brief Adds two vector 
   */
  extern void vector3_add(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief Adds a vector and a scalar 
   */
  extern void vector3_add_scalar(vector3* target, const vector3* vector, const float scalar);

  /**
   * /brief Subtracts a vector from another 
   */
  extern void vector3_sub(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief Subtracts a scalar from vector 
   */
  extern void vector3_sub_scalar(vector3* target, const vector3* vector, const float scalar);

  /**
   * /brief Multiplies two vectors 
   */
  extern void vector3_mul(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief Multiplies a vector and a scalar 
   */
  extern void vector3_mul_scalar(vector3* target, const vector3* vector, const float scalar);

  /**
   * /brief Divides a vector by another 
   */
  extern void vector3_div(vector3* target, const vector3* vector, const vector3* other);

  /**
   * /brief Divides a vector by a scalar 
   */
  extern void vector3_div_scalar(vector3* target, const vector3* vector, const float scalar);

  /**
   * /brief Equality check. 
   */
  extern int vector3_equal(const vector3* vector, const vector3* other);

  /**
   * /brief Vector copy. 
   */
  extern void vector3_copy(vector3* target, const vector3* vector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif