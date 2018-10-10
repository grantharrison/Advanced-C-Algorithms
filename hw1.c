//Grant Harrison
//
//CS3050
//
//Machine Problem 1
//
//
#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct List
{
    struct Node *head;
};

struct Graph
{
    int V;
    struct List *array;
};

FILE *fp;

struct Node *CreateNode(int);
void addEdge(struct Graph*, int, int);
void printGraph(struct Graph*);
struct Graph *CreateGraph(int );

int main(void)
{
    struct Graph *graph;
    int src, des;
    int w = 0;
    fp = fopen("practice.txt","r");
    while(fscanf(fp,"%d %d", &src, &des)!=EOF)
    {
	if(src == des)
	{
	    w = src;
	}
	if(src < des)
	{
	    w = des;
	}
	if(src > des)
	{
	    w = src;
	}
    }
    printf("%d\n",w);
    fclose(fp);
    graph = CreateGraph(9);
    fp = fopen("practice.txt","r");
    while(fscanf(fp,"%d %d", &src, &des)!=EOF)
    {
	addEdge(graph, src, des);
    }
    printGraph(graph);
    fclose(fp);
    return 0;
}

struct Node *CreateNode(int x)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = x;
    p->next = NULL;
    return p;
}

struct Graph *CreateGraph(int V)
{
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));   
    graph->V=V;
    graph->array=(struct List*)malloc(sizeof(struct List)*V);
    int i;
    for(i=0;i<V;i++)
     {
        graph->array[i].head=NULL;
     }
    return graph;
}

void addEdge(struct Graph* graph,int src,int des)
{
     struct Node *temp1, *temp2;    
     temp1 = CreateNode(des);
     temp1->next=graph->array[src].head;
     graph->array[src].head=temp1;
     
     //For undirected graphs

     temp2 = CreateNode(src);
     temp2->next=graph->array[des].head;
     graph->array[des].head=temp2;
}

void printGraph(struct Graph* graph)
{
    int v, j;
    j=1;

    for (v = 1; v < graph->V; v++)
    {
        struct Node* trav = graph->array[v].head;

        printf("\n Adjacency list of vertex %d: ", j);
        
        while (trav!=NULL)
        {
            printf("-> %d", trav->data);
            
            trav = trav->next;
        }
	j++;
        printf("\n");
    }
}
	









