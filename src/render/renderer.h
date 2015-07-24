/*

  The MIT License (MIT)

  Copyright (c) 2015 VISUEM LTD

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

/*
*  author:    noyan gunday
*  date:      feb 4th, 2008
*  abstract:  opengl es 2.0 renderer.
*/

#ifndef __VISUEM_RENDERER_H__
#define __VISUEM_RENDERER_H__

#include "image.h"
#include "array.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#include <GL/glew.h>
#include <Windows.h> 
#include <gl/GL.h>
#else
#include <OpenGL/gl.h>
#endif

  /**
   * /brief specifies data type of vertex attribute
   */
  typedef enum 
  {
    dt_int_8,             /* 8-bits signed integer */
    dt_uint_8,            /* 8-bits unsigned integer */
    dt_int_16,            /* 16-bits signed integer */
    dt_uint_16,           /* 16-bits unsigned integer */
    dt_int_32,            /* 32-bits signed integer */
    dt_uint_32,           /* 32-bits unsigned integer */
    dt_f_32,              /* 32-bits floating point number */
    dt_f_64,              /* 64-bits floating point number */
  } data_type;

  /**
   * /brief specifies data type of a uniform
   */
  typedef enum 
  {
    ut_int_1,             /* single integer */
    ut_int_2,             /* vector of 2 integers */
    ut_int_3,             /* vector of 3 integers */
    ut_int_4,             /* vector of 4 integers */
    ut_float_1,           /* single float */
    ut_float_2,           /* vector of 2 floats */
    ut_float_3,           /* vector of 3 floats */
    ut_float_4,           /* vector of 4 float */
    ut_float_2x2,         /* 2x2 float matrix */
    ut_float_3x3,         /* 3x3 float matrix */
    ut_float_4x4,         /* 4x4 float matrix */
    ut_sampler,           /* texture sampler */
  } uniform_type;

  /** 
   * /brief specifies type of a shader
   */
  typedef enum 
  {
    st_vertex,            /* vertex shader */
    st_fragment,          /* fragment shader */
  } shader_type;

  /** 
   * /brief specifies type of a buffer
   */
  typedef enum 
  {
    bt_vertex,            /* vertex buffer */
    bt_index,             /* index buffer */
  } buffer_type;

  /**
   * /brief specifies type of a texture
   */
  typedef enum 
  {
    tt_2d,                /* 2d texture */
    tt_cube,              /* cube texture */
  } texture_type;

  /** 
   * /brief specifies texture target
   */
  typedef enum 
  {
    ta_2d,                /* 2d texture target */
    ta_cube_positive_x,   /* positive x face of cube texture */
    ta_cube_negative_x,   /* positive x face of cube texture */
    ta_cube_positive_y,   /* positive x face of cube texture */
    ta_cube_negative_y,   /* positive x face of cube texture */
    ta_cube_positive_z,   /* positive x face of cube texture */
    ta_cube_negative_z,   /* positive x face of cube texture */
  } texture_target;

  /** 
   * /brief specifies usage of a buffer
   */
  typedef enum 
  {
    bu_stream_draw,       /* content will be modified by the application once and will be used at most a few times */
    bu_stream_read,       /* content will be modified by reading data from GL, returned when queried by application and will be used at most a few times */
    bu_stream_copy,       /* content will be modified by reading data from GL, used as the source for for gl drawing and will be used at most a few times */
    bu_static_draw,       /* content will be modified by the application once and will be used many times */
    bu_static_read,       /* content will be modified by reading data from GL, returned when queried by application once and will be used many times */
    bu_static_copy,       /* content will be modified by reading data from GL, used as the source for for gl drawing once and will be used many times */
    bu_dynamic_draw,      /* content will be modified by the application many times and will be used many times */
    bu_dynamic_read,      /* content will be modified by reading data from GL, returned when queried by application many times and will be used many times */
    bu_dynamic_copy,      /* content will be modified by reading data from GL, used as the source for for gl drawing many times and will be used many times */
  } buffer_usage;

  /** 
   * /brief specifies mapping mode of a buffer
   */
  typedef enum 
  {
    mm_not_mapped,        /* not mapped */
    mm_read_only,         /* read only access */
    mm_write_only,        /* write only access */
    mm_read_write,        /* read/write access */
  } map_mode;

  /**
   * /brief specifies draw mode
   */
  typedef enum 
  {
    dm_points,            /* draw points */
    dm_lines,             /* draw lines */
    dm_line_loop,         /* draw line loop */
    dm_line_strip,        /* draw line strip */
    dm_triangles,         /* draw triangles */
    dm_triangle_strip,    /* draw triangle strip */
    dm_quads,             /* draw quads */
    dm_quad_strip,        /* draw quad strips */
    dm_polygon,           /* draw polygons */
  } draw_mode;

  /**
   * /brief specifies alpha blend mode
   */
  typedef enum 
  {
    bm_zero,                          /* 0 0 0 0 */
    bm_one,                           /* 1 1 1 1 */
    bm_source_color,                  /* R s / k R G s / k G B s / k B A s / k A */
    bm_one_minus_source_color,        /* 1 1 1 1 - R s / k R G s / k G B s / k B A s / k A */
    bm_destination_color,             /* R d / k R G d / k G B d / k B A d / k A */
    bm_one_minus_destination_color,   /* 1 1 1 1 - R d / k R G d / k G B d / k B A d / k A */
    bm_source_alpha,                  /* A s / k A A s / k A A s / k A A s / k A */
    bm_one_minus_source_alpha,        /* 1 1 1 1 - A s / k A A s / k A A s / k A A s / k A */
    bm_destination_alpha,             /* A d / k A A d / k A A d / k A A d / k A */
    bm_one_minus_destination_alpha,   /* 1 1 1 1 - A d / k A A d / k A A d / k A A d / k A */
    bm_source_alpha_saturate,         /* i i i 1 */
  } blend_mode;

  /** 
   * /brief specifies depth test function
   */
  typedef enum 
  {
    tf_never,               /* never passes */
    tf_always,              /* always passes */
    tf_equal,               /* passes if the incoming depth value is equal to the stored depth value */
    tf_not_equal,           /* passes if the incoming depth value is not equal to the stored depth value */
    tf_less,                /* passes if the incoming depth value is less than the stored depth value */
    tf_less_or_equal,       /* passes if the incoming depth value is less than or equal to the stored depth value. */
    tf_greater,             /* passes if the incoming depth value is greater than the stored depth value */
    tf_greater_or_equal,    /* passes if the incoming depth value is greater than or equal to the stored depth value. */
  } test_function;

  /** 
   * /brief specifies stencil operation
   */
  typedef enum 
  {
    so_keep,                /* stencil value unchanged */
    so_zero,                /* stencil value set to zero */
    so_replace,             /* stencil value replaced by stencil reference value */
    so_increment,           /* stencil value incremented */
    so_increment_and_wrap,  /* stencil value decremented and wrap to maximum unsigned integer */
    so_decrement,           /* stencil value decremented */
    so_decrement_and_wrap,  /* stencil value decremented and wrap to maximum unsigned integer */
    so_invert,              /* stencil value decremented and wrap to maximum unsigned integer */
  } stencil_op;

  /** 
   * /brief specifies vertex face ordering 
   */
  typedef enum 
  {
    vo_counter_clockwise,   /* order vertices counter clockwise */
    vo_clockwise,           /* order vertices clockwise */
  } vertex_order;

  /** 
   * /brief specifies face culling mode  
   */
  typedef enum 
  {
    cm_front,               /* front face culling */
    cm_back,                /* back face culling */
  } cull_mode;

  /** 
   * /brief specifies face rendering mode 
   */
  typedef enum 
  {
    ft_front,               /* front face */
    ft_back,                /* back face */
    ft_front_and_back,      /* front and back face */
  } face_type;

  /** 
   * /brief specifies polygon fill mode 
   */
  typedef enum 
  {
    pm_fill,                /* fills polygon */
    pm_wireframe,           /* draws wireframe polygon */
  } polygon_mode;

  /** 
   * /brief specifies texture wrap mode 
   */
  typedef enum
  {
    wm_repeat,              /* create a repeating pattern */
    wm_clamp_to_edge,       /* clamped to the range 1 2N 1 - 1 2N , where N is the size of the texture in the direction of clamping */
    wm_mirrored_repeat,     /* create a mirrored repeating pattern */
  } wrap_mode;

  /** 
   * /brief specifies texture filter
   */
  typedef enum
  {
    fm_nearest,             /* nearest filter */
    fm_linear,              /* linear texture filter */
  } filter_mode;

  /** 
   * /brief vertex attribute 
   */
  typedef struct {
    data_type       type;             /* type of vertex attribute data */
    int             size;             /* number of elements of this attribute per vertex (eg. vertex position has 3 elements; x, y and z) */
    char*           name;             /* name of the attribute. this should be the same with the attribute name in shader source code */
  } attribute;

  /** 
   * /brief dynamic vertex structure 
   */
  typedef struct {
    array*          attributes;       /* vertex attribute array */
    int             size;             /* size of a single vertex defined by this vertex structure */
  } vertex;

  /**
   * /brief shader uniform 
   */
  typedef struct {
    uniform_type    type;             /* type of uniform */
    int             element_count;    /* element count of uniform */
    void*           data;             /* pointer to uniform data in cpu controlled memory */
    char*           name;             /* name of the uniform. this should be the same with the uniform name in shader source code */
    GLint           location;         /* location of uniform in context */
  } uniform;

  /** 
   * /brief uniform set 
   */
  typedef struct {
    array*          uniforms;         /* shader uniform array */
  } uniform_set;

  /** 
   * /brief texture 
   */
  typedef struct {
    texture_type    type;             /* type of texture */
    unsigned int    height;           /* height of texture in video memory */
    unsigned int    width;            /* width of texture in video memory */
    float           height_ratio;     /* ratio of height of the original image and height of the texture */
    float           width_ratio;      /* ratio of width of the original image and width of the texture */
    GLuint          texture_object;   /* handle to texture object within the context */
    int             mipmaps;          /* texture has mipmaps? */
  } texture;


  /** 
   * /brief glsl shader 
   */
  typedef struct {
    shader_type     type;             /* type of shader */
    int             compiled;         /* is this shader compiled? */
    GLuint          shader_object;    /* handle to shader object within the context */
  } shader;

  /** 
   * /brief shader program 
   */
  typedef struct {
    int             linked;           /* is this program linked? */
    GLuint          program_object;   /* handle to program object within the context */
  } program;

  /** 
   * /brief buffer map 
   */
  typedef struct {
    map_mode        mode;             /* memory map mode */ 
    void*           mapped_memory;    /* pointer to memory */
  } buffer_map;

  /** 
   * /brief buffer 
   */
  typedef struct {
    buffer_type     type;             /* type of buffer */
    int             size;             /* size of the buffer */
    buffer_map      map;              /* pointer to mapped memory */
    GLuint          buffer_object;    /* handle to buffer object within the context */
  } buffer;

  /** 
   * /brief framebuffer 
   */
  typedef struct {
    int             complete;               /* is this framebuffer complete? */
    int             width;                  /* width of framebuffer */
    int             height;                 /* height of framebuffer */
    int             color_attachment_count; /* number of color attachments attached to framebuffer */
    int             has_depth_attachment;   /* framebuffer has depth attachment? */
    texture**       attachments;            /* attachments of framebuffer */
    GLuint          framebuffer_object;     /* handle to frambuffer object within the context */
  } framebuffer;

  /** 
   * /brief viewport 
   */
  typedef struct {
    int             x;                /* x offset of viewport */
    int             y;                /* y offset of viewport */
    int             width;            /* width of viewport */
    int             height;           /* height of viewport */
  } viewport;

  /** 
   * /brief renderer
   * only 1 instance of renderer should be allocated per gl context.
   */
  typedef struct {
    int             tex_unit_count;     /* number of useable texture image units */
    int             attachment_count;   /* number of useable color attachments for framebuffer objects */
    texture**       active_textures;    /* keeps track of actively bound textures in texture image units */
    buffer*         active_buffers[2];  /* keeps track of actively bound buffers */
    program*        active_program;     /* keeps track of program currently in use */
    framebuffer*    active_framebuffer; /* keeps track of framebuffer currently in use */
    wrap_mode       wrapping[2];        /* current texture wrap mode state of renderer (0 - s coordinate, 1 - t coordinate) */
    filter_mode     texture_filters[3]; /* current texture filter state of renderer (0 - min filter, 1 - mag filter, 2 - mip filter) */
    int             mipmaps;            /* current mipmapping state of renderer */
    stencil_op      stencil_ops[3];     /* current stencil operation states (0 - stencil fail, 1 - stencil pass depth fail, 3 - stencil pass) */
    test_function   depth_function;     /* current depth test function */
    blend_mode      blend_modes[2];     /* current blend modes (0 - source blend factor, 1 - destination blend factor) */
    vertex_order    polygon_face;       /* vertex order of polygon faces */
    cull_mode       face_cull_mode;     /* current face culling mode of renderer */
    polygon_mode    fill_modes[3];      /* current polygon fill mode of faces (0 - front facing polygons, 1 - back facing polygons, 2 - front and back facing polygons) */
    int             stencil;            /* stencil test state flag */
    int             blend;              /* alpha blending state flag */ 
    int             depth_test;         /* depth test state flag */
    int             face_cull;          /* culling state flag */
    viewport        current_viewport;   /* current viewport of renderer */
  } renderer;

  /** 
   * /brief creates a renderer 
   */
  extern renderer* renderer_alloc();

  /** 
   * /brief creates an empty texture 
   */
  extern texture* renderer_alloc_texture(renderer* renderer_, texture_type type, const int height, const int width, const color_format internal_format, const color_format format);

  /** 
   * /brief creates a vertex buffer 
   */
  extern buffer* renderer_alloc_buffer(renderer* renderer_, const buffer_type type, const int size, const buffer_usage usage);

  /** 
   * /brief creates a vertex shader 
   */
  extern shader* renderer_alloc_shader(const shader_type type);

  /**
   * /brief creates a shader program 
   */
  extern program* renderer_alloc_program();

  /**
   * /brief creates a vertex structure 
   */
  extern vertex* renderer_alloc_vertex(const int struct_size);

  /**
   * /brief creates a uniform set 
   */
  extern uniform_set* renderer_alloc_uniform_set();

  /** 
   * /brief creates a framebuffer 
   */
  extern framebuffer* renderer_alloc_framebuffer(renderer* renderer_, const int width, const int height, const int color_attachment_count, const int has_depth_attachment);

  /** 
   * /brief binds texture to a tex unit 
   */
  extern void renderer_bind_texture(renderer* renderer_, const int tex_unit, texture* texture_);

  /** 
   * /brief binds program 
   */
  extern void renderer_bind_program(renderer* renderer_, program* program_);

  /** 
   * /brief binds a buffer 
   */
  extern void renderer_bind_buffer(renderer* renderer_, buffer* buffer_);

  /** 
   * /brief binds a framebuffer 
   */
  extern void renderer_bind_framebuffer(renderer* renderer_, framebuffer* framebuffer_);

  /** 
   * /brief activates a vertex buffer 
   */
  extern void renderer_activate_vertex_buffer(renderer* renderer_, buffer* buffer_, const vertex* vertex_);

  /** 
   * /brief draws elements of an index buffer 
   */
  extern void renderer_execute_index_buffer(renderer* renderer_, buffer* buffer_, const int start, const int count, const draw_mode mode);

  /** 
   * /brief draws a client-side vertex array 
   */
  extern void renderer_draw_vertex_array(renderer* renderer_, void* vertex_array, const vertex* vertex_, const int count, const draw_mode mode);

  /** 
   * /brief binds uniforms of a uniform set 
   */
  extern void renderer_bind_uniforms(const uniform_set* set);

  /** 
   * /brief unbinds a buffer 
   */
  extern void renderer_unbind_buffer(renderer* renderer_, buffer_type slot);

  /** 
   * /brief updates texture data 
   */
  extern void renderer_update_texture(renderer* renderer_, texture* texture_, const texture_target target, const int height, const int width, const color_format format, const void* data);

  /** 
   * /brief updates buffer data 
   */
  extern void renderer_update_buffer(renderer* renderer_, buffer* buffer_, const int size, const void* data);

  /** 
   * /brief maps a buffer 
   */
  extern void renderer_map_buffer(renderer* renderer_, buffer* buffer_, const map_mode mode);

  /** 
   * /brief unmaps a buffer 
   */ 
  extern void renderer_unmap_buffer(buffer* buffer_);

  /** 
   * /brief compiles shader 
   */
  extern void renderer_compile_shader(shader* shader_, const char* source_code);

  /** 
   * /brief attaches a shader to a program 
   */
  extern void renderer_attach_shader(program* program_, const shader* shader_);

  /** 
   * /brief links a shader program 
   */
  extern void renderer_link_program(program* program_, const vertex* vertex_);

  /** 
   * /brief fills uniform locations of a uniform set 
   */
  extern void renderer_fill_uniform_locations(program* program_, uniform_set* set);

  /** 
   * /brief creates a 2d texture and fills it with image data 
   */
  extern texture* renderer_make_texture_cube_from_image(renderer* renderer_, const image* image[6], const color_format internal_format);

  /** 
   * /brief creates a 2d texture, loads image files and fills texture with image data 
   */
  extern texture* renderer_make_texture_cube_from_file(renderer* renderer_, const char* file_name[6], const color_format internal_format);

  /** 
   * /brief creates a 2d texture and fills it with image data 
   */
  extern texture* renderer_make_texture_2d_from_image(renderer* renderer_, const image* image, const color_format internal_format);

  /** 
   * /brief creates a 2d texture, loads image file and fills texture with image data 
   */
  extern texture* renderer_make_texture_2d_from_file(renderer* renderer_, const char* file_name, const color_format internal_format);

  /** 
   * /brief adds a new vertex attribute to vertex 
   */
  extern void renderer_add_vertex_attribute(vertex* vertex_, const int size, const data_type type, const char* name);

  /** 
   * /brief adds a new shader uniform to uniform set
   */
  extern void renderer_add_uniform(uniform_set* set, const uniform_type type, const int element_count, const void* data, const char* name);

  /** 
   * /brief sets texture wrapping mode of renderer 
   */
  extern void renderer_set_wrapping(renderer* renderer_, const wrap_mode s, const wrap_mode t);

  /** 
   * /brief sets texture filter mode of renderer 
   */
  extern void renderer_set_filters(renderer* renderer_, const filter_mode min, const filter_mode mag, const filter_mode mip);

  /** 
   * /brief sets viewport of renderer 
   */
  extern void renderer_set_viewport(renderer* renderer_, const int x, const int y, const int width, const int height);

  /** 
   * /brief sets polygon fill mode of renderer 
   */
  extern void renderer_set_fill_mode(renderer* renderer_, const face_type type, const polygon_mode mode);

  /** 
   * /brief sets vertex ordering of renderer 
   */
  extern void renderer_set_polygon_face(renderer* renderer_, const vertex_order order);

  /** 
   * /brief sets blending state of renderer 
   */
  extern void renderer_set_blend(renderer* renderer_, const blend_mode source_factor, const blend_mode destination_factor);

  /** 
   * /brief sets depth test state of renderer 
   */
  extern void renderer_set_depth_test(renderer* renderer_, const test_function depth_function);

  /** 
   * /brief sets stencil state of renderer 
   */
  extern void renderer_set_stencil(renderer* renderer_, const test_function stencil_function, const int reference, const unsigned int mask, const stencil_op stencil_fail, const stencil_op stencil_pass_depth_fail, const stencil_op stencil_pass);

  /** 
   * /brief sets face culling mode of renderer 
   */
  extern void renderer_set_cull_mode(renderer* renderer_, const cull_mode mode);

  /** 
   * /brief enables mipmapping 
   */
  extern void renderer_enable_mipmaps(renderer* renderer_);

  /** 
   * /brief enables alpha blending 
   */
  extern void renderer_enable_blend(renderer* renderer_);

  /** 
   * /brief enables stencil test 
   */
  extern void renderer_enable_stencil(renderer* renderer_);

  /** 
   * /brief enables depth test 
   */
  extern void renderer_enable_depth_test(renderer* renderer_);

  /** 
   * /brief enables face culling 
   */
  extern void renderer_enable_cull_face(renderer* renderer_);

  /** 
   * /brief disables mipmapping 
   */
  extern void renderer_disable_mipmaps(renderer* renderer_);

  /** 
   * /brief disables alpha blending 
   */
  extern void renderer_disable_blend(renderer* renderer_);

  /** 
   * /brief disables stencil test 
   */
  extern void renderer_disable_stencil(renderer* renderer_);

  /** 
   * /brief disables depth test 
   */
  extern void renderer_disable_depth_test(renderer* renderer_);

  /** 
   * /brief disables face culling 
   */
  extern void renderer_disable_cull_face(renderer* renderer_);

  /** 
   * /brief clears specified buffers with specified color 
   */
  extern void renderer_clear_buffers(const int clear_color_buffer, const int clear_depth_buffer, const int clear_stencil_buffer, const float red, const float green, const float blue, const float alpha);

  /** 
   * /brief deletes a shader 
   */
  extern void renderer_free_shader(shader* shader_);

  /** 
   * /brief deletes a program 
   */
  extern void renderer_free_program(program* program_);

  /** 
   * /brief deletes a texture 
   */
  extern void renderer_free_texture(texture* texture_);

  /** 
   * /brief deletes a buffer 
   */
  extern void renderer_free_buffer(buffer* buffer_);

  /** 
   * /brief deletes a uniform set 
   */
  extern void renderer_free_uniform_set(uniform_set* set);

  /** 
   * /brief deletes a vertex structure 
   */
  extern void renderer_free_vertex(vertex* vertex_);

  /** 
   * /brief deletes a framebuffer 
   */
  extern void renderer_free_framebuffer(framebuffer* framebuffer_);

  /** 
   * /brief deletes a renderer 
   */
  extern void renderer_free(renderer* renderer_);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
