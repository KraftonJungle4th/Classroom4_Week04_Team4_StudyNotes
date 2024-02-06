#include "rbtree.h"
#include "stdio.h"

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
  }
    y->left = x;
    x->parent = y;
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
  }
    y->right = x;
    x->parent = y;
}

void insert_fixup(rbtree * t, node_t * z){
  node_t * y = NULL; // uncle
  while (z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left){ // 부모님이 할아버지의 왼쪽 자녀일 떄
        y = z->parent->parent->right; 
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
        continue; // 추가
      } else {
        if(z == z->parent->right){ // 아빠는 왼쪽인데 나는 오른쪽이므로 지그재그. 그래서 왼쪽으로 로테이트
        z = z->parent;
        left_rotate(t,z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t,z->parent->parent);
      }
    }
    else{
      // 부모님이 오른쪽 자식인 경우
      y = z->parent->parent->left; 
      if (y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
        continue; // 추가
      } else {
        if(z == z->parent->left){
        z = z->parent;
        right_rotate(t,z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      left_rotate(t,z->parent->parent);
      }
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
        continue;
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else{ 
        if (w->right->color == RBTREE_BLACK) {
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
    }
    else
    {
      node_t * w = x->parent->left;
        if (w->color == RBTREE_RED) {
          w->color = RBTREE_BLACK;
          x->parent->color = RBTREE_RED;
          right_rotate(t, x->parent);
          w = x->parent->left;
          continue;
        }
        if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
          w->color = RBTREE_RED;
          x = x->parent;
        }
        else {
          if(w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          left_rotate(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
        }
    }
  }
  x->color = RBTREE_BLACK;
}



rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t *)malloc(sizeof(node_t));
  nil->color = RBTREE_BLACK;
  p->nil = nil;
  p->root = nil;
  return p;
}

// 추가함수
void postorder(rbtree * t, node_t * target){

    if (target != t->nil){
      postorder(t, target -> left);
      postorder(t, target -> right);
      free(target);
    }
}

void delete_rbtree(rbtree *t) {
  node_t *target = t->root;
  postorder(t, target);
  free(t->nil);
  free(t);
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)malloc(sizeof(node_t));

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
  node_t * cur = t -> root;

  while(cur->left != t->nil){
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t * cur = t -> root;

  while(cur->right != t->nil){
    cur = cur->right;
  }
  return cur;
}

node_t *find_successor(const rbtree *t, node_t* target) {
  while(target->left != t->nil){
    target = target->left;
  }

  return target;
}


int rbtree_erase(rbtree *t, node_t *p) {
  node_t *y = p;
  node_t *x = NULL;
  color_t y_original_color = y->color;

  if (p->left == t->nil) {
    x = p->right;
    rbtree_transplant(t, p, p->right);
  }
  else if (p->right == t->nil) {
    x = p->left;
    rbtree_transplant(t, p, p->left);
  }
  else {
    y = find_successor(t, p->right); // 삭제되는 노드 y로 생각하여 successor 찾는 과정이 수행되지 않았음
    y_original_color = y->color;
    x = y->right;
    if (y->parent == p) {
      x->parent = y;
    }
    else {
      rbtree_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
      }
    rbtree_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  
  }
  free(p);
  if (y_original_color == RBTREE_BLACK) {
    erase_fixup(t, x);
  }
  return 0;
}

// 추가함수
void inorder(const rbtree * t, node_t * target, int * index, size_t size, key_t *arr){
  if (target == t->nil){
    return;
  }
      inorder(t, target -> left, index, size, arr);
      if (*index < size){
        arr[(*index)++] = target->key;
      }
      inorder(t, target -> right, index, size, arr);
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  int cnt = 0;
  int * index = &cnt;

  inorder(t, t->root, index, n, arr);

  return 0;
}