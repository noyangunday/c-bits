#include "vector4.h"
#include "util.h"
#include <math.h> /* sqrt */

void vector4_blend(vector4* target, const vector4* vector, const vector4* other, const float amount) 
{
  const float one_minus_amount = 1.0f - amount;
  target->tuples[0] = vector->tuples[0] * amount + other->tuples[0] * one_minus_amount; 
  target->tuples[1] = vector->tuples[1] * amount + other->tuples[1] * one_minus_amount; 
  target->tuples[2] = vector->tuples[2] * amount + other->tuples[2] * one_minus_amount; 
  target->tuples[3] = vector->tuples[3] * amount + other->tuples[3] * one_minus_amount; 
}

void vector4_ceil(vector4* target, const vector4* vector, const vector4* other) 
{
  target->tuples[0] = vector->tuples[0] < other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] < other->tuples[1] ? other->tuples[1] : vector->tuples[1];
  target->tuples[2] = vector->tuples[2] < other->tuples[2] ? other->tuples[2] : vector->tuples[2];
  target->tuples[3] = vector->tuples[3] < other->tuples[3] ? other->tuples[3] : vector->tuples[3];
}

void vector4_center(vector4* target, const vector4* vector, const vector4* other) 
{
  target->tuples[0] = (vector->tuples[0] + other->tuples[0]) / 2.0f; 
  target->tuples[1] = (vector->tuples[1] + other->tuples[1]) / 2.0f; 
  target->tuples[2] = (vector->tuples[2] + other->tuples[2]) / 2.0f; 
  target->tuples[3] = (vector->tuples[3] + other->tuples[3]) / 2.0f; 
}

void vector4_clamp(vector4* target, const vector4* vector, const float min, const float max) 
{
  target->tuples[0] = vector->tuples[0] > max ? max : (vector->tuples[0] < min ? min : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > max ? max : (vector->tuples[1] < min ? min : vector->tuples[1]);
  target->tuples[2] = vector->tuples[2] > max ? max : (vector->tuples[2] < min ? min : vector->tuples[2]);
  target->tuples[3] = vector->tuples[3] > max ? max : (vector->tuples[3] < min ? min : vector->tuples[3]);
}

void vector4_copy_to_array(const vector4* vector, float* array_) 
{
  array_[0] = vector->tuples[0];
  array_[1] = vector->tuples[1];
  array_[2] = vector->tuples[2];
  array_[3] = vector->tuples[3];
}

float vector4_distance(const vector4* vector, const vector4* other) 
{
  vector4 temp;
  vector4_sub(&temp, vector, other);
  return vector4_length(&temp);
}

void vector4_floor(vector4* target, const vector4* vector, const vector4* other) 
{
  target->tuples[0] = vector->tuples[0] > other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] > other->tuples[1] ? other->tuples[1] : vector->tuples[1];
  target->tuples[2] = vector->tuples[2] > other->tuples[2] ? other->tuples[2] : vector->tuples[2];
  target->tuples[3] = vector->tuples[3] > other->tuples[3] ? other->tuples[3] : vector->tuples[3];
}

void vector4_from_values(vector4* target, const float t0, const float t1, const float t2, const float t3)
{
  target->tuples[0] = t0;
  target->tuples[1] = t1;
  target->tuples[2] = t2;
  target->tuples[3] = t3;
}

void vector4_from_array(vector4* target, const float* array_) 
{
  target->tuples[0] = array_[0];
  target->tuples[1] = array_[1];
  target->tuples[2] = array_[2];
  target->tuples[3] = array_[3];
}

void vector4_lerp(vector4* target, const vector4* vector, const vector4* other, float amount) 
{
  target->tuples[0] = vector->tuples[0] + (other->tuples[0] - vector->tuples[0]) * amount;
  target->tuples[1] = vector->tuples[1] + (other->tuples[1] - vector->tuples[1]) * amount;
  target->tuples[2] = vector->tuples[2] + (other->tuples[2] - vector->tuples[2]) * amount;
  target->tuples[3] = vector->tuples[3] + (other->tuples[3] - vector->tuples[3]) * amount;
}

void vector4_invert(vector4* target, const vector4* vector) 
{
  target->tuples[0] = -vector->tuples[0];
  target->tuples[1] = -vector->tuples[1];
  target->tuples[2] = -vector->tuples[2];
  target->tuples[3] = -vector->tuples[3];
}

float vector4_length_square(const vector4* vector) 
{
  return vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1] + vector->tuples[2] * vector->tuples[2] + vector->tuples[3] * vector->tuples[3];
}

void vector4_reflect(vector4* target, const vector4* vector, const vector4* normal) 
{
  vector4 temp;
  float two_dot;

  /* r = v1 - (n * (n.v) * 2) */
  two_dot = vector4_dot(vector, normal) * 2.0f;
  vector4_mul_scalar(&temp, normal, two_dot);
  vector4_sub(target, vector, &temp);
}

