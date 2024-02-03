#include <stdio.h>
// #include <stdlib.h>

int main() {
    int a[3][2];
    printf("%d", a);
    printf("%d", &(a[0][0])+1);
    // printf("%d", a[0] + 1);
}
