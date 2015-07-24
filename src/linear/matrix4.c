#include "matrix4.h"
#include "util.h"
#include <math.h> /* tan */

void matrix4_copy_to_array(const matrix4* matrix, float* array_)
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
  array_[9] = matrix->tuples[9];
  array_[10] = matrix->tuples[10];
  array_[11] = matrix->tuples[11];
  array_[12] = matrix->tuples[12];
  array_[13] = matrix->tuples[13];
  array_[14] = matrix->tuples[14];
  array_[15] = matrix->tuples[15];
}

void matrix4_from_values(matrix4* target, const float t0, const float t1, const float t2, const float t3, const float t4, const float t5, const float t6, const float t7, const float t8, const float t9, const float t10, const float t11, const float t12, const float t13, const float t14, const float t15)
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
  target->tuples[9] = t9;
  target->tuples[10] = t10;
  target->tuples[11] = t11;
  target->tuples[12] = t12;
  target->tuples[13] = t13;
  target->tuples[14] = t14;
  target->tuples[15] = t15;
}

void matrix4_from_array(matrix4* target, const float* array_) 
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
  target->tuples[9] = array_[9];
  target->tuples[10] = array_[10];
  target->tuples[11] = array_[11];
  target->tuples[12] = array_[12];
  target->tuples[13] = array_[13];
  target->tuples[14] = array_[14];
  target->tuples[15] = array_[15];
}

void matrix4_identity(matrix4* matrix)
{
  matrix->tuples[0] = 1.0f;
  matrix->tuples[1] = 0.0f;
  matrix->tuples[2] = 0.0f;
  matrix->tuples[3] = 0.0f;
  matrix->tuples[4] = 0.0f;
  matrix->tuples[5] = 1.0f;
  matrix->tuples[6] = 0.0f;
  matrix->tuples[7] = 0.0f;
  matrix->tuples[8] = 0.0f;
  matrix->tuples[9] = 0.0f;
  matrix->tuples[10] = 1.0f;
  matrix->tuples[11] = 0.0f;
  matrix->tuples[12] = 0.0f;
  matrix->tuples[13] = 0.0f;
  matrix->tuples[14] = 0.0f;
  matrix->tuples[15] = 1.0f;
}

void matrix4_add(matrix4* target, const matrix4* matrix, const matrix4* other)
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
  target->tuples[9] = matrix->tuples[9] + other->tuples[9];
  target->tuples[10] = matrix->tuples[10] + other->tuples[10];
  target->tuples[11] = matrix->tuples[11] + other->tuples[11];
  target->tuples[12] = matrix->tuples[12] + other->tuples[12];
  target->tuples[13] = matrix->tuples[13] + other->tuples[13];
  target->tuples[14] = matrix->tuples[14] + other->tuples[14];
  target->tuples[15] = matrix->tuples[15] + other->tuples[15];
}

void matrix4_sub(matrix4* target, const matrix4* matrix, const matrix4* other)
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
  target->tuples[9] = matrix->tuples[9] - other->tuples[9];
  target->tuples[10] = matrix->tuples[10] - other->tuples[10];
  target->tuples[11] = matrix->tuples[11] - other->tuples[11];
  target->tuples[12] = matrix->tuples[12] - other->tuples[12];
  target->tuples[13] = matrix->tuples[13] - other->tuples[13];
  target->tuples[14] = matrix->tuples[14] - other->tuples[14];
  target->tuples[15] = matrix->tuples[15] - other->tuples[15];
}

