#include <stdio.h>
#include <string.h>
#include "io.h"
#include "jpegio.h"
#include "pngio.h"

/** 
 * image loader callbacks 
 */
typedef struct 
{
  int       (*validate)(const char*);         /* format validation function */
  image*    (*load_from_file)(const char*);   /* format load function */
} image_loader_callbacks;

/**
 * a Lookup table for image loader callbacks 
 */
static const image_loader_callbacks callback_lookup[] = 
{
  {png_validate, png_load_from_file},     /* png callbacks */
  {jpeg_validate, jpeg_load_from_file}    /* jpeg callbacks */
};

/** 
 * detects type of image file 
 */
image_loader io_detect_loader_type(const char* path)
{
  int loop;
  image_loader type = il_unknown;

  for (loop = 0 ; loop < il_unknown; loop++) 
  {
    if (callback_lookup[loop].validate(path)) 
    {
      type = (image_loader)loop;
      break; 
    }
  }
  return type;
}

image* io_load_image(const char* path)
{
  image_loader type = io_detect_loader_type(path);
  return (type == il_unknown) ? (0) : (callback_lookup[type].load_from_file(path));
}

image* io_load_image_with_type(const char* path, image_loader type) 
{
  return (type == il_unknown) ? (0) : (callback_lookup[type].load_from_file(path));
}
