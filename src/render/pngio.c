#include "pngio.h"
#include <stdlib.h> /* malloc */
#include "png/png.h"

int png_validate(const char* path)
{
  FILE*   file;
  char    buffer[8];

  if ((file = fopen(path, "rb")) == 0) return 0;
  if (fread(buffer, 1, 8, file) != 8) return 0;

  /* signature check */
  return(!png_sig_cmp((png_bytep)buffer, (png_size_t)0, 8));
}


image* png_load_from_file(const char* path)
{
  int               bit_depth; 
  int               png_format;
  int               interlace_type;
  unsigned int      sig_read = 0;
  unsigned int      row_bytes;
  unsigned int      loop;
  FILE*             file;
  png_structp       png;
  png_infop         info;
  png_uint_32       width, height;
  png_bytepp        row_pointers;
  color_format      format;
  image*            new_image;

  if ((file = fopen(path, "rb")) == 0) return 0;

  if ((png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0)) == 0)
  {
    fclose(file);
    return 0;
  }
  if ((info = png_create_info_struct(png)) == 0) 
  {
    fclose(file);
    png_destroy_read_struct(&png, 0, 0);
    return 0;
  }
  if (setjmp(png_jmpbuf(png))) 
  {
    png_destroy_read_struct(&png, &info, 0);
    fclose(file);
    return 0;
  }

  png_init_io(png, file);
  png_set_sig_bytes(png, sig_read);
  png_read_info(png, info);
  png_get_IHDR(png, info, &width, &height, &bit_depth, &png_format, &interlace_type, 0, 0);

  /* Set transformation options */
  png_set_packing(png);
  if (png_format == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(png);
  if (png_format == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
  if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
  if (bit_depth == 16) png_set_strip_16(png);

  png_read_update_info(png, info);
  row_bytes = png_get_rowbytes(png, info);
  bit_depth = png_get_channels(png, info) * png_get_bit_depth(png, info);

  if (bit_depth == 8) format = cf_gray;
  else if (bit_depth == 16) format = cf_gray_alpha;
  else if (bit_depth == 24) format = cf_rgb_24;
  else if (bit_depth == 32) format = cf_rgba_32;
  else 
  {
    png_destroy_read_struct(&png, &info, 0);
    fclose(file);
    return 0;
  }

  new_image = image_alloc(width, height, format);

  row_pointers = (png_bytepp)malloc(height * sizeof(png_bytep));
  for (loop = 0; loop < height; ++loop) row_pointers[loop] = new_image->buffer + (loop * row_bytes);
  png_read_image(png, row_pointers);

  free(row_pointers);
  png_destroy_read_struct(&png, &info, 0);
  fclose(file);
  return new_image;
}


void png_save_to_file(image* raw, const char* path)
{

  int               loop;
  int               color_format;
  int               bpp;
  FILE*             file;
  png_structp       png;
  png_infop         info;
  png_bytepp        row_pointers;

  if ((file = fopen(path, "wb")) == 0) return;

  if ((png = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0)) == 0)
  {
    fclose(file);
    return;
  }
  if ((info = png_create_info_struct(png)) == 0) 
  {
    fclose(file);
    png_destroy_write_struct(&png, 0);
    return;
  }
  if (setjmp(png_jmpbuf(png))) 
  {
    png_destroy_write_struct(&png, &info);
    fclose(file);
    return;
  }

  png_init_io(png, file);

  if (raw->format == cf_gray) 
  {
    color_format = PNG_COLOR_TYPE_GRAY;
    bpp = 1;
  }
  else if (raw->format == cf_gray_alpha) 
  {
    color_format = PNG_COLOR_TYPE_GRAY_ALPHA;
    bpp = 2;
  }
  else if (raw->format == cf_rgb_24) 
  {
    color_format = PNG_COLOR_TYPE_RGB;
    bpp = 3;
  }
  else if (raw->format == cf_rgba_32) 
  {
    color_format = PNG_COLOR_TYPE_RGBA;
    bpp = 4;
  }
  else 
  {
    png_destroy_write_struct(&png, &info);
    fclose(file);
    return;
  }

  png_set_IHDR(png, info, raw->width, raw->height, 8, color_format, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info(png, info);

  row_pointers = (png_bytepp)malloc(raw->height * sizeof(png_bytep));
  for (loop = 0; loop < raw->height; ++loop) row_pointers[raw->height - 1 - loop] = raw->buffer + (loop * raw->width * bpp);
  png_write_image(png, row_pointers);

  png_write_end(png, 0);

  free(row_pointers);
  png_destroy_write_struct(&png, &info);
  fclose(file);
}