void matrix4_mul(matrix4* target, const matrix4* matrix, const matrix4* other)
{
  matrix4 temp;
  temp.tuples[0] = matrix->tuples[0] * other->tuples[0] + matrix->tuples[1] * other->tuples[4] + matrix->tuples[2] * other->tuples[8] + matrix->tuples[3] * other->tuples[12]; 
  temp.tuples[1] = matrix->tuples[0] * other->tuples[1] + matrix->tuples[1] * other->tuples[5] + matrix->tuples[2] * other->tuples[9] + matrix->tuples[3] * other->tuples[13]; 
  temp.tuples[2] = matrix->tuples[0] * other->tuples[2] + matrix->tuples[1] * other->tuples[6] + matrix->tuples[2] * other->tuples[10] + matrix->tuples[3] * other->tuples[14]; 
  temp.tuples[3] = matrix->tuples[0] * other->tuples[3] + matrix->tuples[1] * other->tuples[7] + matrix->tuples[2] * other->tuples[11] + matrix->tuples[3] * other->tuples[15]; 
  temp.tuples[4] = matrix->tuples[4] * other->tuples[0] + matrix->tuples[5] * other->tuples[4] + matrix->tuples[6] * other->tuples[8] + matrix->tuples[7] * other->tuples[12]; 
  temp.tuples[5] = matrix->tuples[4] * other->tuples[1] + matrix->tuples[5] * other->tuples[5] + matrix->tuples[6] * other->tuples[9] + matrix->tuples[7] * other->tuples[13]; 
  temp.tuples[6] = matrix->tuples[4] * other->tuples[2] + matrix->tuples[5] * other->tuples[6] + matrix->tuples[6] * other->tuples[10] + matrix->tuples[7] * other->tuples[14]; 
  temp.tuples[7] = matrix->tuples[4] * other->tuples[3] + matrix->tuples[5] * other->tuples[7] + matrix->tuples[6] * other->tuples[11] + matrix->tuples[7] * other->tuples[15]; 
  temp.tuples[8] = matrix->tuples[8] * other->tuples[0] + matrix->tuples[9] * other->tuples[4] + matrix->tuples[10] * other->tuples[8] + matrix->tuples[11] * other->tuples[12]; 
  temp.tuples[9] = matrix->tuples[8] * other->tuples[1] + matrix->tuples[9] * other->tuples[5] + matrix->tuples[10] * other->tuples[9] + matrix->tuples[11] * other->tuples[13]; 
  temp.tuples[10] = matrix->tuples[8] * other->tuples[2] + matrix->tuples[9] * other->tuples[6] + matrix->tuples[10] * other->tuples[10] + matrix->tuples[11] * other->tuples[14]; 
  temp.tuples[11] = matrix->tuples[8] * other->tuples[3] + matrix->tuples[9] * other->tuples[7] + matrix->tuples[10] * other->tuples[11] + matrix->tuples[11] * other->tuples[15]; 
  temp.tuples[12] = matrix->tuples[12] * other->tuples[0] + matrix->tuples[13] * other->tuples[4] + matrix->tuples[14] * other->tuples[8] + matrix->tuples[15] * other->tuples[12]; 
  temp.tuples[13] = matrix->tuples[12] * other->tuples[1] + matrix->tuples[13] * other->tuples[5] + matrix->tuples[14] * other->tuples[9] + matrix->tuples[15] * other->tuples[13]; 
  temp.tuples[14] = matrix->tuples[12] * other->tuples[2] + matrix->tuples[13] * other->tuples[6] + matrix->tuples[14] * other->tuples[10] + matrix->tuples[15] * other->tuples[14]; 
  temp.tuples[15] = matrix->tuples[12] * other->tuples[3] + matrix->tuples[13] * other->tuples[7] + matrix->tuples[14] * other->tuples[11] + matrix->tuples[15] * other->tuples[15]; 
  matrix4_copy(target, &temp);
}

