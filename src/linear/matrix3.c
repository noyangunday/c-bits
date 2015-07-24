#include "matrix3.h"
#include "util.h"

void matrix3_copy_to_array(const matrix3* matrix, float* array_)
{
  array_[0] = matrix->tuples[0];
  array_[1] = matrix->tuples[1];
  array_[2] = matrix->tuples[2];
  array_[3] = matrix->tuples[3];
  array_[4] = matrix->tuples[4];
  array_[5] = matrix->tuples[5];
  array_[6] = matrix->tuples[6];
  array_[7] = matrix->tuples[7];
  array_[8] = matrix->tuples[8];
}

void matrix3_from_values(matrix3* target, const float t0, const float t1, const float t2, const float t3, const float t4, const float t5, const float t6, const float t7, const float t8)
{
  target->tuples[0] = t0;
  target->tuples[1] = t1;
  target->tuples[2] = t2;
  target->tuples[3] = t3;
  target->tuples[4] = t4;
  target->tuples[5] = t5;
  target->tuples[6] = t6;
  target->tuples[7] = t7;
  target->tuples[8] = t8;
}

void matrix3_from_array(matrix3* target, const float* array_) 
{
  target->tuples[0] = array_[0];
  target->tuples[1] = array_[1];
  target->tuples[2] = array_[2];
  target->tuples[3] = array_[3];
  target->tuples[4] = array_[4];
  target->tuples[5] = array_[5];
  target->tuples[6] = array_[6];
  target->tuples[7] = array_[7];
  target->tuples[8] = array_[8];
}

void matrix3_identity(matrix3* matrix)
{
  matrix->tuples[0] = 1.0f;
  matrix->tuples[1] = 0.0f;
  matrix->tuples[2] = 0.0f;
  matrix->tuples[3] = 0.0f;
  matrix->tuples[4] = 1.0f;
  matrix->tuples[5] = 0.0f;
  matrix->tuples[6] = 0.0f;
  matrix->tuples[7] = 0.0f;
  matrix->tuples[8] = 1.0f;
}

void matrix3_add(matrix3* target, const matrix3* matrix, const matrix3* other)
{
  target->tuples[0] = matrix->tuples[0] + other->tuples[0];
  target->tuples[1] = matrix->tuples[1] + other->tuples[1];
  target->tuples[2] = matrix->tuples[2] + other->tuples[2];
  target->tuples[3] = matrix->tuples[3] + other->tuples[3];
  target->tuples[4] = matrix->tuples[4] + other->tuples[4];
  target->tuples[5] = matrix->tuples[5] + other->tuples[5];
  target->tuples[6] = matrix->tuples[6] + other->tuples[6];
  target->tuples[7] = matrix->tuples[7] + other->tuples[7];
  target->tuples[8] = matrix->tuples[8] + other->tuples[8];
}

void matrix3_sub(matrix3* target, const matrix3* matrix, const matrix3* other)
{
  target->tuples[0] = matrix->tuples[0] - other->tuples[0];
  target->tuples[1] = matrix->tuples[1] - other->tuples[1];
  target->tuples[2] = matrix->tuples[2] - other->tuples[2];
  target->tuples[3] = matrix->tuples[3] - other->tuples[3];
  target->tuples[4] = matrix->tuples[4] - other->tuples[4];
  target->tuples[5] = matrix->tuples[5] - other->tuples[5];
  target->tuples[6] = matrix->tuples[6] - other->tuples[6];
  target->tuples[7] = matrix->tuples[7] - other->tuples[7];
  target->tuples[8] = matrix->tuples[8] - other->tuples[8];
}

