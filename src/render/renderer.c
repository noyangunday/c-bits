#include "renderer.h"
#include <stdlib.h>             /* malloc */
#include <memory.h>             /* memset */
#include "io.h"                 /* image loader */

/**
 * next power of two
 */
unsigned int math_npot(const unsigned int value)
{
  unsigned int power_of_two = value;
  power_of_two = power_of_two - 1;
  power_of_two = power_of_two | (power_of_two >> 1);
  power_of_two = power_of_two | (power_of_two >> 2);
  power_of_two = power_of_two | (power_of_two >> 4);
  power_of_two = power_of_two | (power_of_two >> 8);
  power_of_two = power_of_two | (power_of_two >> 16);
  return power_of_two + 1;
}

/** 
 * frees an array of images 
 */
#define renderer_free_images(images, size) do { \
  int loop; \
  for (loop = 0; loop < size; loop++) \
  { \
  image_free(images[loop]); \
  } \
} while(0)


/** 
 * internal color format lookup 
 */
static const GLint if_lookup[] =
{
  GL_ALPHA8,
  GL_LUMINANCE8,          
  GL_LUMINANCE8_ALPHA8,
  GL_RGB8,     
  GL_RGBA8,     
  GL_RGB8,       
  GL_RGBA8,
  GL_DEPTH_COMPONENT
};

/** 
 * color format lookup 
 */
static const GLenum color_lookup[] =
{
  GL_ALPHA,
  GL_LUMINANCE,          
  GL_LUMINANCE_ALPHA,
  GL_RGB,     
  GL_RGBA,     
  GL_BGR,       
  GL_BGRA,
  GL_DEPTH_COMPONENT
};

/** 
 * data type lookup 
 */
static const GLenum data_type_lookup[] = 
{
  GL_BYTE,
  GL_UNSIGNED_BYTE, 
  GL_SHORT,
  GL_UNSIGNED_SHORT,
  GL_INT,
  GL_UNSIGNED_INT,
  GL_FLOAT,
  GL_DOUBLE
};

/** 
 * data type size lookup 
 */
static const GLenum data_size_lookup[] = {1, 1, 2, 2, 4, 4, 4, 8};

/** 
 * shader type lookup 
 */
static const GLenum shader_type_lookup[] = 
{
  GL_VERTEX_SHADER, 
  GL_FRAGMENT_SHADER
};

/** 
 * buffer type lookup 
 */
static const GLenum buffer_type_lookup[] = 
{
  GL_ARRAY_BUFFER, 
  GL_ELEMENT_ARRAY_BUFFER
};

/** 
 * texture type lookup 
 */
static const GLenum texture_type_lookup[] =
{
  GL_TEXTURE_2D,
  GL_TEXTURE_CUBE_MAP
};

/** 
 * texture target lookup 
 */
