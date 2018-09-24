//Grant Harrison



#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct adjList
{
    int v;
    struct Node *array;
};

FILE *fp;

struct Node *CreateNode(int);
struct adjList *CreateAdjList(int);
void CreateAdj(struct adjList*, int, int);
void printAdj(struct adjList*);
void freeList(struct adjList*);
struct adjList *SortAdjList(struct adjList*);

int main(void)
{
    struct adjList *list;
    int s, d, q;

    printf("\nPlease enter the largest number in the edge list\n");
    scanf("%d", &q);
    q++;

    list = CreateAdjList(q);

    fp = fopen("vertices.txt", "r");
    while (fscanf(fp, "%d %d", &s, &d) != EOF)
    {
	CreateAdj(list, s, d);
    }

    list = SortAdjList(list);

    printAdj(list);
   // freeList(list);

    fclose(fp);

    return 0;
}

struct Node *CreateNode(int x)
{
    struct Node *q = (struct Node*)malloc(sizeof(struct Node));

    q->data = x;
    q->next = NULL;
    return q;
}

struct adjList *CreateAdjList(int z)
{
    int i;
    struct adjList *p = (struct adjList*)malloc(sizeof(struct adjList));

    p->v = z;
    p->array = (struct Node*)malloc(sizeof(struct Node)*z);

    for (i=0; i < z; i++)
    {
	p->array[i].next = NULL;
    }

    return p;
}

void CreateAdj(struct adjList *list, int s, int d)
{
    struct Node *t1, *t2;

    t1 = CreateNode(d);
    t1->next = list->array[s].next;
    list->array[s].next = t1;

    t2 = CreateNode(s);
    t2->next = list->array[d].next;
    list->array[d].next = t2;
}

void printAdj(struct adjList *list)
{
    int i, j;
    j = 0;

    for (i=0; i < (list->v); i++)
    {
	struct Node *q = list->array[i].next;

	printf("\n %d: ", j);

	while (q != NULL)
	{
	    printf(" -> %d", q->data);
	    q = q->next;
	}
	j++;
	printf("\n");
    }
} 

struct adjList *SortAdjList(struct adjList *list)
{
    int u, v;
    struct adjList *q = CreateAdjList(list->v);
    struct Node *p, *z;

    v = list->v;

    for (int i=0; i < (v); v--)
    {
	p = list->array[v].next;
	while (p != NULL)
	{
	    u = p->data;
	    z = CreateNode(v);
            z->next = q->array[u].next;
            q->array[u].next = z;
	    p = p->next;
	}
    }
    
    return q;
}
