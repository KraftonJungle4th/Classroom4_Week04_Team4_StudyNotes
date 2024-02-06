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


rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->nil = nil;
  p->root = nil;
  return p;
}

// 추가함수
void postorder(rbtree * t, node_t * target){
  if (target->left != t->nil){
      postorder(t, target -> left);
  }

  if (target->right != t->nil){
      postorder(t, target -> right);
  } 

  free(target);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory

  if (t->root != t->nil){
    postorder(t, t->root);
  }

  free(t->nil);
  free(t);
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t *)calloc(1, sizeof(node_t));

  z->key = key;
  z->parent = NULL;
  z->left = NULL;
  z->right = NULL;

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
  node_t * cur = t -> root;

  while(cur != t->nil){
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  
  node_t * cur = t -> root;

  while(cur != t->nil){
    cur = cur->right;
  }
  return cur;
}

node_t *find_successor(const rbtree *t, node_t* target) {
  // TODO: implement find

  while(target->left != t->nil){
    target = target->left;
  }

  return target;
}


int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}


// 추가함수
void inorder(rbtree * t, node_t * target, int index, size_t size, key_t *arr){
  if (target == t->nil){
    return;
  }
      inorder(t, target -> left, index, size, arr);
      if (index < size){
        arr[index++] = target->key;
      }
      inorder(t, target -> right, index, size, arr);
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array

  inorder(t, t->root, 0, n, arr);

  return 0;
}