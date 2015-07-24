#include "vector3.h"
#include "util.h"
#include <math.h> /* sqrt */

void vector3_blend(vector3* target, const vector3* vector, const vector3* other, const float amount) 
{
  const float one_minus_amount = 1.0f - amount;
  target->tuples[0] = vector->tuples[0] * amount + other->tuples[0] * one_minus_amount; 
  target->tuples[1] = vector->tuples[1] * amount + other->tuples[1] * one_minus_amount; 
  target->tuples[2] = vector->tuples[2] * amount + other->tuples[2] * one_minus_amount; 
}

void vector3_ceil(vector3* target, const vector3* vector, const vector3* other) 
{
  target->tuples[0] = vector->tuples[0] < other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] < other->tuples[1] ? other->tuples[1] : vector->tuples[1];
  target->tuples[2] = vector->tuples[2] < other->tuples[2] ? other->tuples[2] : vector->tuples[2];
}

void vector3_center(vector3* target, const vector3* vector, const vector3* other) 
{
  target->tuples[0] = (vector->tuples[0] + other->tuples[0]) / 2.0f; 
  target->tuples[1] = (vector->tuples[1] + other->tuples[1]) / 2.0f; 
  target->tuples[2] = (vector->tuples[2] + other->tuples[2]) / 2.0f; 
}

void vector3_clamp(vector3* target, const vector3* vector, const float min, const float max) 
{
  target->tuples[0] = vector->tuples[0] > max ? max : (vector->tuples[0] < min ? min : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > max ? max : (vector->tuples[1] < min ? min : vector->tuples[1]);
  target->tuples[2] = vector->tuples[2] > max ? max : (vector->tuples[2] < min ? min : vector->tuples[2]);
}

void vector3_copy_to_array(const vector3* vector, float* array_) 
{
  array_[0] = vector->tuples[0];
  array_[1] = vector->tuples[1];
  array_[2] = vector->tuples[2];
}

float vector3_distance(const vector3* vector, const vector3* other) 
{
  vector3 temp;
  vector3_sub(&temp, vector, other);
  return vector3_length(&temp);
}

void vector3_floor(vector3* target, const vector3* vector, const vector3* other) 
{
  target->tuples[0] = vector->tuples[0] > other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] > other->tuples[1] ? other->tuples[1] : vector->tuples[1];
  target->tuples[2] = vector->tuples[2] > other->tuples[2] ? other->tuples[2] : vector->tuples[2];
}

void vector3_from_values(vector3* target, const float t0, const float t1, const float t2)
{
  target->tuples[0] = t0;
  target->tuples[1] = t1;
  target->tuples[2] = t2;
}

void vector3_from_array(vector3* target, const float* array_) 
{
  target->tuples[0] = array_[0];
  target->tuples[1] = array_[1];
  target->tuples[2] = array_[2];
}

void vector3_lerp(vector3* target, const vector3* vector, const vector3* other, float amount) 
{
  target->tuples[0] = vector->tuples[0] + (other->tuples[0] - vector->tuples[0]) * amount;
  target->tuples[1] = vector->tuples[1] + (other->tuples[1] - vector->tuples[1]) * amount;
  target->tuples[2] = vector->tuples[2] + (other->tuples[2] - vector->tuples[2]) * amount;
}

void vector3_invert(vector3* target, const vector3* vector) 
{
  target->tuples[0] = -vector->tuples[0];
  target->tuples[1] = -vector->tuples[1];
  target->tuples[2] = -vector->tuples[2];
}

float vector3_length_square(const vector3* vector) 
{
  return vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1] + vector->tuples[2] * vector->tuples[2];
}

void vector3_reflect(vector3* target, const vector3* vector, const vector3* normal) 
{
  vector3 temp;
  float two_dot;

  /* r = v1 - (n * (n.v) * 2) */
  two_dot = vector3_dot(vector, normal) * 2.0f;
  vector3_mul_scalar(&temp, normal, two_dot);
  vector3_sub(target, vector, &temp);
}

void vector3_reset(vector3* vector) 
{
  vector->tuples[0] = 0.0f;
  vector->tuples[1] = 0.0f;
  vector->tuples[2] = 0.0f;
}

