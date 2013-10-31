#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _proc
{
    char name[32];			//进程名
    int run_time;			//运行时间
    int req_time;			//需要时间
    int pri;				//优先级
    enum {ready,end} state;	//进程状态
    struct _proc *prior;	//指向上一个块指针
    struct _proc *next;		//指向下一个块的指针
} PROC;

int time=0;
PROC *g_head=NULL,*g_curr=NULL;

void Init()
{
    //头结点不储存数据
    PROC *p;
    g_head = (PROC*)malloc(sizeof(PROC));
    g_head->next = NULL;
    g_head->prior = NULL;

    //第一个进程初始化
    p = (PROC*)malloc(sizeof(PROC));
    strcpy(p->name, "P1");
    p->run_time = 0;
    p->req_time = 2;
    p->pri = 1;
    p->state = ready;
    p->next = NULL;
    p->prior = g_head;		//上一个指针指向头结点
    g_head->next = p;		//将他挂在链表上
    g_curr=g_head->next;	//当前指针指向第一个节点

    //第二个进程初始化
    p = (PROC*)malloc(sizeof(PROC));
    strcpy(p->name, "P2");
    p->run_time = 0;
    p->req_time = 3;
    p->pri = 5;
    p->state = ready;
    if(p->pri>g_curr->pri)
    {
        p->prior=g_curr->prior;
        g_curr->prior->next=p;
        p->next=g_curr;
        g_curr->prior=p;
        g_curr=g_head->next;
    }
    else
    {
        g_curr->next=p;
        p->prior=g_curr;
        p->next=NULL;
        g_curr=g_head->next;
    }

    p = (PROC*)malloc(sizeof(PROC));
    strcpy(p->name, "P3");
    p->run_time = 0;
    p->req_time = 1;
    p->pri = 3;
    p->state = ready;
    if(p->pri>g_curr->pri)
    {
        p->prior=g_curr->prior;
        g_curr->prior->next=p;
        p->next=g_curr;
        g_curr->prior=p;
        g_curr=g_head->next;
    }
    else
    {
        g_curr=g_curr->next;
        if(p->pri>g_curr->pri)
        {
            p->prior=g_curr->prior;
            g_curr->prior->next=p;
            p->next=g_curr;
            g_curr->prior=p;
            g_curr=g_head->next;
        }
        else
        {
            g_curr->next=p;
            p->prior=g_curr;
            p->next=NULL;
            g_curr=g_head->next;
        }
    }


    p = (PROC*)malloc(sizeof(PROC));
    strcpy(p->name, "P4");
    p->run_time = 0;
    p->req_time = 2;
    p->pri = 4;
    p->state = ready;
    if(p->pri>g_curr->pri)
    {
        p->prior=g_curr->prior;
        g_curr->prior->next=p;
        p->next=g_curr;
        g_curr->prior=p;
        g_curr=g_head->next;
    }
    else
    {
        g_curr=g_curr->next;
        if(p->pri>g_curr->pri)
        {
            p->prior=g_curr->prior;
            g_curr->prior->next=p;
            p->next=g_curr;
            g_curr->prior=p;
            g_curr=g_head->next;
        }
        else
        {
            g_curr=g_curr->next;
            if(p->pri>g_curr->pri)
            {
                p->prior=g_curr->prior;
                g_curr->prior->next=p;
                p->next=g_curr;
                g_curr->prior=p;
                g_curr=g_head->next;
            }
            else
            {
                g_curr->next=p;
                p->prior=g_curr;
                p->next=NULL;
                g_curr=g_head->next;
            }
        }
    }

    p = (PROC*)malloc(sizeof(PROC));
    strcpy(p->name, "P5");
    p->run_time = 0;
    p->req_time = 4;
    p->pri = 2;
    p->state = ready;
    if(p->pri>g_curr->pri)
    {
        p->prior=g_curr->prior;
        g_curr->prior->next=p;
        p->next=g_curr;
        g_curr->prior=p;
        g_curr=g_head->next;
    }
    else
    {
        g_curr=g_curr->next;
        if(p->pri>g_curr->pri)
        {
            p->prior=g_curr->prior;
            g_curr->prior->next=p;
            p->next=g_curr;
            g_curr->prior=p;
            g_curr=g_head->next;
        }
        else
        {
            g_curr=g_curr->next;
            if(p->pri>g_curr->pri)
            {
                p->prior=g_curr->prior;
                g_curr->prior->next=p;
                p->next=g_curr;
                g_curr->prior=p;
                g_curr=g_head->next;
            }
            else
            {
                g_curr=g_curr->next;
                if(p->pri>g_curr->pri)
                {
                    p->prior=g_curr->prior;
                    g_curr->prior->next=p;
                    p->next=g_curr;
                    g_curr->prior=p;
                    g_curr=g_head->next;
                }
                else
                {
                    g_curr->next=p;
                    p->prior=g_curr;
                    p->next=NULL;
                    g_curr=g_head->next;
                }
                }
            }
        }
    }
    void PrintInfo()
    {
        PROC *t = g_head->next;
        printf("Time : %d\t Process Information\n", time);
        printf("name  run_time  req_time  pri  state\n");
        printf("------------------------------------\n");
        while(t!=NULL)
        {
            printf("%4s  %8d  %8d  %3d  %5s\n", t->name, t->run_time, t->req_time,t->pri, t->state == ready? "ready" : "end");
            t = t->next;
        }
        printf("Current process is %s\n", g_curr->name);
        printf("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");
    }
    void run()
    {
        PROC *p;
        g_curr = g_head->next;

        PrintInfo();

        while(g_curr->next!=NULL)
        {

            if(g_curr->pri>=g_curr->next->pri)
            {
                time++;
                g_curr->run_time++;
                g_curr->req_time--;
                g_curr->pri--;
                if(g_curr->req_time==0)
                {
                    g_curr->state = end;
                    PrintInfo();

                    g_head->next = g_curr->next;
                    g_curr->next->prior=g_head;
                    free(g_curr);
                    g_curr = g_head->next;
                }
                else
                {
                    PrintInfo();
                    p=g_curr->next;

                    if(p->next!=NULL)
                    {
                        while(g_curr->pri<p->pri)
                        {
                            p=g_curr->next;
                            g_curr->next=p->next;
                            p->next->prior=g_curr;
                            g_curr->prior->next=p;
                            p->prior=g_curr->prior;
                            g_curr->prior=p;
                            p->next=g_curr;
                        }
                    }
                    else
                    {
                        if(g_curr->pri<p->pri)
                        {
                            g_curr->next=NULL;
                            g_curr->prior->next=p;
                            p->prior=g_curr->prior;
                            g_curr->prior=p;
                            p->next=g_curr;
                        }
                    }
                }
                g_curr = g_head->next;

            }
        }

        PrintInfo();

        while(g_curr!=g_head)
        {
            time++;
            g_curr->run_time++;
            g_curr->req_time--;
            g_curr->pri--;
            if(g_curr->req_time==0)
            {
                g_curr->state = end;
                PrintInfo();
                g_head->next = g_curr->next;

                free(g_curr);
                g_curr=g_head;
            }
            else PrintInfo();
        }
    }

    int main(int argc, char* argv[])
    {
        Init();
        run();
        free(g_head);
        return 0;
    }
