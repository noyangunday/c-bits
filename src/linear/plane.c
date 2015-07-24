#include "plane.h"
#include "util.h"

void plane_reset(plane* plane_)
{
  plane_->normal.tuples[0] = 0.0f;
  plane_->normal.tuples[1] = 0.0f;
  plane_->normal.tuples[2] = 0.0f;
  plane_->distance = 0.0f;
}

void plane_normalize(plane* target, const plane* plane_)
{
  float length;
  
  length = vector3_length(&plane_->normal);
  vector3_div_scalar(&target->normal, &plane_->normal, length);
  target->distance = plane_->distance / length;
}

void plane_from_values(plane* plane_, const float a, const float b, const float c, const float d)
{
  plane_->normal.tuples[0] = a;
  plane_->normal.tuples[1] = b;
  plane_->normal.tuples[2] = c;
  plane_->distance = d;
}

void plane_from_nd(plane* plane_, const vector3* normal, const float distance)
{
  plane_->normal.tuples[0] = normal->tuples[0];
  plane_->normal.tuples[1] = normal->tuples[1];
  plane_->normal.tuples[2] = normal->tuples[2];
  plane_->distance = distance;
}

int plane_equal(const plane* plane_, const plane* other)
{
  return 
    vector3_equal(&plane_->normal, &other->normal) &&
    math_fequal(plane_->distance, other->distance, math_epsilon);
}

void plane_copy(plane* target, const plane* plane_)
{
  target->normal.tuples[0] = plane_->normal.tuples[0];
  target->normal.tuples[1] = plane_->normal.tuples[1];
  target->normal.tuples[2] = plane_->normal.tuples[2];
  target->distance = plane_->distance;
}
