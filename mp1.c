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
void MergeSort(struct Node**);
struct Node* SortedMerge(struct Node*, struct Node*);
void Mid(struct Node*, struct Node**, struct Node**);

int main(void)
{
    struct adjList *list;
    int s, d, i, q;

    printf("\nPlease enter the largest number in the edge list\n");
    scanf("%d", &q);
    q++;

    list = CreateAdjList(q);

    fp = fopen("practice.txt", "r");
    while (fscanf(fp, "%d %d", &s, &d) != EOF)
    {
	CreateAdj(list, s, d);
    }

    for (i=0; i < q; i++)
    {
	MergeSort(&(list->array[i].next));
    }

    printAdj(list);

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

void MergeSort(struct Node** q) 
{ 
    struct Node* p = *q; 
    struct Node* a; 
    struct Node* b; 
    if ((p == NULL) || (p->next == NULL)) 
    { 
	return; 
    } 
    Mid(p, &a, &b);  
    MergeSort(&a); 
    MergeSort(&b); 

    *q = SortedMerge(a, b);
    
}

struct Node* SortedMerge(struct Node* a, struct Node* b) 
{ 
    struct Node* r = NULL; 
    if (a == NULL)
    {
	return(b);
    }
    else if (b==NULL) 
    {
	return(a);
    }
    if (a->data <= b->data) 
    { 
	r = a; 
	r->next = SortedMerge(a->next, b); 
    } 
    else
    { 
	r = b; 
	r->next = SortedMerge(a, b->next); 
    } 
    return(r); 
} 

void Mid(struct Node* s, struct Node** g, struct Node** b) 
{ 
    struct Node* z; 
    struct Node* x; 
    x = s; 
    z = s->next; 
  
    while (z != NULL) 
    { 
	z = z->next; 
	if (z != NULL) 
	{ 
	    x = x->next; 
	    z = z->next; 
	} 
    } 
    *g = s; 
    *b = x->next; 
    x->next = NULL; 
} 
