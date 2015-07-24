#include "map.h"
#include <string.h> /* strcmp */
#include <stdlib.h> /* malloc */

/**
 * node colours
 */
#define RB_BLACK        0
#define RB_RED          1

/** 
 * set the node's right child 
 */
#define rbnode_set_right_child(n, r) do \
{ \
  (n)->right = (r); \
  if ((r) != 0) (r)->parent = (n); \
} while (0)

/**
 * set the node's left child 
 */
#define rbnode_set_left_child(n, l) do \
{ \
  (n)->left = (l); \
  if ((l) != 0) (l)->parent = (n); \
} while (0)


/** 
 * set tree's root node 
 */
#define tree_set_root(t, n) do \
{ \
  t->root = (n); \
  if ((n) != 0) { \
  (n)->parent = 0; \
  (n)->color = RB_BLACK; \
  } \
} while (0)

/** 
 * is node a left child of its parent 
 */
#define rbnode_is_left_child(n) ((n)->parent != 0 && (n)->parent->left == (n))

/** 
 * is node a right child of its parent 
 */
#define rbnode_is_right_child(n) ((n)->parent != 0 && (n)->parent->right == (n))

/** 
 * is node a root node 
 */
#define rbnode_is_root(n) ((n)->parent == 0)

/** 
 * is node a leaf node 
 */
#define rbnode_is_leaf(n) ((n)->left == 0 && (n)->right == 0)

/** 
 * is node a red node 
 */
#define rbnode_is_red(n) ((n)->color == RB_RED)

/** 
 * is node a black node 
 */
#define rbnode_is_black(n) ((n)->color == RB_BLACK)

/** 
 * node's right uncle (if its parent is a right child) 
 */
#define rbnode_right_uncle(n) ((n)->parent->parent->right)

/** 
 * node's left uncle (if its parent is a left child) 
 */
#define rbnode_left_uncle(n) ((n)->parent->parent->left)

/** 
 * node's grand parent node 
 */
#define rbnode_grand_parent(n) ((n)->parent->parent)

/** 
 * left rotate a node in a tree 
 */ 
void map_left_rotate(map* tree, rbnode* node);
void map_left_rotate(map* tree, rbnode* node) 
{                               
  rbnode* r;

  r = node->right;         
  rbnode_set_right_child(node, r->left);                                  
  if (rbnode_is_root(node)) tree_set_root(tree, r);                             
  else if (rbnode_is_right_child(node)) rbnode_set_right_child(node->parent, r);  
  else rbnode_set_left_child(node->parent, r);                            
  rbnode_set_left_child(r, node);               
};

/** 
 * right rotate a node in a tree 
 */ 
void map_right_rotate(map* tree, rbnode* node);
void map_right_rotate(map* tree, rbnode* node) 
{ 
  rbnode* l = node->left;

  rbnode_set_left_child(node, l->right); 
  if (rbnode_is_root(node)) tree_set_root(tree, l);
  else if (rbnode_is_right_child(node)) rbnode_set_right_child(node->parent, l);
  else rbnode_set_left_child(node->parent, l);
  rbnode_set_right_child(l, node);
}

/**
 * create a new node from key-value pair 
 * returns a red-black tree node with specified key-value pair
 */ 
rbnode* rbnode_create(const char* key, void* pointer, const int tag);
rbnode* rbnode_create(const char* key, void* pointer, const int tag)
{
  rbnode* new_node = (rbnode*)malloc(sizeof(rbnode));

  memset(new_node, 0, sizeof(rbnode));
  new_node->data.key = (char*)malloc(sizeof(char) * (strlen(key) + 1));
  strcpy(new_node->data.key, key);
  new_node->data.value.pointer = pointer;
  new_node->data.value.tag = tag,
  new_node->color = RB_RED;
  return new_node;
}

/** 
 * deletes a node.
 */ 
void rbnode_destroy(rbnode* node);
void rbnode_destroy(rbnode* node)
{
  if (node->data.key) free(node->data.key); 
  free(node); /* hmm */
}

/**
 * deletes a node with its children.
 */
