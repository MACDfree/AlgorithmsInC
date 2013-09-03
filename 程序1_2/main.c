#include <stdio.h>
#define N 10
//这是快速合并，但相对的查找速度会减慢，主要是不能保证一次性查找出结果，可能需要多次的查找。
int main()
{
    int i, j, p, q, t, id[N];
    for(i=0; i<N; i++)
    {
        id[i] = i;
    }
    while(scanf("%d %d", &p, &q)==2)
    {
        for(i=p; i!=id[i]; i=id[i]);
        for(j=q; j!=id[j]; j=id[j]);
        if(i==j)
            continue;
        id[i] = j;
        for(i=0; i<N; i++)
        {
            printf("%d ", id[i]);
        }
        printf("\n");
    }
    return 0;
}
