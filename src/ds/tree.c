#include "tree.h"
#include <stdlib.h> /* malloc */
#include <memory.h> /* memset */

tree_node* tree_alloc(void* data, const int tag)
{
  tree_node* new_node;

  new_node = (tree_node*)malloc(sizeof(tree_node));
  memset(new_node, 0, sizeof(tree_node));
  new_node->data.pointer = data;
  new_node->data.tag = tag;

  return new_node;
}

void tree_free(tree_node* node)
{
  tree_node* iterator = node->first_child;

  while (iterator) 
  {
    tree_free(iterator);
    iterator = iterator->next_sibling;
  }
  free(node);
}

void tree_insert(tree_node* location, tree_node* node, const tree_insertion method)
{
  if (!location || !node) return;
  switch (method) 
  {
  case insert_before:
    node->next_sibling = location;
    node->prev_sibling = location->prev_sibling;
    node->parent = location->parent;
    if (location->prev_sibling) location->prev_sibling->next_sibling = node;
    else if (node->parent) node->parent->first_child = node;
    location->prev_sibling = node;
    break;
  case insert_after:
    node->next_sibling = location->next_sibling;
    node->prev_sibling = location;
    node->parent = location->parent;
    if (location->next_sibling) location->next_sibling->prev_sibling = node;
    else if (node->parent) node->parent->last_child = node;
    location->next_sibling = node;
    break;
  case insert_as_first_child:
    if (location->first_child) location->first_child->prev_sibling = node;
    node->next_sibling = location->first_child;
    node->prev_sibling = 0;
    node->parent = location;
    location->first_child = node;
    if (!location->last_child && !node->next_sibling) location->last_child = node; 
    break;
  case insert_as_last_child:
    if (location->last_child) location->last_child->next_sibling = node;
    node->next_sibling = 0;
    node->prev_sibling = location->last_child;
    node->parent = location;
    location->last_child = node;
    if (!location->first_child && !node->prev_sibling) location->first_child = node; 
    break;
  }
}

tree_node* tree_insert_data(tree_node* location, void* data, const int tag, const tree_insertion method)
{
  tree_node* new_node;

  if (!location) return 0;
  new_node = (tree_node*)malloc(sizeof(tree_node));
  new_node->first_child = 0;
  new_node->last_child = 0;
  new_node->data.pointer = data;
  new_node->data.tag = tag;
  tree_insert(location, new_node, method);

  return new_node;
}

void tree_remove(tree_node* node) 
{
  if (node->next_sibling) node->next_sibling->prev_sibling = node->prev_sibling;
  if (node->prev_sibling) node->prev_sibling->next_sibling = node->next_sibling;
  if (node->parent) 
  {
    if (node->parent->first_child == node) node->parent->first_child = node->next_sibling;
    if (node->parent->last_child == node) node->parent->last_child = node->prev_sibling;
    if (node->parent->first_child && !node->parent->last_child) node->parent->last_child = node->parent->first_child;
    if (!node->parent->first_child && node->parent->last_child) node->parent->first_child = node->parent->last_child;
  }
}