void matrix4_mul_vector(vector4* target, const matrix4* matrix, const vector4* vector)
{
  vector4 temp;
  temp.tuples[0] = matrix->tuples[0] * vector->tuples[0] + matrix->tuples[4] * vector->tuples[1] + matrix->tuples[8] * vector->tuples[2] + matrix->tuples[12] * vector->tuples[3]; 
  temp.tuples[1] = matrix->tuples[1] * vector->tuples[0] + matrix->tuples[5] * vector->tuples[1] + matrix->tuples[9] * vector->tuples[2] + matrix->tuples[13] * vector->tuples[3];
  temp.tuples[2] = matrix->tuples[2] * vector->tuples[0] + matrix->tuples[6] * vector->tuples[1] + matrix->tuples[10] * vector->tuples[2] + matrix->tuples[14] * vector->tuples[3]; 
  temp.tuples[3] = matrix->tuples[3] * vector->tuples[0] + matrix->tuples[7] * vector->tuples[1] + matrix->tuples[11] * vector->tuples[2] + matrix->tuples[15] * vector->tuples[3];
  vector4_copy(target, &temp);
}

void matrix4_mul_scalar(matrix4* target, const matrix4* matrix, const float scalar)
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
  target->tuples[9] = matrix->tuples[9] * scalar;
  target->tuples[10] = matrix->tuples[10] * scalar;
  target->tuples[11] = matrix->tuples[11] * scalar;
  target->tuples[12] = matrix->tuples[12] * scalar;
  target->tuples[13] = matrix->tuples[13] * scalar;
  target->tuples[14] = matrix->tuples[14] * scalar;
  target->tuples[15] = matrix->tuples[15] * scalar;
}

void matrix4_transpose(matrix4* target, const matrix4* matrix)
{
  matrix4 temp;
  matrix4_copy(&temp, matrix);
  temp.tuples[1] = matrix->tuples[4];
  temp.tuples[2] = matrix->tuples[8];
  temp.tuples[3] = matrix->tuples[12];
  temp.tuples[4] = matrix->tuples[1];
  temp.tuples[6] = matrix->tuples[9];
  temp.tuples[7] = matrix->tuples[13];
  temp.tuples[8] = matrix->tuples[2];
  temp.tuples[9] = matrix->tuples[6];
  temp.tuples[11] = matrix->tuples[14];
  temp.tuples[12] = matrix->tuples[3];
  temp.tuples[13] = matrix->tuples[7];
  temp.tuples[14] = matrix->tuples[11];
  matrix4_copy(target, &temp);
}

