#include <stdio.h>
#include <stdlib.h>

typedef struct PCBTable
{
    char *pName;
    int state;      //0-run, 1-ready, 2-wait, 3-finish
    int cause;      //1-s1, 2-s2
    int breakPoint; //0-4
} PCBTable;

typedef struct semaphore
{
    int num;
    PCBTable *point;
} semaphore;

PCBTable *currentP=NULL;
char B[10]={0};
int in=0, out=0;
int PA[5] = {0, 1, 2, 3, 4};
int SA[5] = {0, 1, 2, 3, 4};
int PC = 0;
semaphore *s1=NULL, *s2=NULL;
PCBTable *productor=NULL, *consumer=NULL;

void P(semaphore *s)
{
    s->num--;
    if(s->num<0)
    {
        currentP->state = 2;
        s->point = currentP;
    }
    else
    {
        currentP->state = 1;
    }
}

void V(semaphore *s)
{
    s->num++;
    if(s->num<=0)
    {
        s->point->state = 1;
        s->point = NULL;
    }
    else
    {
        currentP->state = 1;
    }
}

void put(char c)
{
    B[in] = c;
    in = (in+1) % 10;
}

char GET()
{
    char t;
    t = B[out];
    out = (out+1) % 10;
    return t;
}

char produce()
{
    char t;
    printf("input a charector: ");
    scanf("%c%*c", &t);
    return t;
}

void consume(char t)
{
    printf("output a charector: %c\n", t);
}

void ChooseP(int i)
{
    static char t;
    productor->state = 1;
    productor->breakPoint = (i+1) % 5;
    switch(i)
    {
    case 0:
        printf("productor: produce()\n");
        t = produce();break;
    case 1:
        printf("productor: P(s1)\n");
        P(s1);break;
    case 2:
        printf("productor: put(t)\n");
        put(t);break;
    case 3:
        printf("productor: V(s2)\n");
        V(s2);break;
    case 4:
        printf("productor: goto 0\n");
        PC = 0;break;
    }
}

void ChooseC(int i)
{
    static char t;
    consumer->state = 1;
    consumer->breakPoint = (i+1) % 5;
    switch(i)
    {
    case 0:
        printf("productor: P(s2)\n");
        P(s2);break;
    case 1:
        printf("productor: GET()\n");
        t = GET();break;
    case 2:
        printf("productor: V(s1)\n");
        V(s1);break;
    case 3:
        printf("productor: consume(t)\n");
        consume(t);break;
    case 4:
        printf("productor: goto 0\n");
        PC = 0;break;
    }
}

void init()
{
    productor = (PCBTable *)malloc(sizeof(PCBTable));
    productor->pName = "producter";
    productor->breakPoint = 0;
    productor->cause = 0;
    productor->state = 1;
    consumer = (PCBTable *)malloc(sizeof(PCBTable));
    consumer->pName = "consumer";
    consumer->breakPoint = 0;
    consumer->cause = 0;
    consumer->state = 1;
    s1 = (semaphore *)malloc(sizeof(semaphore));
    s1->num = 10;
    s1->point = NULL;
    s2 = (semaphore *)malloc(sizeof(semaphore));
    s2->num = 0;
    s2->point = NULL;
}

int main()
{
    char c;
    init();
    /*
loop:
    printf("choose current process(p:productor,c:consumer): ");
    c = (char)getchar();
    if(c=='p')
    {
        currentP = productor;
    }
    else if(c=='c')
    {
        currentP = consumer;
    }
    else
    {
        goto loop;
    }*/

    while(productor->state!=3||consumer->state!=3)
    {
        if(productor->state==1 && consumer->state==1)
        {
            printf("choose current process(p:productor,c:consumer): ");
            scanf("%c%*c", &c);
            if(c=='p')
            {
                currentP = productor;
                PC = currentP->breakPoint;
                ChooseP(PA[PC]);
            }
            else if(c=='c')
            {
                currentP = consumer;
                PC = currentP->breakPoint;
                ChooseC(SA[PC]);
            }
            else
            {
                continue;
            }
            continue;
        }
        else if(productor->state==1)
        {
            printf("productor is ready only.\n");
            currentP = productor;
            PC = currentP->breakPoint;
            ChooseP(PA[PC]);
            continue;
        }
        else if(consumer->state==1)
        {
            printf("consumer is ready only.\n");
            currentP = consumer;
            PC = currentP->breakPoint;
            ChooseC(SA[PC]);
            continue;
        }
    }
    return 0;
}
