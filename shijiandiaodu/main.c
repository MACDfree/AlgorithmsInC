#include <stdio.h>
#include <stdlib.h>

typedef struct _proc
{
    char *name;         //进程名
    int run_time;       //运行时间，默认为0
    int req_time;       //要求时间，任意设初值
    enum {R, E} state;  //进程状态
    struct _proc *next; //指向下一个节点的指针
    struct _proc *prior;  //指向上一个节点的指针
} PROC;

int time=0, number=5;
PROC *g_head=NULL, *g_curr=NULL;

void init(void)
{
    PROC *p;
    //第一个进程
    p = (PROC *)malloc(sizeof(PROC));
    p->name = "Q1";
    p->run_time = 0;
    p->req_time = 2;
    p->state = R;
    g_head = p;
    g_curr = p;

    //第二个进程
    p = (PROC *)malloc(sizeof(PROC));
    p->name = "Q2";
    p->run_time = 0;
    p->req_time = 3;
    p->state = R;
    g_curr->next = p;
    p->prior = g_curr;
    g_curr = p;

    //第三个进程
    p = (PROC *)malloc(sizeof(PROC));
    p->name = "Q3";
    p->run_time = 0;
    p->req_time = 1;
    p->state = R;
    g_curr->next = p;
    p->prior = g_curr;
    g_curr = p;

    //第四个进程
    p = (PROC *)malloc(sizeof(PROC));
    p->name = "Q4";
    p->run_time = 0;
    p->req_time = 2;
    p->state = R;
    g_curr->next = p;
    p->prior = g_curr;
    g_curr = p;

    //第五个进程
    p = (PROC *)malloc(sizeof(PROC));
    p->name = "Q5";
    p->run_time = 0;
    p->req_time = 4;
    p->state = R;
    g_curr->next = p;
    p->prior = g_curr;
    p->next = g_head;
    g_curr = p->next;
    g_head->prior = p;
}

void chose_and_run(void)
{
    void print_info(void);
    if((++g_curr->run_time) != g_curr->req_time)
    {
        print_info();
        g_curr = g_curr->next;
        printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n\n");
    }
    else
    {
        PROC *t = g_curr;
        g_curr->state = E;
        print_info();
        g_curr->prior->next = g_curr->next;
        g_curr->next->prior = g_curr->prior;
        g_curr = g_curr->prior;
        free(t);
        number--;
        printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n\n");
    }
}

void print_info(void)
{
    int i;
    PROC *t = g_curr;
    printf("time: %d\t Process Information\n", time);
    printf("name  run_time  req_time  state\n");
    printf("-------------------------------\n");
    for(i=0; i<number; i++)
    {
        printf("%2s  %8d  %8d  %5s\n",
               t->name, t->run_time, t->req_time, t->state==R?"ready":"end");
        t = t->next;
    }
    printf("Current process is %s\n", g_curr->name);
    printf("-------------------------------\n");
}

int main()
{
    init();
    //printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n\n\n");
    while(g_curr->next!=g_curr || g_curr->prior!=g_curr || g_curr->run_time!=g_curr->req_time)
    {
        chose_and_run();
        time++;
    }
    return 0;
}