void matrix4_invert(matrix4* target, const matrix4* matrix)
{
  float temp[12];
  float dest[16];
  float det;

  temp[0]  = matrix->tuples[10] * matrix->tuples[15];
  temp[1]  = matrix->tuples[14] * matrix->tuples[11];
  temp[2]  = matrix->tuples[6] * matrix->tuples[15];
  temp[3]  = matrix->tuples[14] * matrix->tuples[7];
  temp[4]  = matrix->tuples[6] * matrix->tuples[11];
  temp[5]  = matrix->tuples[10] * matrix->tuples[7];
  temp[6]  = matrix->tuples[2] * matrix->tuples[15];
  temp[7]  = matrix->tuples[14] * matrix->tuples[3];
  temp[8]  = matrix->tuples[2] * matrix->tuples[11];
  temp[9]  = matrix->tuples[10] * matrix->tuples[3];
  temp[10] = matrix->tuples[2] * matrix->tuples[7];
  temp[11] = matrix->tuples[6] * matrix->tuples[3];
  dest[0]  = temp[0]* matrix->tuples[5] + temp[3]* matrix->tuples[9] + temp[4]* matrix->tuples[13];
  dest[0] -= temp[1]* matrix->tuples[5] + temp[2]* matrix->tuples[9] + temp[5]* matrix->tuples[13];
  dest[1]  = temp[1]* matrix->tuples[1] + temp[6]* matrix->tuples[9] + temp[9]* matrix->tuples[13];
  dest[1] -= temp[0]* matrix->tuples[1] + temp[7]* matrix->tuples[9] + temp[8]* matrix->tuples[13];
  dest[2]  = temp[2]* matrix->tuples[1] + temp[7]* matrix->tuples[5] + temp[10]* matrix->tuples[13];
  dest[2] -= temp[3]* matrix->tuples[1] + temp[6]* matrix->tuples[5] + temp[11]* matrix->tuples[13];
  dest[3]  = temp[5]* matrix->tuples[1] + temp[8]* matrix->tuples[5] + temp[11]* matrix->tuples[9];
  dest[3] -= temp[4]* matrix->tuples[1] + temp[9]* matrix->tuples[5] + temp[10]* matrix->tuples[9];
  dest[4]  = temp[1]* matrix->tuples[4] + temp[2]* matrix->tuples[8] + temp[5]* matrix->tuples[12];
  dest[4] -= temp[0]* matrix->tuples[4] + temp[3]* matrix->tuples[8] + temp[4]* matrix->tuples[12];
  dest[5]  = temp[0]* matrix->tuples[0] + temp[7]* matrix->tuples[8] + temp[8]* matrix->tuples[12];
  dest[5] -= temp[1]* matrix->tuples[0] + temp[6]* matrix->tuples[8] + temp[9]* matrix->tuples[12];
  dest[6]  = temp[3]* matrix->tuples[0] + temp[6]* matrix->tuples[4] + temp[11]* matrix->tuples[12];
  dest[6] -= temp[2]* matrix->tuples[0] + temp[7]* matrix->tuples[4] + temp[10]* matrix->tuples[12];
  dest[7]  = temp[4]* matrix->tuples[0] + temp[9]* matrix->tuples[4] + temp[10]* matrix->tuples[8];
  dest[7] -= temp[5]* matrix->tuples[0] + temp[8]* matrix->tuples[4] + temp[11]* matrix->tuples[8];
  temp[0]  = matrix->tuples[8]* matrix->tuples[13];
  temp[1]  = matrix->tuples[12]* matrix->tuples[9];
  temp[2]  = matrix->tuples[4]* matrix->tuples[13];
  temp[3]  = matrix->tuples[12]* matrix->tuples[5];
  temp[4]  = matrix->tuples[4]* matrix->tuples[9];
  temp[5]  = matrix->tuples[8]* matrix->tuples[5];
  temp[6]  = matrix->tuples[0]* matrix->tuples[13];
  temp[7]  = matrix->tuples[12]* matrix->tuples[1];
  temp[8]  = matrix->tuples[0]* matrix->tuples[9];
  temp[9]  = matrix->tuples[8]* matrix->tuples[1];
  temp[10] = matrix->tuples[0]* matrix->tuples[5];
  temp[11] = matrix->tuples[4]* matrix->tuples[1];
  dest[8]   = temp[0]* matrix->tuples[7] + temp[3]* matrix->tuples[11] + temp[4]* matrix->tuples[15];
  dest[8]  -= temp[1]* matrix->tuples[7] + temp[2]* matrix->tuples[11] + temp[5]* matrix->tuples[15];
  dest[9]   = temp[1]* matrix->tuples[3] + temp[6]* matrix->tuples[11] + temp[9]* matrix->tuples[15];
  dest[9]  -= temp[0]* matrix->tuples[3] + temp[7]* matrix->tuples[11] + temp[8]* matrix->tuples[15];
  dest[10]  = temp[2]* matrix->tuples[3] + temp[7]* matrix->tuples[7] + temp[10]* matrix->tuples[15];
  dest[10] -= temp[3]* matrix->tuples[3] + temp[6]* matrix->tuples[7] + temp[11]* matrix->tuples[15];
  dest[11]  = temp[5]* matrix->tuples[3] + temp[8]* matrix->tuples[7] + temp[11]* matrix->tuples[11];
  dest[11] -= temp[4]* matrix->tuples[3] + temp[9]* matrix->tuples[7] + temp[10]* matrix->tuples[11];
  dest[12]  = temp[2]* matrix->tuples[10] + temp[5]* matrix->tuples[14] + temp[1]* matrix->tuples[6];
  dest[12] -= temp[4]* matrix->tuples[14] + temp[0]* matrix->tuples[6] + temp[3]* matrix->tuples[10];
  dest[13]  = temp[8]* matrix->tuples[14] + temp[0]* matrix->tuples[2] + temp[7]* matrix->tuples[10];
  dest[13] -= temp[6]* matrix->tuples[10] + temp[9]* matrix->tuples[14] + temp[1]* matrix->tuples[2];
  dest[14]  = temp[6]* matrix->tuples[6] + temp[11]* matrix->tuples[14] + temp[3]* matrix->tuples[2];
  dest[14] -= temp[10]* matrix->tuples[14] + temp[2]* matrix->tuples[2] + temp[7]* matrix->tuples[6];
  dest[15]  = temp[10]* matrix->tuples[10] + temp[4]* matrix->tuples[2] + temp[9]* matrix->tuples[6];
  dest[15] -= temp[8]* matrix->tuples[6] + temp[11]* matrix->tuples[10] + temp[5]* matrix->tuples[2];
  det = 1.0f / ( matrix->tuples[0] * dest[0] + matrix->tuples[4] * dest[1] + matrix->tuples[8] * dest[2] + matrix->tuples[12] * dest[3]);
  target->tuples[0] = dest[0] * det; 
  target->tuples[1] = dest[4] * det; 
  target->tuples[2] = dest[8] * det; 
  target->tuples[3] = dest[12] * det;
  target->tuples[4] = dest[1] * det; 
  target->tuples[5] = dest[5] * det; 
  target->tuples[6] = dest[9] * det; 
  target->tuples[7] = dest[13] * det;
  target->tuples[8] = dest[2] * det; 
  target->tuples[9] = dest[6] * det; 
  target->tuples[10] = dest[10] * det; 
  target->tuples[11] = dest[14] * det;
  target->tuples[12] = dest[3] * det; 
  target->tuples[13] = dest[7] * det; 
  target->tuples[14] = dest[11] * det; 
  target->tuples[15] = dest[15] * det;
  matrix4_transpose(target, target);
}

