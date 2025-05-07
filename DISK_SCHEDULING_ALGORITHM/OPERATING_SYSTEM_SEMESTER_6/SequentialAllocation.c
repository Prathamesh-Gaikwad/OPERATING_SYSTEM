#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200

typedef struct dir
{
	char fname[20];
	int start, length;
	struct dir *next;
}NODE;

void init();
void delete();
void create();
void show_dir();
void show_bitvector();

NODE *first, *last;
int bit[MAX];
int n;

int main()
{
	int ch;
	
	init();
	
	while(1)
	{
		printf("\n1.Show Bit Vector.");
		printf("\n2.Create New File.");
		printf("\n3.Show Directory.");
		printf("\n4.Delete File.");
		printf("\n5.Exit.");
		
		printf("\nEnter Your Choice [1-5]: ");
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
				 
			default : printf("\nInvalid Choice");
		}
	}
	
	return 0;
}

void init()
{
	int i;
	int k;
	
	printf("\nEnter Total No. Of Disk Blocks : ");
	scanf("%d", &n);
	
	for(i = 0; i < 10; i++)
	{
		k = rand()%n;
		bit[k] = 1;
	}
}

void show_bitvector()
{
	int i;
	
	for(i = 0; i < n; i++)
		printf("%d", bit[i]);
	
	printf("\n");
}

void show_dir()
{
	NODE *p;
	
	printf("\nFile\t Start\t Length\n");
	
	p = first;
	
	while(p != NULL)
	{
		printf("%s\t%d\t%d\n", p->fname, p->start, p->length);
		p = p->next;
	}
}

void create()
{
	NODE *p;
	char fname[20];
	int nob, i = 0, j = 0, start;
	
	printf("\nEnter File Name : ");
	scanf("%s", fname);
	
	printf("\nEnter No. Of Blocks");
	scanf("%d", &nob);
	
	while(1)
	{
		while(i < n)
		{
			if(bit[i] == 0)
				break;
			i++;
		}
		
		if(i < n)
		{
			start = i;
			j = 1;
			
			while(j < nob && i < n && bit[i] == 0)
			{
				i++;
				j++;
			}
			
			if(j == nob)
			{
				p = (NODE *)malloc(sizeof(NODE));
				
				strcpy(p->fname, fname);
				p->length = nob;
				p->next = NULL;
				
				if(first == NULL)
					first = p;
				else
					last->next = p;
					
				last = p;
				
				for(j = 0; j < nob; j++)
					bit[j + start] = 1;
					
				printf("\nFile %s Created Successfully", fname);
				
				return;
			}
		}
		else
		{
			printf("\nFail to create file %s", fname);
			
			return;
		}
	}
}

void delete()
{
	int i;
	NODE *p, *q;
	char fname[20];
	
	printf("\nEnter File To Be Deleted : ");
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
		printf("\nFile %s Not Found", fname);
		
		return;
	}
	
	for(i = 0; i < p->length; i++)
		bit[p->start + i] = 0;
	
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
	
	printf("\nFile %s deleted Successfully", fname);
}
