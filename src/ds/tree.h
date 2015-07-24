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
*  date:      dec 24th, 2006
*  abstract:  type independent tree
*/

#ifndef __VISUEM_TREE_H__
#define __VISUEM_TREE_H__

#include "generic.h"

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * /brief specifies tree insertion method 
   */
  typedef enum 
  {
    insert_as_first_child,      /* insert as the first child of the node */
    insert_as_last_child,       /* insert as the last child of the node */
    insert_before,              /* insert before the node */
    insert_after,               /* insert after the node */
  } tree_insertion;

  /**
   * \brief tree node structure
   */
  typedef struct tree_node_ {
    struct tree_node_*    parent;
    struct tree_node_*    first_child;
    struct tree_node_*    last_child;
    struct tree_node_*    prev_sibling;
    struct tree_node_*    next_sibling;
    generic               data;
  } tree_node;

  /** 
   * /brief creates a node with given data
   */
  extern tree_node* tree_alloc(void* data, const int tag);

  /** 
   * /brief deletes a node and its children
   * not responsible for deallocation of data within nodes
   */
  extern void tree_free(tree_node* node);

  /** 
   * \brief inserts a node with given method 
   */
  extern void tree_insert(tree_node* location, tree_node* node, const tree_insertion method);

  /*
   * /brief inserts a data to tree with given method  
   * creates a node with given data and inserts
   */
  extern tree_node* tree_insert_data(tree_node* location, void* data, const int tag, const tree_insertion method);

  /** 
   * /brief removes a node from the tree
   */
  extern void tree_remove(tree_node* node);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
