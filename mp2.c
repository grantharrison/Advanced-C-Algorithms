/* Grant Harrison
 * 
 * Machine Problem 2
 *
 * CS 3050 
 *
 * This program runs in linear time, the majority of the functions are from
 * my machine problem 1. My DFS function runs in linear time because it iterates 
 * through each vertex of that level of the adj (i.e. adj(2) - 1, 3, 5) which is 
 * dependent on the number of vertices and edges between them giving you O(V + E) time.
 * Also I created a funtion(s) that iterated through an array so you can see if it has been
 * discovered yet or not ( 0 or 1) if it is zero it sends it to my DFS function. Each 
 * function in this program runs in no greater than linear time so this gives you an overall run
 * time of O(|v|+|E|) which is linear.
 */

#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct Node
{
	int visit;
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
void CreateAdjTranspose(struct adjList*, int, int);
void DFS(int, struct adjList*, int*);
void DFS_Transposed(int*, struct adjList*);
void DFS_Untransposed(int*, struct adjList*);

int main(void)
{
    struct adjList *list, *listT;
    int s, d, q = 0;

    fp = fopen("mp2.txt", "r");
    while (fscanf(fp, "%d %d", &s, &d) != EOF)
    {
		if(q < s)
		{
			q = s;
		}
		if(q < d)
		{
			q = d;
		}
    }
    q++;

    fclose(fp);

    list = CreateAdjList(q);
	listT = CreateAdjList(q);

    fp = fopen("mp2.txt", "r");
    while (fscanf(fp, "%d %d", &s, &d) != EOF)
    {
		CreateAdj(list, s, d);
		CreateAdjTranspose(listT, s, d);
    }

	int visited[MAX], visited2[MAX];

	for (int t = 0; t <= q; t++)
	{
		visited[t] = 0;
		visited2[t] = 0;
	}

	DFS_Untransposed(visited, list);
	DFS_Transposed(visited2, listT);
	 
	freeList(list);
	freeList(listT);

    fclose(fp);

    return 0;
}

struct Node *CreateNode(int x)
{
    struct Node *q = (struct Node*)malloc(sizeof(struct Node));
	q->visit = 0;
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
	p->array[i].visit = 0;
	p->array[i].next = NULL;
    }

    return p;
}

void CreateAdj(struct adjList *list, int s, int d)
{
    struct Node *t1;

    t1 = CreateNode(d);
    t1->next = list->array[s].next;
    list->array[s].next = t1;
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
	    printf(" -> %d visted %d", q->data, q->visit);
	    q = q->next;
	}
	j++;
	printf("\n");
    }
} 

void freeList(struct adjList *list)
{
    if (list == NULL)
    {
        printf("Nothing to free.\n");
        return;
    }

    for (int i=0; i < (list->v); i++)
    {
	free(list->array[i].next);
    }
    
    free(list);

}

void CreateAdjTranspose(struct adjList *list, int s, int d)
{
	struct Node *t2;

	t2 = CreateNode(s);
    t2->next = list->array[d].next;
    list->array[d].next = t2;
}

void DFS(int i, struct adjList *list, int visited[])
{
    struct Node *p;

    //printf("%d\n",i);
    p=list->array[i].next;
    visited[i]=1;
    while(p!=NULL)
    {
       i = p->data;
       if(visited[i] == 0)
            DFS(i, list, visited);
        p=p->next;
    }
}

void DFS_Untransposed(int visited[], struct adjList *list)
{
	int q = list->v;
	for (int w = 0; w < q; w++)
    {
         if(visited[w] == 0)
         {
             DFS(w, list, visited);
         }
    }
}

void DFS_Transposed(int visited2[], struct adjList *listT)
{
	int q = listT->v;
	int r = 0;
	printf("SCC's are: ");
	for (int z = 0; z < q; z++)
    {
		if(visited2[z] == 0)
        {
            printf("%d ", r);
            r++;
            DFS(z, listT, visited2);
        }
    }
	printf("\n");
}