void matrix3_mul(matrix3* target, const matrix3* matrix, const matrix3* other)
{
  matrix3 temp;
  temp.tuples[0] = matrix->tuples[0] * other->tuples[0] + matrix->tuples[1] * other->tuples[3] + matrix->tuples[2] * other->tuples[6]; 
  temp.tuples[1] = matrix->tuples[0] * other->tuples[1] + matrix->tuples[1] * other->tuples[4] + matrix->tuples[2] * other->tuples[7]; 
  temp.tuples[2] = matrix->tuples[0] * other->tuples[2] + matrix->tuples[1] * other->tuples[5] + matrix->tuples[2] * other->tuples[8]; 
  temp.tuples[3] = matrix->tuples[3] * other->tuples[0] + matrix->tuples[4] * other->tuples[3] + matrix->tuples[5] * other->tuples[6]; 
  temp.tuples[4] = matrix->tuples[3] * other->tuples[1] + matrix->tuples[4] * other->tuples[4] + matrix->tuples[5] * other->tuples[7]; 
  temp.tuples[5] = matrix->tuples[3] * other->tuples[2] + matrix->tuples[4] * other->tuples[5] + matrix->tuples[5] * other->tuples[8]; 
  temp.tuples[6] = matrix->tuples[6] * other->tuples[0] + matrix->tuples[7] * other->tuples[3] + matrix->tuples[8] * other->tuples[6]; 
  temp.tuples[7] = matrix->tuples[6] * other->tuples[1] + matrix->tuples[7] * other->tuples[4] + matrix->tuples[8] * other->tuples[7]; 
  temp.tuples[8] = matrix->tuples[6] * other->tuples[2] + matrix->tuples[7] * other->tuples[5] + matrix->tuples[8] * other->tuples[8];  
  matrix3_copy(target, &temp);
}

void matrix3_mul_scalar(matrix3* target, const matrix3* matrix, const float scalar)
{
  target->tuples[0] = matrix->tuples[0] * scalar;
  target->tuples[1] = matrix->tuples[1] * scalar;
  target->tuples[2] = matrix->tuples[2] * scalar;
  target->tuples[3] = matrix->tuples[3] * scalar;
  target->tuples[4] = matrix->tuples[4] * scalar;
  target->tuples[5] = matrix->tuples[5] * scalar;
  target->tuples[6] = matrix->tuples[6] * scalar;
  target->tuples[7] = matrix->tuples[7] * scalar;
  target->tuples[8] = matrix->tuples[8] * scalar;
}

void matrix3_mul_vector(vector3* target, const matrix3* matrix, const vector3* vector)
{
  vector3 temp;  
  temp.tuples[0] = matrix->tuples[0] * vector->tuples[0] + matrix->tuples[3] * vector->tuples[1] + matrix->tuples[6] * vector->tuples[2]; 
  temp.tuples[1] = matrix->tuples[1] * vector->tuples[0] + matrix->tuples[4] * vector->tuples[1] + matrix->tuples[7] * vector->tuples[2]; 
  temp.tuples[2] = matrix->tuples[2] * vector->tuples[0] + matrix->tuples[5] * vector->tuples[1] + matrix->tuples[8] * vector->tuples[2];
  vector3_copy(target, &temp);
}

int matrix3_equal(const matrix3* matrix, const matrix3* other)
{
  return 
    math_fequal(matrix->tuples[0], other->tuples[0], math_epsilon) && 
    math_fequal(matrix->tuples[1], other->tuples[1], math_epsilon) &&
    math_fequal(matrix->tuples[2], other->tuples[2], math_epsilon) &&
    math_fequal(matrix->tuples[3], other->tuples[3], math_epsilon) &&
    math_fequal(matrix->tuples[4], other->tuples[4], math_epsilon) &&
    math_fequal(matrix->tuples[5], other->tuples[5], math_epsilon) &&
    math_fequal(matrix->tuples[6], other->tuples[6], math_epsilon) &&
    math_fequal(matrix->tuples[7], other->tuples[7], math_epsilon) &&
    math_fequal(matrix->tuples[8], other->tuples[8], math_epsilon);
}

void matrix3_copy(matrix3* target, const matrix3* matrix)
{
  target->tuples[0] = matrix->tuples[0];
  target->tuples[1] = matrix->tuples[1];
  target->tuples[2] = matrix->tuples[2];
  target->tuples[3] = matrix->tuples[3];
  target->tuples[4] = matrix->tuples[4];
  target->tuples[5] = matrix->tuples[5];
  target->tuples[6] = matrix->tuples[6];
  target->tuples[7] = matrix->tuples[7];
  target->tuples[8] = matrix->tuples[8];
}
