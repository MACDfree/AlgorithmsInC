#include <stdio.h>
#include <stdlib.h>
#define bool char

typedef struct pageTable
{
    int pageNum;
    bool flag;
    int blockNum;
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
    int i, t=0;
    PageTable pt[] = {
        {0, 1,  5, 11}, {1, 1,  8, 12},
        {2, 1,  9, 13}, {3, 1,  1, 21},
        {4, 0, -1, 22}, {5, 0, -1, 23},
        {6, 0, -1, 121},
    };
    OptionTable ot[] = {
        {"+", 0, 70}, {"+", 1, 50},
        {"*", 2, 15}, {"s", 3, 21},
        {"r", 0, 56}, {"-", 6, 40},
        {"y", 4, 53}, {"+", 5, 23},
        {"s", 1, 37}, {"r", 2, 78},
        {"+", 4,  1}, {"s", 6, 84},
    };

    for(i=0; i<12; i++)
    {
        t = ot[i].pageNum;
        printf("Option is %s.\n", ot[i].option);
        if(pt[t].flag==1)
        {
            printf("Absolute address is %d.\n\n", pt[t].blockNum*128+ot[i].unitNum);
        }
        else
        {
            printf("***warning*** %d page is lose.\n\n", t);
        }
    }
    return 0;
}