void rbnode_destroy_with_children(rbnode* node);
void rbnode_destroy_with_children(rbnode* node)
{
  if (node->right) rbnode_destroy_with_children(node->right);
  if (node->left) rbnode_destroy_with_children(node->left);
  rbnode_destroy(node);
}

/** 
 * balances map after an insertion.
 */
void map_insert_balance(map* tree, rbnode* node);
void map_insert_balance(map* tree, rbnode* node) 
{
  rbnode* uncle;

  while (rbnode_is_root(node) == 0 && node->parent->color == RB_RED) 
  {
    if (rbnode_is_left_child(node->parent)) 
    {
      uncle = rbnode_right_uncle(node);
      if (uncle != 0 && rbnode_is_red(uncle)) 
      {
        node->parent->color = RB_BLACK;
        rbnode_grand_parent(node)->color = RB_RED;
        uncle->color = RB_BLACK;
        node = rbnode_grand_parent(node);
      }
      else 
      {
        if (rbnode_is_right_child(node)) 
        {
          node = node->parent;
          map_left_rotate(tree, node);
        }
        node->parent->color = RB_BLACK;
        rbnode_grand_parent(node)->color = RB_RED;
        map_right_rotate(tree, rbnode_grand_parent(node));
      }
    }
    else 
    {
      uncle = rbnode_left_uncle(node);
      if (uncle != 0 && rbnode_is_red(uncle)) 
      {
        node->parent->color = RB_BLACK;
        rbnode_grand_parent(node)->color = RB_RED;
        uncle->color = RB_BLACK;
        node = rbnode_grand_parent(node);
      }
      else 
      {
        if (rbnode_is_left_child(node)) 
        {
          node = node->parent;
          map_right_rotate(tree, node);
        }
        node->parent->color = RB_BLACK;
        rbnode_grand_parent(node)->color = RB_RED;
        map_left_rotate(tree, rbnode_grand_parent(node));
      }
    }
  }
  tree->root->color = RB_BLACK;
}

map* map_alloc() 
{
  map* new_tree = (map*)malloc(sizeof(map));
  memset(new_tree, 0, sizeof(map));
  return new_tree;
}

void map_free(map* tree) 
{
  rbnode_destroy_with_children(tree->root);
  free(tree);
}

void map_insert(map* tree, const char* key, void* data, const int tag) 
{
  rbnode* node = rbnode_create(key, data, tag);
  rbnode* iterator;
  int     comparison;
  int     fail = 0;

  if (tree->root == 0) 
  {
    tree_set_root(tree, node);
    tree->size = 0;
  }
  else 
  {
    iterator = tree->root;
    while (iterator != 0) 
    {
      comparison = strcmp(key, iterator->data.key);

      /* key already exists */
      if (comparison == 0) 
      {
        fail = 1;
        iterator = 0;
      }
      /* new key < iterator's key */
      else if (comparison < 0) 
      {
        /* left of iterator is free */
        if (iterator->left != 0) 
        {
          iterator = iterator->left;
        } 
        /* left of iterator is occupied */
        else 
        {
          rbnode_set_left_child(iterator, node);
          iterator = 0;
        }
      }
      /* new key > iterator's key */
      else 
      {
        /* right of iterator is free */
        if (iterator->right != 0) 
        {
          iterator = iterator->right;
        }
        /* right of iterator is occupied */
        else 
        {
          rbnode_set_right_child(iterator, node);
          iterator = 0;
        }
      }
    }
  }

  /* tree requires rebalancing */
  if (!fail) 
  {
    tree->size++;
    map_insert_balance(tree, node);
  }
}

generic* map_search(map* tree, const char* key)
{
  int comparison;

  rbnode* iterator = tree->root;
  while (iterator != 0) 
  {
    comparison = strcmp(key, iterator->data.key);
    /* found */
    if (comparison == 0) 
    {
      return &iterator->data.value;
    }
    /* key < iterator's key */
    else if (comparison < 0) 
    {
      iterator = iterator->left;
    }
    /* key > iterator's key */
    else 
    {
      iterator = iterator->right;
    }
  }
  return 0;
}
