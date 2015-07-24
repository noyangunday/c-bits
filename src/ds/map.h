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
*  date:      dec 25th, 2006
*  abstract:  red-black tree based type independent map
*/

#ifndef __VISUEM_MAP_H__
#define __VISUEM_MAP_H__

#include "generic.h"

#ifdef __cplusplus
extern "C" {
#endif

  /** 
   * /brief key-value pair.
   */
  typedef struct 
  {
    char*                 key;
    generic               value;
  } meta;

  /** 
   * /brief red-black tree node.
   */
  typedef struct rbnode_ 
  {
    int                   color;
    meta                  data;
    struct rbnode_ *      left;
    struct rbnode_ *      right;
    struct rbnode_ *      parent;
  } rbnode;

  /** 
   * /brief red-black tree based map
   */
  typedef struct 
  {
    rbnode*               root;
    int                   size;
  } map;

  /** 
   * /brief allocates a map
   */
  extern map* map_alloc();

  /** 
   * /bries deletes a map
   * not responsible for deallocation of data within nodes
   */    
  extern void map_free(map* tree);

  /** 
   * /brief insert a node into map.
   */
  extern void map_insert(map* tree, const char* key, void* data, const int tag);

  /** 
   * /brief searches a map with a specific key 
   *
   * /return a void pointer to element related with given key.
   *         a null pointer if key is not found.
   */
  extern generic* map_search(map* tree, const char* key);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif