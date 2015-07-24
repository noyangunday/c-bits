#include "matrix2.h"
#include "util.h"

void matrix2_copy_to_array(const matrix2* matrix, float* array_)
{
  array_[0] = matrix->tuples[0];
  array_[1] = matrix->tuples[1];
  array_[2] = matrix->tuples[2];
  array_[3] = matrix->tuples[3];
}

void matrix2_from_values(matrix2* target, const float t0, const float t1, const float t2, const float t3)
{
  target->tuples[0] = t0;
  target->tuples[1] = t1;
  target->tuples[2] = t2;
  target->tuples[3] = t3;
}

void matrix2_from_array(matrix2* target, const float* array_) 
{
  target->tuples[0] = array_[0];
  target->tuples[1] = array_[1];
  target->tuples[2] = array_[2];
  target->tuples[3] = array_[3];
}

void matrix2_identity(matrix2* matrix)
{
  matrix->tuples[0] = 1.0f;
  matrix->tuples[1] = 0.0f;
  matrix->tuples[2] = 0.0f;
  matrix->tuples[3] = 1.0f;
}

void matrix2_add(matrix2* target, const matrix2* matrix, const matrix2* other)
{
  target->tuples[0] = matrix->tuples[0] + other->tuples[0];
  target->tuples[1] = matrix->tuples[1] + other->tuples[1];
  target->tuples[2] = matrix->tuples[2] + other->tuples[2];
  target->tuples[3] = matrix->tuples[3] + other->tuples[3];
}

void matrix2_sub(matrix2* target, const matrix2* matrix, const matrix2* other)
{
  target->tuples[0] = matrix->tuples[0] - other->tuples[0];
  target->tuples[1] = matrix->tuples[1] - other->tuples[1];
  target->tuples[2] = matrix->tuples[2] - other->tuples[2];
  target->tuples[3] = matrix->tuples[3] - other->tuples[3];
}

void matrix2_mul(matrix2* target, const matrix2* matrix, const matrix2* other)
{
  matrix2 temp;
  temp.tuples[0] = matrix->tuples[0] * other->tuples[0] + matrix->tuples[1] * other->tuples[2]; 
  temp.tuples[1] = matrix->tuples[0] * other->tuples[1] + matrix->tuples[1] * other->tuples[3]; 
  temp.tuples[2] = matrix->tuples[2] * other->tuples[0] + matrix->tuples[3] * other->tuples[2]; 
  temp.tuples[3] = matrix->tuples[2] * other->tuples[1] + matrix->tuples[3] * other->tuples[3]; 
  matrix2_copy(target, &temp);
}

void matrix2_mul_scalar(matrix2* target, const matrix2* matrix, const float scalar)
{
  target->tuples[0] = matrix->tuples[0] * scalar;
  target->tuples[1] = matrix->tuples[1] * scalar;
  target->tuples[2] = matrix->tuples[2] * scalar;
  target->tuples[3] = matrix->tuples[3] * scalar;
}

void matrix2_mul_vector(vector2* target, const matrix2* matrix, const vector2* vector)
{
  vector2 temp;
  temp.tuples[0] = matrix->tuples[0] * vector->tuples[0] + matrix->tuples[2] * vector->tuples[1];
  temp.tuples[1] = matrix->tuples[1] * vector->tuples[0] + matrix->tuples[3] * vector->tuples[1];
  vector2_copy(target, &temp);
}

int matrix2_equal(const matrix2* matrix, const matrix2* other)
{
  return 
    math_fequal(matrix->tuples[0], other->tuples[0], math_epsilon) && 
    math_fequal(matrix->tuples[1], other->tuples[1], math_epsilon) &&
    math_fequal(matrix->tuples[2], other->tuples[2], math_epsilon) &&
    math_fequal(matrix->tuples[3], other->tuples[3], math_epsilon);
}


void matrix2_copy(matrix2* target, const matrix2* matrix)
{
  target->tuples[0] = matrix->tuples[0];
  target->tuples[1] = matrix->tuples[1];
  target->tuples[2] = matrix->tuples[2];
  target->tuples[3] = matrix->tuples[3];
}
