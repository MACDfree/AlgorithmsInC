#include <stdio.h>
#define N 10

int main()
{
    int i, j, p, q, id[N], sz[N];
    for(i=0; i<N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
    while(scanf("%d %d", &p, &q)==2)
    {
        for(i=p; i!=id[i]; i=id[i]);
        for(j=q; j!=id[j]; j=id[j]);
        if(i==j)
            continue;
        id[i] = j;
        //判断节点的数目，总把小树连接到大树上。
        if(sz[i]<sz[j])
        {
            id[i] = j;
            sz[j] += sz[i];
        }
        else
        {
            id[j] = i;
            sz[i] += sz[j];
        }
        for(i=0; i<N; i++)
        {
            printf("%d ", id[i]);
        }
        printf("\n");
        for(i=0; i<N; i++)
        {
            printf("%d ", sz[i]);
        }
        printf("\n");
    }
    return 0;
}
