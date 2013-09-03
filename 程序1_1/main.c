#include <stdio.h>
#define N 10
//合并-查找算法，此为快速查找慢速合并，即查找速度相对较快，但合并速度较慢。
//合并操作就是把元素根据条件合并到一个集合中，具体实现是用树结构具有相同根的元素就是在同一集合中。
//查找操作是保证查找同一集合中的元素时返回相同的结果，即树的根。
int main()
{
    int i, p, q, t, id[N];
    for(i=0; i<N; i++)
    {
        id[i] = i;
    }
    while(scanf("%d %d", &p, &q)==2)//书中原代码scanf("%d %d\n", &p, &q)==2，不能达到预期
    {
        if(id[p]==id[q])
            continue;
        for(t=id[p],i=0; i<N; i++)//此为合并操作
        {
            if(id[i]==t)
            {
                id[i]=id[q];
            }
        }
        for(i=0; i<N; i++)
        {
            printf("%d ", id[i]);
        }
        printf("\n");
    }
    return 0;
}
