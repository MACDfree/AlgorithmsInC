#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void banana()
{
    printf("in banana()\n");
    longjmp(buf, 4);
    printf("you'll never see this.");
}

int main()
{
    int a=5,b=-3,c=4;
    printf("%d%d\n", (++a,b++), c-2);
    return 0;
}
