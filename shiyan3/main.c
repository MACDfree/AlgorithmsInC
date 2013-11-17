#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define bool char

typedef struct IOtable
{
    char pName[20];
    int cylinderNum;    //0-199
    int trackNum;       //0-19
    int blockNum;       //0-7
    struct IOtable *next;
    struct IOtable *prev;
} IOtable;

int g_dir=1;    //1:in,-1:out
int g_current_cylinder=0, g_current_track=0, g_current_block=0;
IOtable *head=NULL,*endless=NULL;

bool get_rand()
{
    return rand() < RAND_MAX/2;
}

void init()
{
    IOtable *p, *t;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p1");
    p->cylinderNum = 100;
    p->trackNum = 0;
    p->blockNum = 0;
    head = p;
    head->prev = NULL;
    t = p;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p2");
    p->cylinderNum = 150;
    p->trackNum = 0;
    p->blockNum = 1;
    t->next = p;
    p->prev = t;
    t=p;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p3");
    p->cylinderNum = 60;
    p->trackNum = 1;
    p->blockNum = 5;
    t->next = p;
    p->prev = t;
    t=p;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p4");
    p->cylinderNum = 60;
    p->trackNum = 7;
    p->blockNum = 2;
    t->next = p;
    p->prev = t;
    t=p;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p5");
    p->cylinderNum = 20;
    p->trackNum = 6;
    p->blockNum = 2;
    t->next = p;
    p->prev = t;
    t=p;

    p = (IOtable *)malloc(sizeof(IOtable));
    strcpy(p->pName, "p6");
    p->cylinderNum = 14;
    p->trackNum = 3;
    p->blockNum = 5;
    t->next = p;
    p->next = NULL;
    p->prev = t;
    endless = p;
}

void request()
{
    char t;
    IOtable *p;
    while(1)
    {
        printf("Is there request?(y or N) ");
        scanf("%c%*c", &t);
        if(t=='y')
        {
            p = (IOtable *)malloc(sizeof(IOtable));
            printf("Input process name: ");
            scanf("%s%*c", p->pName);
            printf("Input address(cylinderNum trackNum blockNum): ");
            scanf("%d %d %d%*c", &(p->cylinderNum), &(p->trackNum), &(p->blockNum));
            if(endless)
            {
                endless->next = p;
                p->prev = endless;
                endless = p;
                endless->next = NULL;
            }
            else
            {
                head = p;
                endless = p;
                p->next = NULL;
                p->prev = NULL;
            }
            return;
        }
        else if(t=='N')
        {
            return;
        }
        else
        {
            printf("Input error!\n");
            continue;
        }
    }

}

bool close()
{
    int t, s, minBlock=8,minCylinder=200;
    IOtable *p=head, *result=NULL;
    while(p)
    {
        t = (p->cylinderNum - g_current_cylinder) * g_dir;
        if(t>=0 && t<=minCylinder)
        {
            s=abs(p->blockNum-g_current_block);
            if(t<minCylinder)
            {
                minCylinder = t;
                minBlock = s;
            }
            if(s<=minBlock)
            {
                minBlock = s;
                result = p;
            }
        }
        p = p->next;
    }
    if(result)
    {
        g_current_cylinder = result->cylinderNum;
        g_current_track = result->trackNum;
        g_current_block = result->blockNum;
        printf("run: %s \tcylinder: %d\ttrack: %d\tblock: %d\ndirection: %s\n\n",
                result->pName, result->cylinderNum, result->trackNum, result->blockNum, g_dir>0?"in":"out");
        if(result->prev==NULL && result->next==NULL)
        {
            head = NULL;
            endless = NULL;
            free(result);
            return 1;
        }
        else if(result->prev==NULL)
        {
            result->next->prev = result->prev;
            head = result->next;
        }
        else if(result->next==NULL)
        {
            result->prev->next = result->next;
            endless = result->prev;
        }
        else
        {
            result->next->prev = result->prev;
            result->prev->next = result->next;
        }
        free(result);
        return 1;
    }
    else
    {
        return 0;
    }
}

void csan()
{
    if(close()==0)
    {
        g_dir = -g_dir;
    }
}

int main()
{
    init();
    while(head!=NULL)
    {
        if(get_rand())
        {
            request();
        }
        else
        {
            csan();
        }
    }
    return 0;
}