void vector3_saturate(vector3* target, const vector3* vector) 
{
  target->tuples[0] = vector->tuples[0] > 1.0f ? 1.0f : (vector->tuples[0] < 0.0f ? 0.0f : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > 1.0f ? 1.0f : (vector->tuples[1] < 0.0f ? 0.0f : vector->tuples[1]);
  target->tuples[2] = vector->tuples[2] > 1.0f ? 1.0f : (vector->tuples[2] < 0.0f ? 0.0f : vector->tuples[2]);
}

void vector3_normalize(vector3* target, const vector3* vector)
{
  float inv_length = 1.0f / vector3_length(vector);

  target->tuples[0] = vector->tuples[0] * inv_length;
  target->tuples[1] = vector->tuples[1] * inv_length;
  target->tuples[2] = vector->tuples[2] * inv_length;
}

float vector3_dot(const vector3* vector, const vector3* other)
{
  return vector->tuples[0] * other->tuples[0] + vector->tuples[1] * other->tuples[1] + vector->tuples[2] * other->tuples[2];
}

void vector3_cross(vector3* target, const vector3* vector, const vector3* other)
{
  vector3 temp;
  temp.tuples[0] = vector->tuples[1] * other->tuples[2] - vector->tuples[2] * other->tuples[1];
  temp.tuples[1] = vector->tuples[2] * other->tuples[0] - vector->tuples[0] * other->tuples[2];
  temp.tuples[2] = vector->tuples[0] * other->tuples[1] - vector->tuples[1] * other->tuples[0];
  vector3_copy(target, &temp);
}

float vector3_length(const vector3* vector)
{
  return sqrt(vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1] + vector->tuples[2] * vector->tuples[2]);
}

void vector3_add(vector3* target, const vector3* vector, const vector3* other)
{
  target->tuples[0] = vector->tuples[0] + other->tuples[0];
  target->tuples[1] = vector->tuples[1] + other->tuples[1];
  target->tuples[2] = vector->tuples[2] + other->tuples[2];
}

void vector3_add_scalar(vector3* target, const vector3* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] + scalar;
  target->tuples[1] = vector->tuples[1] + scalar;
  target->tuples[2] = vector->tuples[2] + scalar;
}

void vector3_sub(vector3* target, const vector3* vector, const vector3* other)
{
  target->tuples[0] = vector->tuples[0] - other->tuples[0];
  target->tuples[1] = vector->tuples[1] - other->tuples[1];
  target->tuples[2] = vector->tuples[2] - other->tuples[2];
}

void vector3_sub_scalar(vector3* target, const vector3* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] - scalar;
  target->tuples[1] = vector->tuples[1] - scalar;
  target->tuples[2] = vector->tuples[2] - scalar;
}

void vector3_mul(vector3* target, const vector3* vector, const vector3* other)
{
  target->tuples[0] = vector->tuples[0] * other->tuples[0];
  target->tuples[1] = vector->tuples[1] * other->tuples[1];
  target->tuples[2] = vector->tuples[2] * other->tuples[2];
}

void vector3_mul_scalar(vector3* target, const vector3* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] * scalar;
  target->tuples[1] = vector->tuples[1] * scalar;
  target->tuples[2] = vector->tuples[2] * scalar;
}

void vector3_div(vector3* target, const vector3* vector, const vector3* other)
{
  target->tuples[0] = vector->tuples[0] / other->tuples[0];
  target->tuples[1] = vector->tuples[1] / other->tuples[1];
  target->tuples[2] = vector->tuples[2] / other->tuples[2];
}

void vector3_div_scalar(vector3* target, const vector3* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] / scalar;
  target->tuples[1] = vector->tuples[1] / scalar;
  target->tuples[2] = vector->tuples[2] / scalar;
}

int vector3_equal(const vector3* vector, const vector3* other)
{
  return 
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon) && 
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon) &&
    math_fequal(vector->tuples[2], other->tuples[2], math_epsilon);
}

void vector3_copy(vector3* target, const vector3* vector)
{
  target->tuples[0] = vector->tuples[0];
  target->tuples[1] = vector->tuples[1];
  target->tuples[2] = vector->tuples[2];
}