float matrix4_determinant(matrix4* matrix)
{
  return 
    matrix->tuples[0] * (matrix->tuples[5] * (matrix->tuples[10] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[11]) + matrix->tuples[9] * (-(matrix->tuples[6] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[7])) + matrix->tuples[13] * (matrix->tuples[6] * matrix->tuples[11] - matrix->tuples[10] * matrix->tuples[7])) -
    matrix->tuples[4] * (matrix->tuples[1] * (matrix->tuples[10] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[11]) + matrix->tuples[9] * (-(matrix->tuples[2] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[3])) + matrix->tuples[13] * (matrix->tuples[2] * matrix->tuples[11] - matrix->tuples[10] * matrix->tuples[3])) +
    matrix->tuples[8] * (matrix->tuples[1] * (matrix->tuples[6] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[7]) + matrix->tuples[5] * (-(matrix->tuples[2] * matrix->tuples[15] - matrix->tuples[14] * matrix->tuples[3])) + matrix->tuples[13] * (matrix->tuples[2] * matrix->tuples[7] - matrix->tuples[6] * matrix->tuples[3])) -
    matrix->tuples[12] * (matrix->tuples[1] * (matrix->tuples[6] * matrix->tuples[11] - matrix->tuples[10] * matrix->tuples[7]) + matrix->tuples[5] * (-(matrix->tuples[2] * matrix->tuples[11] - matrix->tuples[10] * matrix->tuples[3])) + matrix->tuples[9] * (matrix->tuples[2] * matrix->tuples[7] - matrix->tuples[6] * matrix->tuples[3]));
}

void matrix4_translate(matrix4* target, const matrix4* matrix, const vector3* translation)
{
  matrix4 mat;
  matrix4_make_translation(&mat, translation);
  matrix4_mul(target, matrix, &mat);
}

