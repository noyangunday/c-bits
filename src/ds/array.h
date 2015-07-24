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
*  abstract:  type independent dynamic array
*/

#ifndef __VISUEM_ARRAY_H__
#define __VISUEM_ARRAY_H__

#include "generic.h"

#ifdef __cplusplus
extern "C" {
#endif

  /** 
   * /brief array structure
   */      
  typedef struct 
  {   
    generic*  elements;    /* elements of array */     
    int       capacity;    /* current capacity of array */                    
    int       usage;       /* current usage of array */                      
  } array; 

  /**
   * /brief creates an empty array 
   * /return an empty array instance. array elements aren't allocated yet. you need
   *         to push or insert an element to allocate elements. (lazy alloc.)
   */
  extern array* array_alloc();    

  /** 
   * /brief deletes an array 
   * not responsible for deallocation of data within nodes
   */      
  extern void array_free(array* array_);

  /** 
   * /brief pushes an element to the end of the array.
   */        
  extern generic* array_push(array* array_, void* data, const int tag);      

  /**
   * /brief pops back the element at the end of the array.
   */  
  extern generic* array_pop(array* array_);

  /** 
   * /brief inserts an element to a given index of the array.
   */    
  extern void array_insert(array* array_, const int index, void* data, const int tag);

  /** 
   * /brief removes an element at a given index of the array.
   */              
  extern void array_remove(array* array_, const int index);

  /** 
   * /brief clears all elements of the array.
   * not responsible for deallocation of data within nodes
   */
  extern void array_reset(array* array_);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif