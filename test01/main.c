/*����һ����������a������Ϊlen����һ����X��
 *�ж�A���������Ƿ���������������ǵĺ�ΪX��
 *bool judge(int *a, int len, int x)�����ڷ���true�������ڷ���false
 */
#include <stdio.h>
#include <stdlib.h>

int judge(long *a, long len, long x)
{
    long mid = x / 2;
    long i, j, t=0, p;
    for(i=0; i<len; i++)
    {
        if(a[i]>=mid)
        {
            t = i;
            break;
        }
    }
    if(t==0||t==len)
    {
        return 0;
    }

    p = len;
    for(i=0; i<t; i++)
    {
        for(j=t; j<p; j++)
        {
            if(a[i]+a[j]<x)
            {
                continue;
            }
            else if(a[i]+a[j]>x)
            {
                p = j;
                break;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int judge1(long *a, long len, long x)
{
    long left=0, right=len-1;
    while(left<right)
    {
        if(a[left]+a[right]<x)
        {
            left++;
            continue;
        }
        else if(a[left]+a[right]>x)
        {
            right--;
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

long g[1000000];

int main()
{
    long i;
    for(i=0; i<1000000; i++)
        g[i] = i + 1;
    printf("%d\n", judge(g, 1000000, 2000000));
    return 0;
}
