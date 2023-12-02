#include <stdio.h>

// typedef char *string;

int main(void)
{
    char *s = "HI!";
    char **ss = &s;
    printf("%p\n", &s[0]);
    printf("%s\n", s);
    printf("%c\n", *s);
    printf("%p\n", ss);
    printf("%c\n", **ss);
    printf("%p\n",&s);
}