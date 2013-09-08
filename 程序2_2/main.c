#include <stdio.h>

int search(int a[], int v, int l, int r)
{
    while(r>=l)
    {
        int m = (l+r)/2;
        if(v==a[m]) return m;
        if(v<a[m])
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

int main()
{
    int a[] = {1, 3, 4, 6, 7, 8, 9, 12, 34, 96, 100};
    printf("%d\n", search(a, 7, 0, 10));
    return 0;
}