static const GLenum texture_target_lookup[] =
{
  GL_TEXTURE_2D,
  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

/** 
 * buffer usage lookup 
 */
static const GLenum buffer_usage_lookup[] =
{
  GL_STREAM_DRAW,
  GL_STREAM_READ,
  GL_STREAM_COPY,
  GL_STATIC_DRAW,
  GL_STATIC_READ,
  GL_STATIC_COPY,
  GL_DYNAMIC_DRAW,
  GL_DYNAMIC_READ,
  GL_DYNAMIC_COPY
};

/** 
 * buffer map mode lookup 
 */
static const GLenum map_mode_lookup[] = 
{
  0,
  GL_READ_ONLY, 
  GL_WRITE_ONLY,
  GL_READ_WRITE
};

/** 
 * draw mode lookup 
 */
static const GLenum draw_mode_lookup[] =
{
  GL_POINTS,
  GL_LINES,
  GL_LINE_LOOP,
  GL_LINE_STRIP,
  GL_TRIANGLES,
  GL_TRIANGLE_STRIP,
  GL_QUADS,
  GL_QUAD_STRIP,
  GL_POLYGON
};

/** 
 * blend mode lookup 
 */
static const GLenum blend_mode_lookup[] =
{
  GL_ZERO,           
  GL_ONE, 
  GL_SRC_COLOR,                  
  GL_ONE_MINUS_SRC_COLOR,     
  GL_DST_COLOR,           
  GL_ONE_MINUS_DST_COLOR, 
  GL_SRC_ALPHA,             
  GL_ONE_MINUS_SRC_ALPHA,   
  GL_DST_ALPHA,             
  GL_ONE_MINUS_DST_ALPHA,  
  GL_SRC_ALPHA_SATURATE  
};

/** 
 * test function lookup 
 */
static const GLenum test_function_lookup[] =
{
  GL_NEVER,
  GL_ALWAYS,
  GL_EQUAL,             
  GL_NOTEQUAL,       
  GL_LESS,             
  GL_LEQUAL,
  GL_GREATER,
  GL_GEQUAL
};

/** 
 * stencil operation lookup 
 */
static const GLenum stencil_op_lookup[] =
{
  GL_KEEP,
  GL_ZERO,
  GL_REPLACE,
  GL_INCR,
  GL_INCR_WRAP,
  GL_DECR,
  GL_DECR_WRAP,
  GL_INVERT
};

/** 
 * face ordering lookup 
 */
static const GLenum vertex_order_lookup[] =
{
  GL_CCW,
  GL_CW
};

/** 
 * face culling mode lookup 
 */
static const GLenum cull_mode_lookup[] =
{
  GL_FRONT,
  GL_BACK,
};

/** 
 * face render type lookup 
 */
static const GLenum face_type_lookup[] =
{
  GL_FRONT,
  GL_BACK,
  GL_FRONT_AND_BACK,
};

/** 
 * polygon fill mode lookup 
 */
static const GLenum polygon_mode_lookup[] =
{
  GL_FILL,
  GL_LINE,
};

/** 
 * texture wrap mode lookup 
 */
static const GLint wrap_mode_lookup[] =
{
    GL_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_MIRRORED_REPEAT,
};

renderer* renderer_alloc()
{
  renderer* new_renderer;
  new_renderer = (renderer*)malloc(sizeof(renderer));
  memset(new_renderer, 0, sizeof(renderer));

  /* useable texture unit count */
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &new_renderer->tex_unit_count);
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &new_renderer->attachment_count);
  new_renderer->active_textures = (texture**)malloc(sizeof(texture*) * new_renderer->tex_unit_count);
  memset(new_renderer->active_textures, 0, sizeof(texture*) * new_renderer->tex_unit_count);

  new_renderer->mipmaps = 1;
  new_renderer->wrapping[0] = wm_clamp_to_edge;
  new_renderer->wrapping[1] = wm_clamp_to_edge;
  new_renderer->texture_filters[0] = fm_linear;
  new_renderer->texture_filters[1] = fm_linear;
  new_renderer->texture_filters[2] = fm_linear;
  new_renderer->blend_modes[0] = bm_one;
  new_renderer->blend_modes[1] = bm_zero;
  new_renderer->stencil_ops[0] = so_keep;
  new_renderer->stencil_ops[1] = so_keep;
  new_renderer->stencil_ops[2] = so_keep;
  new_renderer->depth_function = tf_less;
  new_renderer->polygon_face = vo_counter_clockwise;
  new_renderer->face_cull_mode = cm_back;
  new_renderer->fill_modes[0] = pm_fill;
  new_renderer->fill_modes[1] = pm_fill;
  new_renderer->fill_modes[2] = pm_fill;
  new_renderer->blend = 0;
  new_renderer->stencil = 0;
  new_renderer->depth_test = 0;
  new_renderer->face_cull = 0;
  return new_renderer;
}

texture* renderer_alloc_texture(renderer* renderer_, texture_type type, const int width, const int height, const color_format internal_format, const color_format format)
{
  texture*  new_texture;
  int       loop;
  int       l_end = (type == tt_2d)?(1):(6);
  GLint     s_filter = GL_NEAREST + renderer_->texture_filters[0] + ((renderer_->mipmaps)?(0x100 + (renderer_->texture_filters[2] * 2)):(0));
  GLint     t_filter = GL_NEAREST + renderer_->texture_filters[1];

  if (height <= 0 && width <= 0) return NULL;
  new_texture = (texture*)malloc(sizeof(texture));
  new_texture->type = type;
  new_texture->height = math_npot(height);
  new_texture->width = math_npot(width);
  new_texture->height_ratio = (float)height / (float)new_texture->height; 
  new_texture->width_ratio = (float)width / (float)new_texture->width; 
  new_texture->mipmaps = renderer_->mipmaps;
  glGenTextures(1, &new_texture->texture_object);
  renderer_bind_texture(renderer_, 0, new_texture);

  for (loop = 0; loop < l_end; loop++)
  {
    glTexImage2D((type == tt_2d)?(GL_TEXTURE_2D):(GL_TEXTURE_CUBE_MAP_POSITIVE_X + loop), 0, if_lookup[internal_format], new_texture->width, new_texture->height, 0, color_lookup[format], GL_UNSIGNED_BYTE, 0);
  }
  glTexParameteri(texture_type_lookup[type], GL_TEXTURE_WRAP_S, wrap_mode_lookup[renderer_->wrapping[0]]); 
  glTexParameteri(texture_type_lookup[type], GL_TEXTURE_WRAP_T, wrap_mode_lookup[renderer_->wrapping[1]]);
  glTexParameteri(texture_type_lookup[type], GL_TEXTURE_MIN_FILTER, s_filter); 
  glTexParameteri(texture_type_lookup[type], GL_TEXTURE_MAG_FILTER, t_filter);
  return new_texture;
}

