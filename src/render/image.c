#include "image.h"
#include <stdlib.h> /* malloc */
#include <memory.h> /* memset */

/** 
 * a lookup table for bytes per pixel for each pixel color format 
 */
static const int size_lookup[] = {1, 1, 2, 3, 4, 3, 4, 4};

image* image_alloc(int width, int height, color_format format)
{
  image* new_image = (image*)malloc(sizeof(image));

  memset(new_image, 0, sizeof(image));
  new_image->format = format;
  new_image->width = width;
  new_image->height = height;
  new_image->buffer = (unsigned char*)malloc(width * height * size_lookup[format]);
  return new_image;
}

void image_free(image* image_)
{
  if(image_->buffer) free(image_->buffer);
  free(image_);
}

void image_update(image* image_, int x, int y, int width, int height, unsigned char* data)
{
  int   loop;  
  int   src_offset = 0;
  int   dst_offset;
  int   line_size;

  if (image_->width < width + x) width = image_->width - x;
  if (image_->height < height + y) height = image_->height - y;
  if (x != 0 || y != 0 || height != image_->height || width != image_->width)
  {
    dst_offset = y * image_->width + x;
    line_size = width * size_lookup[image_->format];
    for (loop = 0; loop < height; loop++) 
    {
      memcpy(image_->buffer + dst_offset, data + src_offset, line_size);
      dst_offset += image_->width;
      src_offset += width;
    }
  }
  else 
  {
    memcpy(image_->buffer, data, height * width * size_lookup[image_->format]);
  }
}

char image_get_pixel(image* image_, int x, int y)
{
  return image_->buffer[y * image_->width + x];
}
