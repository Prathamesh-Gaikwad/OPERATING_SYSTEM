#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

typedef struct dir
{
	char fname[20];
	int start;
	struct dir *next;
}NODE;

void init();
void delete();
void create();
void show_dir();
void show_bitvector();

int n;
int fb;
NODE *last;
NODE *first;
int bit[MAX];

int main()
{
	int ch;
	
	init();
	
	while(1)
	{
		printf("\n\t1.Show Bit Vector");
		printf("\n\t2.Create New File");
		printf("\n\t3.Show Directory");
		printf("\n\t4.Delete File");
		printf("\n\t5.Exit");
		printf("\n\tEnter Your Choice(1-5) : ");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1 : show_bitvector();
				 break;

			case 2 : create();
				 break;
				 
			case 3 : show_dir();
				 break;
				 
			case 4 : delete();
				 break;
				 
			case 5 : exit(0);
				 break;				 
		}
	}
	
	return 0;
}

void init()
{
	int i;
	int k;
	
	printf("\n\tEnter Total No. Of Disk Block : ");
	scanf("%d", &n);
	
	fb = n;
	for(i = 0; i < 10; i++)
	{
		k = rand()%n;
		
		if(bit[k] != 1)
		{
			bit[k] = 1;
			fb--;
		}
	}
}

void show_bitvector()
{
	int i;
	printf("\n\t");
	for(i = 0; i < n; i++)
		printf("%d", bit[i]);
	printf("\n");
}

void show_dir()
{
	NODE *p;
	int i;
	
	printf("\n\tFile\tChain\n");
	p = first;
	while(p != NULL)
	{
		printf("\t%s\t", p->fname);
		i = p->start;
		
		while(i != -1)
		{
			printf("%d-->", i);
			i = bit[i];
		}
		
		printf("NULL\n");
		p = p->next;
	}
}

void create()
{
	NODE *p;
	char fname[20];
	int i, j, nob;
	
	printf("\n\tEnter File Name : ");
	scanf("%s", fname);
	
	printf("\n\tEnter No. Of Blocks : ");
	scanf("%d", &nob);
	
	if(nob > fb)
	{
		printf("\n\tFailed To Create File %s\n", fname);
		return;
	}
	
	for(i = 0; i < n; i++)
	{
		if(bit[i] == 0)
			break;
	}
	
	p = (NODE*)malloc(sizeof(NODE));
	strcpy(p->fname, fname);
	p->start = i;
	p->next = NULL;
	
	if(first == NULL)
		first = p;
	else
	{
		last->next = p;
		last = p;
		fb = fb - nob;
		j = i + 1;
		nob--;
	}
	
	while(nob > 0)
	{
		if(bit[j] == 0)
		{
			bit[i] = j;
			i = j;
			nob--;
		}
		j++;
	}
	
	bit[i] = -1;
	printf("\n\tFile %s Created Successfully\n", fname);
}

void delete()
{
	char fname[20];
	NODE *p, *q;
	int nob = 0, i, j;
	
	printf("\n\tEnter File Name To Be Deleted : ");
	scanf("%s", fname);
	
	p = q = first;
	while(p != NULL)
	{
		if(strcmp(p->fname, fname) == 0)
			break;
		
		q = p;
		p = p->next;
	}
	
	if(p == NULL)
	{
		printf("\n\tFile %s Not Found\n", fname);
		return;
	}
	
	i = p->start;
	while(i != -1)
	{
		nob++;
		j = i;
		i = bit[i];
		bit[j] = 0;
	}
	
	fb = fb + nob;
	
	if(p == first)
		first = first->next;
	else if(p == last)
	{
		last = q;
		last->next = NULL;
	}
	else
		q->next = p->next;
	
	free(p);
	printf("\n\tFile %s Deleted Successfully\n", fname);
}
