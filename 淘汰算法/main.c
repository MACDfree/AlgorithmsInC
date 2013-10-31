#include <stdio.h>

//FIFO
int fifo_io(int *a, int N, int p)
{
    int i=0, j, result;
    while(a[i++]!=0||a[i++]!=p);
    if(i==N)
    {
        result = a[0];
        for(j=1;j<N;j++)
        {
            a[j-1] = a[j];
        }
        a[N-1] = p;
        return result;
    }
    else
    {
        a[i-1] = p;
        return 0;
    }
}
//FIFO end

//LRU
int lru_io(int *a, int N, int p)
{
    int i=0;
    while(a[i]!=0)
    {

    }
}
//LRU end

int main()
{
    printf("Hello world!\n");
    return 0;
}