buffer* renderer_alloc_buffer(renderer* renderer_, const buffer_type type, const int size, const buffer_usage usage)
{
  buffer*   new_buffer;

  if (size <= 0) return NULL;
  new_buffer = (buffer*)malloc(sizeof(buffer));
  memset(new_buffer, 0, sizeof(buffer));
  new_buffer->size = size;
  new_buffer->type = type;
  glGenBuffers(1, &new_buffer->buffer_object);
  glBindBuffer(buffer_type_lookup[type], new_buffer->buffer_object);
  renderer_->active_buffers[type] = new_buffer;
  glBufferData(buffer_type_lookup[type], size, NULL, buffer_usage_lookup[usage]);
  return new_buffer;
}

shader* renderer_alloc_shader(const shader_type type)
{
  shader* new_shader;

  new_shader = (shader*)malloc(sizeof(shader));
  memset(new_shader, 0, sizeof(shader));
  new_shader->type = type;
  new_shader->shader_object = glCreateShader(shader_type_lookup[type]);
  return new_shader;
}

program* renderer_alloc_program()
{
  program* new_program;

  new_program = (program*)malloc(sizeof(program));
  memset(new_program, 0, sizeof(program));
  new_program->linked = 0;
  new_program->program_object = glCreateProgram();
  return new_program;
}

vertex* renderer_alloc_vertex(const int struct_size)
{
  vertex* new_vertex;

  new_vertex = (vertex*)malloc(sizeof(vertex));
  new_vertex->attributes = array_alloc();
  new_vertex->size = struct_size;
  return new_vertex;
}

uniform_set* renderer_alloc_uniform_set()
{
  uniform_set* new_set;

  new_set = (uniform_set*)malloc(sizeof(uniform_set));
  new_set->uniforms = array_alloc();
  return new_set;
}

framebuffer* renderer_alloc_framebuffer(renderer* renderer_, const int width, const int height, const int color_attachment_count, const int has_depth_attachment)
{
  framebuffer*    new_framebuffer;
  framebuffer*    current_framebuffer = renderer_->active_framebuffer;
  int             mipmaps = renderer_->mipmaps;
  filter_mode     filters[] = {renderer_->texture_filters[0], renderer_->texture_filters[1], renderer_->texture_filters[2]};
  int             loop;

  new_framebuffer = (framebuffer*)malloc(sizeof(framebuffer));
  memset(new_framebuffer, 0, sizeof(framebuffer));
  new_framebuffer->color_attachment_count = color_attachment_count > renderer_->attachment_count ? renderer_->attachment_count : color_attachment_count;
  new_framebuffer->width = math_npot(width);
  new_framebuffer->height = math_npot(height);
  new_framebuffer->has_depth_attachment = has_depth_attachment;
  new_framebuffer->attachments = (texture**)malloc(sizeof(texture*) * (color_attachment_count + (has_depth_attachment != 0)));
  memset(new_framebuffer->attachments, 0, sizeof(texture*) * (color_attachment_count + (has_depth_attachment != 0)));

  glGenFramebuffers(1, &new_framebuffer->framebuffer_object);
  glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer->framebuffer_object);

  if (has_depth_attachment)
  {
    renderer_set_filters(renderer_, fm_nearest, fm_nearest, fm_nearest);
    renderer_disable_mipmaps(renderer_);
    new_framebuffer->attachments[color_attachment_count] = renderer_alloc_texture(renderer_, tt_2d, new_framebuffer->width, new_framebuffer->height, cf_depth, cf_depth);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, new_framebuffer->attachments[color_attachment_count]->texture_object, 0);
    renderer_set_filters(renderer_, filters[0], filters[1], filters[2]); 
    if (mipmaps) 
    {
      renderer_enable_mipmaps(renderer_);
    }
  }

  if (color_attachment_count) 
  {
    for (loop = 0; loop < color_attachment_count; loop++) 
    {
      new_framebuffer->attachments[loop] = renderer_alloc_texture(renderer_, tt_2d, new_framebuffer->width, new_framebuffer->height, cf_rgba_32, cf_rgba_32);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + loop, GL_TEXTURE_2D, new_framebuffer->attachments[loop]->texture_object, 0);
    }
  }
  else 
  {
    /* these are stored in fbo state */
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
  }

  new_framebuffer->complete = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
  if (current_framebuffer != 0)
  {
    glBindFramebuffer(GL_FRAMEBUFFER, current_framebuffer->framebuffer_object);
  }
  else
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  return new_framebuffer;
}