void vector4_reset(vector4* vector) 
{
  vector->tuples[0] = 0.0f;
  vector->tuples[1] = 0.0f;
  vector->tuples[2] = 0.0f;
  vector->tuples[3] = 0.0f;
}

void vector4_saturate(vector4* target, const vector4* vector) 
{
  target->tuples[0] = vector->tuples[0] > 1.0f ? 1.0f : (vector->tuples[0] < 0.0f ? 0.0f : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > 1.0f ? 1.0f : (vector->tuples[1] < 0.0f ? 0.0f : vector->tuples[1]);
  target->tuples[2] = vector->tuples[2] > 1.0f ? 1.0f : (vector->tuples[2] < 0.0f ? 0.0f : vector->tuples[2]);
  target->tuples[3] = vector->tuples[3] > 1.0f ? 1.0f : (vector->tuples[3] < 0.0f ? 0.0f : vector->tuples[3]);
}

void vector4_normalize(vector4* target, const vector4* vector)
{
  float inv_length = 1.0f / vector4_length(vector);
  target->tuples[0] = vector->tuples[0] * inv_length;
  target->tuples[1] = vector->tuples[1] * inv_length;
  target->tuples[2] = vector->tuples[2] * inv_length;
  target->tuples[3] = vector->tuples[3] * inv_length;
}

float vector4_dot(const vector4* vector, const vector4* other)
{
  return 
    vector->tuples[0] * other->tuples[0] + vector->tuples[1] * other->tuples[1] + 
    vector->tuples[2] * other->tuples[2] + vector->tuples[3] * other->tuples[3];
}

float vector4_length(const vector4* vector)
{
  return sqrt(vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1] + vector->tuples[2] * vector->tuples[2] + vector->tuples[3] * vector->tuples[3]);
}

void vector4_add(vector4* target, const vector4* vector, const vector4* other)
{
  target->tuples[0] = vector->tuples[0] + other->tuples[0];
  target->tuples[1] = vector->tuples[1] + other->tuples[1];
  target->tuples[2] = vector->tuples[2] + other->tuples[2];
  target->tuples[3] = vector->tuples[3] + other->tuples[3];
}

void vector4_add_scalar(vector4* target, const vector4* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] + scalar;
  target->tuples[1] = vector->tuples[1] + scalar;
  target->tuples[2] = vector->tuples[2] + scalar;
  target->tuples[3] = vector->tuples[3] + scalar;
}

void vector4_sub(vector4* target, const vector4* vector, const vector4* other)
{
  target->tuples[0] = vector->tuples[0] - other->tuples[0];
  target->tuples[1] = vector->tuples[1] - other->tuples[1];
  target->tuples[2] = vector->tuples[2] - other->tuples[2];
  target->tuples[3] = vector->tuples[3] - other->tuples[3];
}

void vector4_sub_scalar(vector4* target, const vector4* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] - scalar;
  target->tuples[1] = vector->tuples[1] - scalar;
  target->tuples[2] = vector->tuples[2] - scalar;
  target->tuples[3] = vector->tuples[3] - scalar;
}

void vector4_mul(vector4* target, const vector4* vector, const vector4* other)
{
  target->tuples[0] = vector->tuples[0] * other->tuples[0];
  target->tuples[1] = vector->tuples[1] * other->tuples[1];
  target->tuples[2] = vector->tuples[2] * other->tuples[2];
  target->tuples[3] = vector->tuples[3] * other->tuples[3];
}

void vector4_mul_scalar(vector4* target, const vector4* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] * scalar;
  target->tuples[1] = vector->tuples[1] * scalar;
  target->tuples[2] = vector->tuples[2] * scalar;
  target->tuples[3] = vector->tuples[3] * scalar;
}

void vector4_div(vector4* target, const vector4* vector, const vector4* other)
{
  target->tuples[0] = vector->tuples[0] / other->tuples[0];
  target->tuples[1] = vector->tuples[1] / other->tuples[1];
  target->tuples[2] = vector->tuples[2] / other->tuples[2];
  target->tuples[3] = vector->tuples[3] / other->tuples[3];
}

void vector4_div_scalar(vector4* target, const vector4* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] / scalar;
  target->tuples[1] = vector->tuples[1] / scalar;
  target->tuples[2] = vector->tuples[2] / scalar;
  target->tuples[3] = vector->tuples[3] / scalar;
}

int vector4_equal(const vector4* vector, const vector4* other)
{
  return 
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon) && 
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon) &&
    math_fequal(vector->tuples[2], other->tuples[2], math_epsilon) &&
    math_fequal(vector->tuples[3], other->tuples[3], math_epsilon);
}

void vector4_copy(vector4* target, const vector4* vector)
{
  target->tuples[0] = vector->tuples[0];
  target->tuples[1] = vector->tuples[1];
  target->tuples[2] = vector->tuples[2];
  target->tuples[3] = vector->tuples[3];
}
