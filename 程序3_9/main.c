#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int item;
    struct node *next;
} node;

int main()
{
    int i, N=9, M=5;
    node *t = malloc(sizeof(node));
    node *x = t;
    t->item = 1;
    t->next = t;
    for(i=2; i<=N; i++)
    {
        x = (x->next = malloc(sizeof(node)));
        x->item = i;
        x->next = t;
    }
    while(x!=x->next)
    {
        for(i=1; i<M; i++)
        {
            x = x->next;
        }
        node *temp = x->next;
        x->next = x->next->next;
        free(temp);
        N--;
    }
    printf("%d\n", x->item);
    return 0;
}