void renderer_bind_texture(renderer* renderer_, const int tex_unit, texture* texture_)
{
  if (texture_ && renderer_->active_textures[tex_unit] != texture_)
  {
    glActiveTexture(GL_TEXTURE0 + tex_unit);
    glBindTexture(texture_type_lookup[texture_->type], texture_->texture_object);
    renderer_->active_textures[tex_unit] = texture_;
  }
}

void renderer_bind_program(renderer* renderer_, program* program_)
{
  if (renderer_->active_program != program_) 
  {
    if (program_ && program_->linked)
    {
      glUseProgram(program_->program_object);
      renderer_->active_program = program_;
    }
    else 
    {
      glUseProgram(0);
      renderer_->active_program = 0;
    }
  }
}

extern void renderer_bind_buffer(renderer* renderer_, buffer* buffer_)
{
  buffer* act_buf = renderer_->active_buffers[buffer_->type];

  if (act_buf != buffer_)  
  {
    /* unmap currently bound buffer if mapped (note: not sure if this is necessary) */
    if (act_buf && act_buf->map.mode != mm_not_mapped)
    {
      renderer_unmap_buffer(act_buf);
    }
    glBindBuffer(buffer_type_lookup[buffer_->type], buffer_->buffer_object);
    renderer_->active_buffers[buffer_->type] = buffer_;
  }
}

void renderer_bind_framebuffer(renderer* renderer_, framebuffer* framebuffer_)
{
  if (renderer_->active_framebuffer != framebuffer_)
  {
    if (framebuffer_ && framebuffer_->complete) 
    {
      glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_->framebuffer_object);
      renderer_->active_framebuffer = framebuffer_;
    }
    else 
    {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      renderer_->active_framebuffer = 0;
    }
  }
}

extern void renderer_unbind_buffer(renderer* renderer_, const buffer_type slot)
{
  buffer* act_buf = renderer_->active_buffers[slot];
  if (act_buf && act_buf->map.mode != mm_not_mapped)
  {
    renderer_unmap_buffer(act_buf);
  }
  glBindBuffer(buffer_type_lookup[slot], 0);
  renderer_->active_buffers[slot] = 0;
}

void renderer_activate_vertex_buffer(renderer* renderer_, buffer* buffer_, const vertex* vertex_)
{
  int offset = 0;
  int loop; 
  attribute* attrib;

  if (buffer_->type == bt_vertex) 
  {
    renderer_bind_buffer(renderer_, buffer_);
    for (loop = 0; loop < vertex_->attributes->usage; loop++) 
    {
      attrib = (attribute*)vertex_->attributes->elements[loop].pointer;
      glEnableVertexAttribArray(loop);
      glVertexAttribPointer(loop, attrib->size, data_type_lookup[attrib->type], 0, vertex_->size, (const void*) offset);
      offset += data_size_lookup[attrib->type] * attrib->size;
    }
  }
}

void renderer_execute_index_buffer(renderer* renderer_, buffer* buffer_, const int start, const int count, const draw_mode mode)
{
  if (buffer_->type == bt_index) 
  {
    renderer_bind_buffer(renderer_, buffer_);
    glDrawElements(draw_mode_lookup[mode], count, GL_UNSIGNED_INT, (const void *)(start * sizeof(unsigned int)));
  }
}

