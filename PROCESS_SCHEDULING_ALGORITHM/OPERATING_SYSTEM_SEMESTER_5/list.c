#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

void list(char, char *);

int main(void)
{
	int n;
	char t1[20];
	char t2[20];
	char t3[20];
	char t4[20];	
	char command[80];
	
	system("clear");
	while(1)
	{
		printf("\n\n[myshell$] : ");
		fflush(stdin);
		fgets(command, 80, stdin);
		n = sscanf(command, "%s%s%s%s", t1, t2, t3, t4);
		
		switch(n)
		{
			case 1 :
				if(!fork())
				{
					execlp(t1, t1, NULL);
					perror(t1);
				}
				break;
				
			case 2 :
				if(!fork())
				{
					execlp(t1, t1, t2, NULL);
					perror(t1);
				}
				break;
				
			case 3 :
				if(strcmp(t1, "list") == 0)
					list(t2[0], t3);
				else
				{
					if(!fork())
					{
						execlp(t1, t2, t3, NULL);
						perror(t1);
					}
					break;					
				}
				break;
				
			case 4 :
				if(!fork())
				{
					execlp(t1, t2, t3, t4, NULL);
					perror(t1);
				}
				break;
			
			default :
				printf("\nInvalid Command!!\n");
				exit(0);
		}
	}
	
	return 0;
}

void list(char c, char *dn)
{
	int cnt = 0;
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	
	if((dir = opendir(dn)) == NULL)
	{
		printf("UNABLE TO OPEN DIRECTORY");
		return;
	}
	
	switch(c)
	{
		case 'f' :
			while((entry = readdir(dir)) != NULL)
			{
				printf("\nFile Name :- %s", entry->d_name);
			}
			break;
			
		case 'n' :
			while((entry = readdir(dir)) != NULL)
				cnt++;
			
			printf("\nTotal No. Of Directory Items :- %d", cnt);
			break;
			
		case 'i' :
			while((entry = readdir(dir)) != NULL)
			{
				printf("\nFile Name :- %s\t File INode Number :- %ld", entry->d_name, entry->d_ino);
			}
			break;
		
		default :
			printf(" %c Command Not Found", c);
	}
}

