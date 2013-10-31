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

void lru(int *p, int len, int num)
{
    int i, f=len-1;
    for(i=0; i<len; i++)
    {
        if(p[i]==num)
        {
            f = i;
            break;
        }
    }
    for(i=f; i>0; i--)
    {
        p[i] = p[i-1];
    }
    p[0] = num;
}

void printP(int p[], int len)
{
    int i;
    for(i=0; i<len; i++)
    {
        printf("%d\t", p[i]);
    }
    printf("\n");
}

int main()
{
    int table[4][9];
    PageTable pt[] =
    {
        {0, 1,  5, 0, 11}, {1, 1,  8, 0, 12},
        {2, 1,  9, 0, 13}, {3, 1,  1, 0, 21},
        {4, 0, -1, 0, 22}, {5, 0, -1, 0, 23},
        {6, 0, -1, 0, 121},
    };
    OptionTable ot[] =
    {
        {"+", 0, 70}, {"+", 1, 50},
        {"*", 2, 15}, {"s", 3, 21},
        {"r", 0, 56}, {"-", 6, 40},
        {"y", 4, 53}, {"+", 5, 23},
        {"s", 1, 37}, {"r", 2, 78},
        {"+", 4,  1}, {"s", 6, 84},
    };

    int P[4], i, L, j;
    for(i=0; i<4; i++)
    {
        P[i] = 3 - i;
        table[i][0] = 3 - i;
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
            lru(P, 4, L);
            printf("Absolute address is %d.\n\n", pt[L].blockNum*128+ot[i].unitNum);
            if(i>3)
            {
                int ii;
                for(ii=0; ii<4; ii++)
                {
                    table[ii][i-3] = P[ii];
                }
            }
        }
        else
        {
            printf("***warning*** %d page is lost.\n", L);
            j = P[3];
            pt[j].flag = 0;
            if(pt[j].changed==1)
            {
                printf("out %d \n", j);
            }
            else
            {
                printf("%d page is not changed.\n", j);
            }
            lru(P, 4, L);
            pt[L].flag = 1;
            pt[L].blockNum = pt[j].blockNum;
            printf("in %d \n\n", L);
            i--;
        }
    }

    printf("\n---------------------------PageTable-----------------------------\n");
    for(i=0; i<4; i++)
    {
        for(j=0; j<9; j++)
        {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
    return 0;
}
