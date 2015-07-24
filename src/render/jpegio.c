#include "jpegio.h"
#include <stdio.h>  /* file i/o */
#include <memory.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include "jpeg/jpeglib.h"

int jpeg_validate(const char* path)
{
  FILE*   file;
  char    buffer[2];

  if ((file = fopen(path, "rb")) == 0) return 0;
  if (fread(buffer, 1, 2, file) != 2) return 0;

  /* check jpeg soi marker */
  return (buffer[0] == 'ÿ' && buffer[1] == 'Ø');
}

image* jpeg_load_from_file(const char* path)
{
  int                               pixels_read;
  unsigned char**                   row_pointers;
  unsigned char*                    rows; 
  FILE*                             file;
  struct jpeg_decompress_struct     info;
  struct jpeg_error_mgr             error_manager;
  color_format                      format;
  image*                            new_image;

  if ((file = fopen(path, "rb")) == NULL) return 0;

  info.err = jpeg_std_error(&error_manager);
  jpeg_create_decompress(&info);
  jpeg_stdio_src(&info, file);
  jpeg_read_header(&info, TRUE);
  jpeg_start_decompress(&info);

  if (info.num_components == 1) format = cf_gray;
  else if (info.num_components == 3) format = cf_rgb_24;
  else 
  {
    jpeg_finish_decompress(&info);
    jpeg_destroy_decompress(&info);
    fclose(file);
    return 0; 
  }

  new_image = image_alloc(info.output_width, info.output_height, format);

  rows = new_image->buffer;
  row_pointers = &rows;
  pixels_read = 0;

  while(info.output_scanline < info.output_height)
  {
    pixels_read = jpeg_read_scanlines(&info, row_pointers, 1);
    *row_pointers += pixels_read * info.num_components * info.output_width;
  }

  jpeg_finish_decompress(&info);
  jpeg_destroy_decompress(&info);
  fclose(file);
  return new_image;
}

void jpeg_save_to_file(image* raw, const char* path, int quality)
{
  int                               loop;
  unsigned char*                    row_pointer[1];
  FILE*                             file;
  struct jpeg_compress_struct       info;
  struct jpeg_error_mgr             error_manager;
  image*                            im;

  if ((file = fopen(path, "wb")) == NULL) return;

  info.err = jpeg_std_error(&error_manager);
  jpeg_create_compress(&info);
  jpeg_stdio_dest(&info, file);

  im = raw;

  if (raw->format == cf_gray) 
  {
    info.input_components  = 1;
    info.in_color_space = JCS_GRAYSCALE;
  }
  else if (raw->format == cf_rgb_24) 
  {
    info.input_components  = 3;
    info.in_color_space = JCS_RGB;
  }
  else if (raw->format == cf_rgba_32) 
  {
    /* drop the alpha channel */
    im = image_alloc(raw->width, raw->height, cf_rgb_24);
    for (loop = 0; loop < raw->width * raw->height; loop++)
    {
      im->buffer[loop * 3] = raw->buffer[loop * 4];
      im->buffer[loop * 3 + 1]  = raw->buffer[loop * 4 + 1];
      im->buffer[loop * 3 + 2]  = raw->buffer[loop * 4 + 2];
    }
    info.input_components  = 3;
    info.in_color_space = JCS_RGB; 
  }
  else 
  {
    jpeg_destroy_compress(&info);
    fclose(file);
    return; 
  }
  
  info.image_width = im->width;
  info.image_height = im->height;

  jpeg_set_defaults(&info);
  info.num_components = info.input_components;
  info.dct_method = JDCT_FLOAT;
  jpeg_set_quality(&info, quality, TRUE);
  jpeg_start_compress(&info, FALSE);

  while(info.next_scanline < info.image_height)
  {
    row_pointer[0] = &im->buffer[(info.image_height - info.next_scanline - 1) * info.image_width * info.input_components];
    jpeg_write_scanlines(&info, row_pointer, 1);
  }

  if (im != raw) free(im);
  jpeg_finish_compress(&info);
  jpeg_destroy_compress(&info);
  fclose(file);
}
