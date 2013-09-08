#include <stdio.h>
#define N 100000000

char a[N];

int main()
{
    unsigned long i, j;

    for(i=2; i<N; i++)
        a[i] = 1;
    for(i=2; i<N; i++)
        if(a[i])
            for(j=i; i*j<N; j++)
                a[i*j] = 0;
    for(i=2; i<N; i++)
        if(a[i])
            printf("%10ld", i);
    return 0;
}
