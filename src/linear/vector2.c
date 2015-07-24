#include "vector2.h"
#include "util.h"
#include <math.h> /* sin, cos, atan2, sqrt */

void vector2_blend(vector2* target, const vector2* vector, const vector2* other, const float amount) 
{
  const float one_minus_amount = 1.0f - amount;
  target->tuples[0] = vector->tuples[0] * amount + other->tuples[0] * one_minus_amount; 
  target->tuples[1] = vector->tuples[1] * amount + other->tuples[1] * one_minus_amount; 
}

void vector2_ceil(vector2* target, const vector2* vector, const vector2* other) 
{
  target->tuples[0] = vector->tuples[0] < other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] < other->tuples[1] ? other->tuples[1] : vector->tuples[1];
}

void vector2_center(vector2* target, const vector2* vector, const vector2* other) 
{
  target->tuples[0] = (vector->tuples[0] + other->tuples[0]) / 2.0f; 
  target->tuples[1] = (vector->tuples[1] + other->tuples[1]) / 2.0f; 
}

void vector2_clamp(vector2* target, const vector2* vector, const float min, const float max) 
{
  target->tuples[0] = vector->tuples[0] > max ? max : (vector->tuples[0] < min ? min : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > max ? max : (vector->tuples[1] < min ? min : vector->tuples[1]);
}

void vector2_copy_to_array(const vector2* vector, float* array_) 
{
  array_[0] = vector->tuples[0];
  array_[1] = vector->tuples[1];
}

float vector2_distance(const vector2* vector, const vector2* other) 
{
  vector2 temp;
  vector2_sub(&temp, vector, other);
  return vector2_length(&temp);
}

void vector2_floor(vector2* target, const vector2* vector, const vector2* other) 
{
  target->tuples[0] = vector->tuples[0] > other->tuples[0] ? other->tuples[0] : vector->tuples[0];
  target->tuples[1] = vector->tuples[1] > other->tuples[1] ? other->tuples[1] : vector->tuples[1];
}

void vector2_from_polar(vector2* target, const float length, const float angle) 
{
  target->tuples[0] = length * cos(angle);
  target->tuples[1] = length * sin(angle);
}

void vector2_from_values(vector2* target, const float t0, const float t1)
{
  target->tuples[0] = t0;
  target->tuples[1] = t1;
}

void vector2_from_array(vector2* target, const float* array_) 
{
  target->tuples[0] = array_[0];
  target->tuples[1] = array_[1];
}

void vector2_lerp(vector2* target, const vector2* vector, const vector2* other, float amount) 
{
  target->tuples[0] = vector->tuples[0] + (other->tuples[0] - vector->tuples[0]) * amount;
  target->tuples[1] = vector->tuples[1] + (other->tuples[1] - vector->tuples[1]) * amount;
}

void vector2_invert(vector2* target, const vector2* vector) 
{
  target->tuples[0] = -vector->tuples[0];
  target->tuples[1] = -vector->tuples[1];
}

float vector2_length_square(const vector2* vector) 
{
  return vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1];
}

void vector2_reflect(vector2* target, const vector2* vector, const vector2* normal) 
{
  vector2 temp;
  float two_dot;

  /* r = v1 - (n * (n.v) * 2) */
  two_dot = vector2_dot(vector, normal) * 2.0f;
  vector2_mul_scalar(&temp, normal, two_dot);
  vector2_sub(target, vector, &temp);
}

void vector2_reset(vector2* vector) 
{
  vector->tuples[0] = 0.0f;
  vector->tuples[1] = 0.0f;
}

void vector2_saturate(vector2* target, const vector2* vector) 
{
  target->tuples[0] = vector->tuples[0] > 1.0f ? 1.0f : (vector->tuples[0] < 0.0f ? 0.0f : vector->tuples[0]);
  target->tuples[1] = vector->tuples[1] > 1.0f ? 1.0f : (vector->tuples[1] < 0.0f ? 0.0f : vector->tuples[1]);
}

void vector2_normalize(vector2* target, const vector2* vector)
{
  float inv_length = 1.0f / vector2_length(vector);
  target->tuples[0] = vector->tuples[0] * inv_length;
  target->tuples[1] = vector->tuples[1] * inv_length;
}

float vector2_dot(const vector2* vector, const vector2* other)
{
  return vector->tuples[0] * other->tuples[0] + vector->tuples[1] * other->tuples[1];
}

float vector2_perpendicular_dot(const vector2* vector, const vector2* other)
{
  return vector->tuples[0] * other->tuples[1] - vector->tuples[1] * other->tuples[0];
}

float vector2_angle(const vector2* vector, const vector2* other)
{
  float radian = -atan2(vector2_perpendicular_dot(vector, other), vector2_dot(vector, other));
  return math_radian_to_degree(radian);
}

float vector2_length(const vector2* vector)
{
  return sqrt(vector->tuples[0] * vector->tuples[0] + vector->tuples[1] * vector->tuples[1]);
}

void vector2_add(vector2* target, const vector2* vector, const vector2* other)
{
  target->tuples[0] = vector->tuples[0] + other->tuples[0];
  target->tuples[1] = vector->tuples[1] + other->tuples[1];
}

void vector2_add_scalar(vector2* target, const vector2* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] + scalar;
  target->tuples[1] = vector->tuples[1] + scalar;
}

void vector2_sub(vector2* target, const vector2* vector, const vector2* other)
{
  target->tuples[0] = vector->tuples[0] - other->tuples[0];
  target->tuples[1] = vector->tuples[1] - other->tuples[1];
}

void vector2_sub_scalar(vector2* target, const vector2* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] - scalar;
  target->tuples[1] = vector->tuples[1] - scalar;
}

void vector2_mul(vector2* target, const vector2* vector, const vector2* other)
{
  target->tuples[0] = vector->tuples[0] * other->tuples[0];
  target->tuples[1] = vector->tuples[1] * other->tuples[1];
}

void vector2_mul_scalar(vector2* target, const vector2* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] * scalar;
  target->tuples[1] = vector->tuples[1] * scalar;
}

void vector2_div(vector2* target, const vector2* vector, const vector2* other)
{
  target->tuples[0] = vector->tuples[0] / other->tuples[0];
  target->tuples[1] = vector->tuples[1] / other->tuples[1];
}

void vector2_div_scalar(vector2* target, const vector2* vector, const float scalar)
{
  target->tuples[0] = vector->tuples[0] / scalar;
  target->tuples[1] = vector->tuples[1] / scalar;
}

void vector2_rotate(vector2* target, const vector2* vector, const float angle)
{
  vector2 temp;
  float r = math_degree_to_radian(angle);
  temp.tuples[0] = vector->tuples[0] * cos(r) + vector->tuples[1] * -sin(r);
  temp.tuples[1] = vector->tuples[0] * sin(r) + vector->tuples[1] * cos(r);
  target->tuples[0] = temp.tuples[0]; 
  target->tuples[1] = temp.tuples[1];
}

int vector2_equal(const vector2* vector, const vector2* other)
{
  return 
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon) &&
    math_fequal(vector->tuples[1], other->tuples[1], math_epsilon);
}

void vector2_copy(vector2* target, const vector2* vector)
{
  target->tuples[0] = vector->tuples[0];
  target->tuples[1] = vector->tuples[1];
}