void matrix4_translate_f(matrix4* target, const matrix4* matrix, const float translation_x, const float translation_y, const float translation_z)
{
  matrix4 mat;
  matrix4_make_translation_f(&mat, translation_x, translation_y, translation_z);
  matrix4_mul(target, matrix, &mat);
}

void matrix4_make_translation(matrix4* matrix, const vector3* translation)
{
  matrix4_identity(matrix);
  matrix->tuples[3] = translation->tuples[0];
  matrix->tuples[7] = translation->tuples[1];
  matrix->tuples[11] = translation->tuples[2];
}

void matrix4_make_translation_f(matrix4* matrix, const float translation_x, const float translation_y, const float translation_z)
{
  matrix4_identity(matrix);
  matrix->tuples[3] = translation_x;
  matrix->tuples[7] = translation_y;
  matrix->tuples[11] = translation_z;
}

void matrix4_scale(matrix4* target, const matrix4* matrix, const vector3* scale)
{
  matrix4 mat;
  matrix4_make_scale(&mat, scale);
  matrix4_mul(target, matrix, &mat);
}

void matrix4_scale_f(matrix4* target, const matrix4* matrix, const float scale_x, const float scale_y, const float scale_z)
{
  matrix4 mat;
  matrix4_make_scale_f(&mat, scale_x, scale_y, scale_z);
  matrix4_mul(target, matrix, &mat);
}

void matrix4_make_scale(matrix4* matrix, const vector3* scale)
{
  matrix4_identity(matrix);
  matrix->tuples[0] = scale->tuples[0];
  matrix->tuples[5] = scale->tuples[1];
  matrix->tuples[10] = scale->tuples[2];
}

void matrix4_make_scale_f(matrix4* matrix, const float scale_x, const float scale_y, const float scale_z)
{
  matrix4_identity(matrix);
  matrix->tuples[0] = scale_x;
  matrix->tuples[5] = scale_y;
  matrix->tuples[10] = scale_z;
}

void matrix4_make_perspective(matrix4* matrix, const float field_of_view, const float aspect_ratio, const float near_plane, const float far_plane)
{
  float range = near_plane * tanf(math_degree_to_radian(field_of_view * 0.5f));
  float left = -range * aspect_ratio;
  float right = range * aspect_ratio;
  float bottom = -range;
  float top = range;

  matrix4_identity(matrix);

  matrix->tuples[0] =  (2 * near_plane) / (right - left);
  matrix->tuples[2] = (right + left) / (right - left);
  matrix->tuples[5] = (2 * near_plane) / (top - bottom);
  matrix->tuples[6] = (top + bottom) / (top - bottom);
  matrix->tuples[10] = (far_plane + near_plane) / (near_plane - far_plane);
  matrix->tuples[11] = (2 * far_plane * near_plane) / (near_plane - far_plane);
  matrix->tuples[14] = -1.0f;
  matrix->tuples[15] = 0.0f;
}

void matrix4_make_ortho(matrix4* matrix, const float left_plane, const float right_plane, const float bottom_plane, const float top_plane, const float near_plane, const float far_plane)
{
  matrix4_identity(matrix);
  matrix->tuples[0] = 2.0f / (right_plane - left_plane);
  matrix->tuples[3] = -(right_plane + left_plane) / (right_plane - left_plane);
  matrix->tuples[5] = 2.0f / (top_plane - bottom_plane);
  matrix->tuples[7] = -(top_plane + bottom_plane) / (top_plane - bottom_plane);
  matrix->tuples[10] = 2.0f / (near_plane - far_plane);
  matrix->tuples[11] = -(far_plane + near_plane) / (far_plane - near_plane);
}

