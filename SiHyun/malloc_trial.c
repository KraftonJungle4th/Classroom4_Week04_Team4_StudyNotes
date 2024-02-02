#include <stdio.h>
#include <malloc.h>

void main()
{
    char *p_name;
    p_name = (char *)malloc(32);
    if(p_name != NULL) {
        printf("Your name :");
        gets(p_name);
        printf("Hi ~ %s\n", p_name);
        free(p_name);
    } else {
        printf("Memory allocation error!");
    }
}