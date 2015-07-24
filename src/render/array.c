#include "array.h"
#include <stdlib.h> /* malloc */
#include <memory.h> /* memset */
#include <string.h> /* memmove */

array* array_alloc()
{
  array* new_array = (array*)malloc(sizeof(array));
  memset(new_array, 0, sizeof(array));
  return new_array;
}

void array_free(array* array_)
{
  if (array_->elements)
  {
    free(array_->elements);
  }
  free(array_);
}

generic* array_push(array* array_, void* data, const int tag) {
  const int index = array_->usage;

  if (index >= array_->capacity)
  {
    array_->capacity += array_->capacity ? array_->capacity : 8;
    array_->elements = (generic*)realloc(array_->elements, array_->capacity * sizeof(generic));                                                                          
  }
  array_->elements[index].pointer = data;
  array_->elements[index].tag = tag;
  ++(array_->usage);
  return &array_->elements[index];
}

generic* array_pop(array* array_)
{ 
  if (array_->usage > 0)
  {
    return &array_->elements[(array_->usage)--];
  }
  return NULL;
}

void array_insert(array* array_, const int index, void* data, const int tag) 
{
  if (index >= array_->usage)
  {
    array_push(array_, data, tag);
    return;
  }
  if (array_->usage >= array_->capacity)
  {
    array_->capacity += array_->capacity?array_->capacity:8;
    array_->elements = (generic*)realloc(array_->elements, array_->capacity * sizeof(generic));
  }
  memmove(array_->elements + index + 1, array_->elements + index, (array_->usage - index) * sizeof(generic));
  array_->elements[index].pointer = data;
  array_->elements[index].tag = tag;
  ++(array_->usage);
}

extern void array_remove(array* array_, const int index) 
{
  if (index >= array_->usage)
  {
    array_pop(array_);
    return;
  }
  memmove(array_->elements + index, array_->elements + index + 1, (array_->usage - index) * sizeof(generic));                  
  --(array_->usage);
}

extern void array_reset(array* array_)
{
  if (array_->elements) 
  {
    free(array_->elements);
    array_->elements = 0;
    array_->usage = 0;
    array_->capacity = 0;
  }
}