void renderer_draw_vertex_array(renderer* renderer_, void* vertex_array, const vertex* vertex_, const int count, const draw_mode mode)
{
  int offset = 0;
  int loop;
  attribute* attrib;

  if (renderer_->active_buffers[bt_vertex]) 
  {
    renderer_unbind_buffer(renderer_, bt_vertex);
  }
  for (loop = 0; loop < vertex_->attributes->usage; loop++) 
  {
    attrib = (attribute*)vertex_->attributes->elements[loop].pointer;
    glEnableVertexAttribArray(loop);
    glVertexAttribPointer(loop, attrib->size, data_type_lookup[attrib->type], 0, vertex_->size, (const void*) (((char*)vertex_array) + offset));
    offset += data_size_lookup[attrib->type] * attrib->size;
  }
  glDrawArrays(draw_mode_lookup[mode], 0, count);
}

void renderer_bind_uniforms(const uniform_set* set)
{
  int loop;
  uniform* uform;
  uniform_type type;

  for (loop = 0; loop < set->uniforms->usage; loop++) 
  {
    uform = (uniform*)set->uniforms->elements[loop].pointer;
    type = uform->type;

    if (uform->location == -1)
    {
      continue;
    }
    else
    {
      switch(uform->type) 
      {
      case ut_sampler:
        glUniform1i(uform->location, (int)uform->data);
        break;
      case ut_float_4x4:
        glUniformMatrix4fv(uform->location, uform->element_count, 0, (float*)uform->data);
        break;
      case ut_float_1:
        glUniform1fv(uform->location, uform->element_count, (float*)uform->data);
        break;
      case ut_int_1:
        glUniform1iv(uform->location, uform->element_count, (int*)uform->data);
        break;
      case ut_int_2:
        glUniform2iv(uform->location, uform->element_count, (int*)uform->data);
        break;
      case ut_int_3:
        glUniform3iv(uform->location, uform->element_count, (int*)uform->data);
        break;
      case ut_int_4:
        glUniform4iv(uform->location, uform->element_count, (int*)uform->data);
        break;
      case ut_float_2:
        glUniform2fv(uform->location, uform->element_count, (float*)uform->data);
        break;
      case ut_float_3:
        glUniform3fv(uform->location, uform->element_count, (float*)uform->data);
        break;
      case ut_float_4:
        glUniform4fv(uform->location, uform->element_count, (float*)uform->data);
        break;
      case ut_float_2x2:
        glUniformMatrix2fv(uform->location, uform->element_count, 0, (float*)uform->data);
        break;
      case ut_float_3x3:
        glUniformMatrix3fv(uform->location, uform->element_count, 0, (float*)uform->data);
        break;
      }
    }
  }
}

void renderer_update_texture(renderer* renderer_, texture* texture_, const texture_target target, const int width, const int height, const color_format format, const void* data)
{
  renderer_bind_texture(renderer_, 0, texture_);
  texture_->width_ratio = (float)width / (float)texture_->width;
  texture_->height_ratio = (float)height / (float)texture_->height;
  glTexSubImage2D(texture_target_lookup[target], 0, 0, 0, width, height, color_lookup[format], GL_UNSIGNED_BYTE, data);
  if(texture_->mipmaps) glGenerateMipmap(texture_type_lookup[texture_->type]);
}

void renderer_update_buffer(renderer* renderer_, buffer* buffer_, const int size, const void * data)
{
  renderer_bind_buffer(renderer_, buffer_);
  glBufferSubData(buffer_type_lookup[buffer_->type], 0, size, data);
}

void renderer_map_buffer(renderer* renderer_, buffer* buffer_, const map_mode mode)
{
  renderer_bind_buffer(renderer_, buffer_);
  buffer_->map.mapped_memory = (void *)glMapBuffer(buffer_type_lookup[buffer_->type], map_mode_lookup[mode]);
  buffer_->map.mode = mode;
}

void renderer_unmap_buffer(buffer* buffer_)
{
  if (buffer_->map.mode != mm_not_mapped) 
  {
    glUnmapBuffer(buffer_type_lookup[buffer_->type]);
    buffer_->map.mode = mm_not_mapped;
  }
}

void renderer_compile_shader(shader* shader_, const char* source_code)
{
  glShaderSource(shader_->shader_object, 1, &source_code, 0);
  glCompileShader(shader_->shader_object);
  glGetShaderiv(shader_->shader_object, GL_COMPILE_STATUS, &shader_->compiled);
}