void matrix4_view(matrix4* matrix, const vector3* viewer, const vector3* target, const vector3* up)
{
  vector3 right;
  vector3 normal_up;
  vector3 forward;
  vector3 neg_pos;

  matrix4_identity(matrix);
  vector3_sub(&forward, target, viewer);
  vector3_normalize(&forward, &forward);
  vector3_cross(&right, &forward, up);
  vector3_normalize(&right, &right);
  vector3_cross(&normal_up, &right, &forward);

  matrix->tuples[0] = right.tuples[0];
  matrix->tuples[1] = right.tuples[1];
  matrix->tuples[2] = right.tuples[2];
  matrix->tuples[4] = normal_up.tuples[0];
  matrix->tuples[5] = normal_up.tuples[1];
  matrix->tuples[6] = normal_up.tuples[2];
  matrix->tuples[8] = -forward.tuples[0];
  matrix->tuples[9] = -forward.tuples[1];
  matrix->tuples[10] = -forward.tuples[2];

  vector3_invert(&neg_pos, viewer);
  matrix4_translate(matrix, matrix, &neg_pos);
}

void matrix4_view_f(matrix4* matrix, const float viewer_x, const float viewer_y, const float viewer_z, const float target_x, const float target_y, const float target_z, const float up_x, const float up_y, const float up_z)
{
  vector3 viewer;
  vector3 target;
  vector3 up;

  vector3_from_values(&viewer, viewer_x, viewer_y, viewer_z);
  vector3_from_values(&target, target_x, target_y, target_z);
  vector3_from_values(&up, up_x, up_y, up_z);
  matrix4_view(matrix, &viewer, &target, &up);
}

void matrix4_from_matrix3(matrix4* target, const matrix3* matrix)
{
  matrix4_identity(target);
  target->tuples[0] = matrix->tuples[0];
  target->tuples[1] = matrix->tuples[1];
  target->tuples[2] = matrix->tuples[2];
  target->tuples[4] = matrix->tuples[3];
  target->tuples[5] = matrix->tuples[4];
  target->tuples[6] = matrix->tuples[5];
  target->tuples[8] = matrix->tuples[6];
  target->tuples[9] = matrix->tuples[7];
  target->tuples[10] = matrix->tuples[8];
}

void matrix4_to_matrix3(matrix3* target, const matrix4* matrix)
{
  target->tuples[0] = matrix->tuples[0];
  target->tuples[1] = matrix->tuples[1];
  target->tuples[2] = matrix->tuples[2];
  target->tuples[3] = matrix->tuples[4];
  target->tuples[4] = matrix->tuples[5];
  target->tuples[5] = matrix->tuples[6];
  target->tuples[6] = matrix->tuples[8];
  target->tuples[7] = matrix->tuples[9];
  target->tuples[8] = matrix->tuples[10];
}

int matrix4_equal(const matrix4* matrix, const matrix4* other)
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
    math_fequal(matrix->tuples[8], other->tuples[8], math_epsilon) &&
    math_fequal(matrix->tuples[9], other->tuples[9], math_epsilon) &&
    math_fequal(matrix->tuples[10], other->tuples[10], math_epsilon) &&
    math_fequal(matrix->tuples[11], other->tuples[11], math_epsilon) &&
    math_fequal(matrix->tuples[12], other->tuples[12], math_epsilon) &&
    math_fequal(matrix->tuples[13], other->tuples[13], math_epsilon) &&
    math_fequal(matrix->tuples[14], other->tuples[14], math_epsilon) &&
    math_fequal(matrix->tuples[15], other->tuples[15], math_epsilon);
}

void matrix4_copy(matrix4* target, const matrix4* matrix)
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
  target->tuples[9] = matrix->tuples[9];
  target->tuples[10] = matrix->tuples[10];
  target->tuples[11] = matrix->tuples[11];
  target->tuples[12] = matrix->tuples[12];
  target->tuples[13] = matrix->tuples[13];
  target->tuples[14] = matrix->tuples[14];
  target->tuples[15] = matrix->tuples[15];
}
