#include <stdio.h>
#include <stdlib.h>

//1*x^2+2*x^1+3

int a[3] = {1, 2, 3};
int x=3;

int fun(int n)
{
    if(n==0)
    {
        return a[0];
    }
    return fun(n-1)*x + a[n];
}

int main()
{
    printf("%d\n", fun(2));
    return 0;
}
