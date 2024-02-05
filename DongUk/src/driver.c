#include "rbtree.h"
#include "rbtree.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    rbtree *result;
    result = new_rbtree();
    printf("%d", result);
    return 0;
}