void renderer_attach_shader(program* program_, const shader* shader_)
{
  if (shader_->compiled)
  {
    glAttachShader(program_->program_object, shader_->shader_object);
  }
}

void renderer_link_program(program* program_, const vertex* vertex_)
{
  int loop;
  attribute* attrib;

  if (vertex_) 
  {
    for (loop = 0; loop < vertex_->attributes->usage; loop++) 
    {
      attrib = (attribute*)vertex_->attributes->elements[loop].pointer;
      glBindAttribLocation(program_->program_object, loop, attrib->name);
    }
  }
  glLinkProgram(program_->program_object);
  glGetProgramiv(program_->program_object, GL_LINK_STATUS, &program_->linked);
}

void renderer_fill_uniform_locations(program* program_, uniform_set* set)
{
  int loop;
  uniform* uform;

  for (loop = 0; loop < set->uniforms->usage; loop++)
  {
    uform = (uniform*)set->uniforms->elements[loop].pointer;
    uform->location = glGetUniformLocation(program_->program_object, uform->name);
  }
}

texture* renderer_make_texture_cube_from_image(renderer* renderer_, const image* image_[6], const color_format internal_format)
{
  texture* new_texture;

  new_texture = renderer_alloc_texture(renderer_, tt_cube, image_[0]->width, image_[0]->height, internal_format, image_[0]->format);
  renderer_update_texture(renderer_, new_texture, ta_cube_positive_x, image_[0]->width, image_[0]->height, image_[0]->format, image_[0]->buffer);
  renderer_update_texture(renderer_, new_texture, ta_cube_negative_x, image_[1]->width, image_[1]->height, image_[1]->format, image_[1]->buffer);
  renderer_update_texture(renderer_, new_texture, ta_cube_positive_y, image_[2]->width, image_[2]->height, image_[2]->format, image_[2]->buffer);
  renderer_update_texture(renderer_, new_texture, ta_cube_negative_y, image_[3]->width, image_[3]->height, image_[3]->format, image_[3]->buffer);
  renderer_update_texture(renderer_, new_texture, ta_cube_positive_z, image_[4]->width, image_[4]->height, image_[4]->format, image_[4]->buffer);
  renderer_update_texture(renderer_, new_texture, ta_cube_negative_z, image_[5]->width, image_[5]->height, image_[5]->format, image_[5]->buffer);
  return new_texture;
}

texture* renderer_make_texture_cube_from_file(renderer* renderer_, const char* file_name[6], const color_format internal_format)
{
  image* image_[6];
  texture* new_texture;

  image_[0] = io_load_image(file_name[0]); if (!image_[0]) { return 0; } 
  image_[1] = io_load_image(file_name[1]); if (!image_[1]) { image_free(image_[0]); return 0; }
  image_[2] = io_load_image(file_name[2]); if (!image_[2]) { renderer_free_images(image_, 2); return 0; }
  image_[3] = io_load_image(file_name[3]); if (!image_[3]) { renderer_free_images(image_, 3); return 0; }
  image_[4] = io_load_image(file_name[4]); if (!image_[4]) { renderer_free_images(image_, 4); return 0; }
  image_[5] = io_load_image(file_name[5]); if (!image_[5]) { renderer_free_images(image_, 5); return 0; }
  new_texture = renderer_make_texture_cube_from_image(renderer_, image_, internal_format);
  renderer_free_images(image_, 6);
  return new_texture;
}

texture* renderer_make_texture_2d_from_image(renderer* renderer_, const image* image_, const color_format internal_format)
{
  texture* new_texture;

  new_texture = renderer_alloc_texture(renderer_, tt_2d, image_->width, image_->height, internal_format, image_->format);
  renderer_update_texture(renderer_, new_texture, ta_2d, image_->width, image_->height, image_->format, image_->buffer);
  return new_texture;
}

texture* renderer_make_texture_2d_from_file(renderer* renderer_, const char* file_name, const color_format internal_format)
{
  image* image_;
  texture* new_texture;

  image_ = io_load_image(file_name);
  if (!image_)
  {
    return 0;
  }
  new_texture = renderer_make_texture_2d_from_image(renderer_, image_, internal_format);
  image_free(image_); 
  return new_texture;
}

