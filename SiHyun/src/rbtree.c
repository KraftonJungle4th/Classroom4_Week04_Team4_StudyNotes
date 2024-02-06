#include "rbtree.h"
#include <stdlib.h>

void left_rotate(rbtree * t, node_t * x){
  node_t * y = x-> right;
  x->right = y->left;
  if(y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil){
    t->root = y;
  } else if (x == x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
    y->left = x;
    x->parent = y;
  }
}

void right_rotate(rbtree * t, node_t * x){
  node_t * y = x-> left;
  x->left = y->right;
  if(y->right != t->nil){
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil){
    t->root = y;
  } else if (x == x->parent->right){
    x->parent->right = y;
  } else {
    x->parent->left = y;
    y->right = x;
    x->parent = y;
  }
}

void insert_fixup(rbtree * t, node_t * z){
  node_t * y; // uncle
  while (z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left){ // 부모님이 할아버지의 왼쪽 자녀일 떄
      y = z->parent->parent->right;
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;
        z = z->parent->parent;
      } else if(z == z->parent->right){
        z = z->parent;
        left_rotate(t,z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t,z->parent->parent);
    }
    else{
      // 부모님이 오른쪽 자식인 경우
      y = z->parent->parent->left; 
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;
        z = z->parent->parent;
      } else if(z == z->parent->left){
        z = z->parent;
        right_rotate(t,z->parent->parent);

      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
        left_rotate(t,z);
    }
  } 
  t->root->color = RBTREE_BLACK;
}

void rbtree_transplant(rbtree * t, node_t * u, node_t * v) {
  if (u->parent == t->nil) {
    t->root = v;
  }
  else if (u == u->parent->left) {
    u->parent->left = v;
  }
  else {
    u->parent->right = v;
    }
  v->parent = u->parent;
}

void erase_fixup(rbtree * t, node_t * x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      node_t * w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else if (w->right->color == RBTREE_BLACK) {
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        right_rotate(t, w);
        w = x->parent->right;
      }
      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->right->color = RBTREE_BLACK;
      left_rotate(t, x->parent);
      x = t->root;
    }
  else
  {
    node_t * w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      if (w->left->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else if (w->left->color == RBTREE_BLACK) {
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        left_rotate(t, w);
        w = x->parent->left;
      }
      w->color = x->parent->color;
      x->parent->color = RBTREE_BLACK;
      w->left->color = RBTREE_BLACK;
      left_rotate(t, x->parent);
      x = t->root;
      }
  }
}

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->nil = nil;
  p->root = nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)calloc(1, sizeof(node_t));

  z->key = key;

  node_t* y = t->nil;
  node_t* x = t->root;

  while (x != t->nil){
      y = x;
      if (z->key < x->key){
        x = x->left;
      } else {
        x = x->right;
      }
  }
  z->parent = y;
  if (y == t->nil){
    t->root = z;
  } else if(z->key < y->key){
    y->left = z;
  } else{
    y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  insert_fixup(t, z);

  return t->root; 
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t* x = t->root;

  while (x != t->nil && key != x->key) {
    if (key < x->key) {
      x = x->left;
    }
    else {
      x = x->right;
    } 
  }
  return x == t->nil ? NULL : x;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t * cur = t -> root -> right;

  while(cur != t->nil){
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  
  node_t * cur = t -> root -> left;

  while(cur != t->nil){
    cur = cur->right;
  }
  return cur;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;
  node_t *x = t->root;
  color_t y_original_color = y->color;

  if (z->left == t->nil) {
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if (z->right == t->nil) {
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else {
    y = rbtree_min(t);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    }
    else {
      rbtree_transplant(t, y, y->right);
      }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  if (y_original_color == RBTREE_BLACK) {
    erase_fixup(t, x);
    }
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}