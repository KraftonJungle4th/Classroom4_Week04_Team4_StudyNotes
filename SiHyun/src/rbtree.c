#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *root = (node_t *)calloc(1, sizeof(node_t));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  root = NULL;
  nil = NULL;
  p->root = root;
  p->nil = nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  // 할일: 트리노드의 메모리를 회수하는것?
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t z;
  z.key = key;
  z.parent = NULL;
  z.left = NULL;
  z.right = NULL;
  node_t* y = t->nil;
  node_t* x = t->root;
  while (x != t->nil){
      y = x;
      if (z.key < x->key){
        x = x->left;
      } else {
        x = x->right;
      }
  }
  z.parent = y;
  if (y == t->nil){
    t->root = &z;
  } else if(z.key < y->key){
    y->left = &z;
  } else{
    y->right = &z;
  }
  z.left = t->nil;
  z.right = t->nil;
  z.color = RBTREE_RED;
  // RB-Insert-Fixup(t, &z)
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  t->root;   

}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {

    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