void renderer_add_vertex_attribute(vertex* vertex_, const int size, const data_type type, const char* name)
{
  attribute* new_attrib;

  new_attrib = (attribute*)malloc(sizeof(attribute));
  memset(new_attrib, 0, sizeof(attribute));
  new_attrib->size = size;
  new_attrib->type = type;
  new_attrib->name = (char*)malloc(sizeof(char*) * (strlen(name) + 1));
  strcpy(new_attrib->name, name);
  array_push(vertex_->attributes, (void*)new_attrib, 0);
}

void renderer_add_uniform(uniform_set* set, const uniform_type type, const int element_count, const void* data, const char* name)
{
  uniform* new_uniform;

  new_uniform = (uniform*)malloc(sizeof(uniform));
  memset(new_uniform, 0, sizeof(uniform));
  new_uniform->type = type;
  new_uniform->element_count = element_count;
  new_uniform->data = (void*)data;
  new_uniform->name = (char*)malloc(sizeof(char*) * (strlen(name) + 1));
  strcpy(new_uniform->name, name);
  array_push(set->uniforms, (void*)new_uniform, 0);
}

void renderer_set_wrapping(renderer* renderer_, const wrap_mode s, const wrap_mode t)
{
  renderer_->wrapping[0] = s;
  renderer_->wrapping[0] = t;
}

void renderer_set_filters(renderer* renderer_, const filter_mode min, const filter_mode mag, const filter_mode mip)
{
  renderer_->texture_filters[0] = min;
  renderer_->texture_filters[1] = mag; 
  renderer_->texture_filters[2] = mip; 
}

void renderer_set_viewport(renderer* renderer_, const int x, const int y, const int width, const int height)
{
  viewport* v = &renderer_->current_viewport;

  if (v->x != x || v->x != x || v->width != width || v->height != height)
  {
    glViewport(x, y, width, height);
    v->x = x;
    v->y = y;
    v->width = width;
    v->height = height;
  }
}

void renderer_set_fill_mode(renderer* renderer_, const face_type type, const polygon_mode mode)
{
  if (renderer_->fill_modes[type] != mode)
  {
    glPolygonMode(face_type_lookup[type], polygon_mode_lookup[mode]);
    renderer_->fill_modes[type] = mode;
  }
}

void renderer_set_polygon_face(renderer* renderer_, const vertex_order order)
{
  if (renderer_->polygon_face != order) 
  {
    glFrontFace(vertex_order_lookup[order]);
    renderer_->polygon_face = order;
  }
}

void renderer_set_blend(renderer* renderer_, const blend_mode source_factor, const blend_mode destination_factor)
{
  blend_mode* bm = renderer_->blend_modes;

  if (bm[0] != source_factor || bm[1] != destination_factor)
  {
    glBlendFunc(blend_mode_lookup[source_factor], blend_mode_lookup[destination_factor]);
    bm[0] = source_factor;
    bm[1] = destination_factor;
  }
}

void renderer_set_depth_test(renderer* renderer_, const test_function depth_function)
{
  if (renderer_->depth_function != depth_function) 
  {
    glDepthFunc(test_function_lookup[depth_function]);
    renderer_->depth_function = depth_function;
  }
}

void renderer_set_stencil(renderer* renderer_, const test_function stencil_function, const int reference, const unsigned int mask, const stencil_op stencil_fail, const stencil_op stencil_pass_depth_fail, const stencil_op stencil_pass)
{
  stencil_op* so = renderer_->stencil_ops;

  glStencilFunc(test_function_lookup[stencil_function], reference, mask);
  if (so[0] != stencil_fail || so[1] != stencil_pass_depth_fail || so[2] != stencil_pass)
  {
    glStencilOp(stencil_op_lookup[stencil_fail], stencil_op_lookup[stencil_pass_depth_fail], stencil_op_lookup[stencil_pass]);
    so[0] = stencil_fail;
    so[1] = stencil_pass_depth_fail;
    so[2] = stencil_pass;
  }
}

void renderer_set_cull_mode(renderer* renderer_, const cull_mode mode)
{
  if (renderer_->face_cull_mode != mode)
  {
    glCullFace(cull_mode_lookup[mode]);
    renderer_->face_cull_mode = mode;
  }
}

void renderer_enable_mipmaps(renderer* renderer_)
{
  renderer_->mipmaps = 1;
}

