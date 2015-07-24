#include "util.h"

int math_fequal(const float float1, const float float2, const float epsilon) 
{
  return (float1 + epsilon >= float2) && (float1 - epsilon <= float2);
}

float math_radian_to_degree(const float radian) 
{
  return radian * math_grad_pi2;
}

float math_degree_to_radian(const float degree) 
{
  return degree * math_grad_pi;
}
