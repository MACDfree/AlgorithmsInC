#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool char

typedef struct pageTable
{
    int pageNum;
    bool flag;
    int blockNum;
    bool changed;
    int diskNum;
} PageTable;

typedef struct optionTable
{
    char *option;
    int pageNum;
    int unitNum;
} OptionTable;

int main()
{
    PageTable pt[] = {
        {0, 1,  5, 0, 11}, {1, 1,  8, 0, 12},
        {2, 1,  9, 0, 13}, {3, 1,  1, 0, 21},
        {4, 0, -1, 0, 22}, {5, 0, -1, 0, 23},
        {6, 0, -1, 0, 121},
    };
    OptionTable ot[] = {
        {"+", 0, 70}, {"+", 1, 50},
        {"*", 2, 15}, {"s", 3, 21},
        {"r", 0, 56}, {"-", 6, 40},
        {"y", 4, 53}, {"+", 5, 23},
        {"s", 1, 37}, {"r", 2, 78},
        {"+", 4,  1}, {"s", 6, 84},
    };

    int P[4], i, k=0, L, j;
    for(i=0; i<4; i++)
    {
        P[i] = i;
    }

    for(i=0; i<12; i++)
    {
        L = ot[i].pageNum;
        printf("Option is %s.\n", ot[i].option);
        if(pt[L].flag==1)
        {
            if(strcmp(ot[i].option, "s")==0)
            {
                pt[L].changed = 1;
            }
            printf("Absolute address is %d.\n\n", pt[L].blockNum*128+ot[i].unitNum);
        }
        else
        {
            printf("***warning*** %d page is lost.\n", L);
            j = P[k];
            pt[j].flag = 0;
            if(pt[j].changed==1)
            {
                printf("out %d \n", j);
            }
            else
            {
                printf("%d page is not changed.\n", j);
            }
            P[k] = L;
            k = (k+1) % 4;
            pt[L].flag = 1;
            pt[L].blockNum = i + 10;
            printf("in %d \n\n", L);
            i--;
        }
    }

    for(i=0; i<4; i++)
    {
        printf("%d\t", P[i]);
    }
    printf("\n");
    for(i=0; i<k; i++)
    {
        printf(" \t");
    }
    printf("^\n");
    return 0;
}