void renderer_enable_blend(renderer* renderer_)
{
  if (!renderer_->blend)
  {
    glEnable(GL_BLEND);
    renderer_->blend = 1;
  }
}

void renderer_enable_stencil(renderer* renderer_)
{
  if (!renderer_->stencil)
  {
    glEnable(GL_STENCIL_TEST);
    renderer_->stencil = 1;
  }
}

void renderer_enable_depth_test(renderer* renderer_)
{
  if (!renderer_->depth_test)
  {
    glEnable(GL_DEPTH_TEST);
    renderer_->depth_test = 1;
  }
}

void renderer_enable_cull_face(renderer* renderer_)
{
  if (!renderer_->face_cull)
  {
    glEnable(GL_CULL_FACE);
    renderer_->face_cull = 1;
  }
}

void renderer_disable_mipmaps(renderer* renderer_)
{
  renderer_->mipmaps = 0;
}

void renderer_disable_blend(renderer* renderer_)
{
  if (renderer_->blend)
  {
    glDisable(GL_BLEND);
    renderer_->blend = 0;
  }
}

void renderer_disable_stencil(renderer* renderer_)
{
  if (renderer_->stencil)
  {
    glDisable(GL_STENCIL_TEST);
    renderer_->stencil = 0;
  }
}

void renderer_disable_depth_test(renderer* renderer_)
{
  if (renderer_->depth_test)
  {
    glDisable(GL_DEPTH_TEST);
    renderer_->depth_test = 0;
  }
}

void renderer_disable_cull_face(renderer* renderer_)
{
  if (renderer_->face_cull)
  {
    glDisable(GL_CULL_FACE);
    renderer_->face_cull = 0;
  }
}

void renderer_clear_buffers(const int clear_color_buffer, const int clear_depth_buffer, const int clear_stencil_buffer, const float red, const float green, const float blue, const float alpha)
{
  glClearColor(red, green, blue, alpha);
  glClear(clear_color_buffer?GL_COLOR_BUFFER_BIT:0 | clear_stencil_buffer?GL_DEPTH_BUFFER_BIT:0 | clear_stencil_buffer?GL_STENCIL_BUFFER_BIT:0);
}

void renderer_free_shader(shader* shader_)
{
  if (shader_->shader_object) 
  {
    glDeleteShader(shader_->shader_object);
  }
  free(shader_);
}

void renderer_free_program(program* program_)
{
  if (program_->program_object) 
  {
    glDeleteProgram(program_->program_object);
  }
  free(program_);
}

void renderer_free_texture(texture* texture_)
{
  if (texture_->texture_object)
  {
    glDeleteTextures(1, &texture_->texture_object);
  }
  free(texture_);
}

void renderer_free_buffer(buffer* buffer_)
{
  if(buffer_->map.mode != mm_not_mapped)
  {
    renderer_unmap_buffer(buffer_);
  }
  if (buffer_->buffer_object)
  {
    glDeleteBuffers(1, &buffer_->buffer_object);
  }
  free(buffer_);
}

void renderer_free_uniform_set(uniform_set* set)
{
  int loop;
  uniform* uform;

  for (loop = 0; loop < set->uniforms->usage; loop++)
  {
    uform = (uniform*)set->uniforms->elements[loop].pointer;
    if (uform) 
    {
      if (uform->name) free(uform->name);
      free(uform);
    }
  }
  array_free(set->uniforms);
  free(set);
}

void renderer_free_vertex(vertex* vertex_)
{
  int loop;
  attribute* attrib;

  for (loop = 0; loop < vertex_->attributes->usage; loop++)
  {
    attrib = (attribute*)vertex_->attributes->elements[loop].pointer;
    if (attrib) 
    {
      if (attrib->name) free(attrib->name);
      free(attrib);
    }
  }
  array_free(vertex_->attributes);
  free(vertex_);
}

void renderer_free_framebuffer(framebuffer* framebuffer_)
{
  int loop;

  for (loop = 0; loop < framebuffer_->color_attachment_count + framebuffer_->has_depth_attachment; loop++)
  {
    renderer_free_texture(framebuffer_->attachments[loop]);
  }
  free(framebuffer_->attachments);
  if (framebuffer_->framebuffer_object)
  {
    glDeleteFramebuffers(1, &framebuffer_->framebuffer_object);
  }
  free(framebuffer_);
}

void renderer_free(renderer* renderer_)
{
  free(renderer_->active_textures);
  free(renderer_);
}
