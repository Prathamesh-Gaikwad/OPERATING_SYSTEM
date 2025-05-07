#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dir
{
	char fname[20];
	int ino, flag;
	struct dir* next;
}DIR;

void print_dir();
void print_free_list();

DIR *first, *last;
int d, fat[200], free_blocks;

int main()
{
	DIR *p;
	int i, j, bno, ch;
	char fname[20];
	
	printf("\n\tEnter No. Of Disk Blocks : ");
	scanf("%d", &d);
	
	for(i = 0; i < d; i++)
		fat[i] = -999;
	
	free_blocks = d;
	
	while(1)
	{
		printf("\n\t****************[MENU]******************");
		printf("\n\t1.Create");
		printf("\n\t2.Delete");
		printf("\n\t3.Print Dir/Free List");
		printf("\n\t4.Exit");
		printf("\n\t****************************************");
		printf("\n\tEnter Your Choice [1-4] : ");
		scanf("%d", &ch);
		printf("\t****************************************\n");

		switch(ch)
		{
			case 1 :
				printf("\n\tEnter File Name : ");
				scanf("%s", fname);
				
				printf("\n\tEnter No. Of Blocks : ");
				scanf("%d", &bno);
				
				if(free_blocks > bno)
				{
					free_blocks -= bno + 1;
					
					p = (DIR *)malloc(sizeof(DIR));
					
					strcpy(p->fname, fname);
					p->flag = 0;
					p->next = NULL;
					
					for(i = 0; i < d; i++)
					{
						if(fat[i] == -999)
							break;
					}
					
					p->ino = i;
					fat[i] = -1;
					i++;
					
					while(bno != 0)
					{
						if(fat[i] == -999)
						{
							fat[i] = p->ino;
							bno--;
						}
						i++;
					}
					
					if(first == NULL)
						first = p;
					else
						last->next = p;
					last = p;
					
					printf("\n\t-->File %s Created Successfully", fname);
				}
				else
					printf("\n\t-->Unable To Create File %s", fname);
				
				break;
			
			case 2 :
				printf("\n\tEnter File To Be Deleted : ");
				scanf("%s", fname);
				
				p = first;
				while(p != NULL)
				{
					if(strcmp(p->fname, fname) == 0 && p->flag == 0)
						break;
					
					p = p->next;
				}
				
				if(p == NULL)
					printf("\n\t-->File %s Not Found", fname);
				else
				{
					p->flag = 1;
					bno = 0;
					
					for(i = 0; i < d; i++)
					{
						if(fat[i] == p->ino)
						{
							fat[i] = -999;
							bno++;
						}
					}
					
					fat[p->ino] = -999;
					free_blocks += bno + 1;
					
					printf("\n\t-->File %s Deleted Successfully", fname);
				}
				
				break;
				
			case 3 :
				print_dir();
				
				print_free_list();
				
				break;
			
			case 4 :
				exit(0);
		}
	}
	
	return 0;
}

void print_dir()
{
	DIR *p;
	int i;

	p = first;

	printf("\n\t--------------------------------------------------");
	printf("\n\tFile\t Inode\t Blocks\t List");
	printf("\n\t--------------------------------------------------");
	while(p != NULL)
	{
		if(p->flag == 0)
		{
			printf("\n\t%s\t %d\t", p->fname, p->ino);
			for(i = 0; i < d; i++)
				if(fat[i] == p->ino)
					printf("%d", i);
			printf("\b \n");
		}
		
		p = p->next;
	}
	
	printf("\n\t--------------------------------------------------\n");
}

void print_free_list()
{
	int i;
	printf("\n\tFree Block List : ");
	for(i = 0; i < d; i++)
		if(fat[i] == -999)
			printf("%d->", i);
	printf("NULL\n");
}
