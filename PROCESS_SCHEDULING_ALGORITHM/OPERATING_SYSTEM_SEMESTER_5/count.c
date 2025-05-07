#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void count(char, char *);

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
				if(strcmp(t1, "count") == 0)
					count(t2[0], t3);
				else
				{
					if(!fork())
					{
						execlp(t1, t1, t2, t3, NULL);
						perror(t1);
					}
				}
				
				break;
				
			default :
				printf("\n\ncommand not found");
				exit(0);
		}
	}
	
	return 0;
}

void count(char c, char *fn)
{
	char ch;
	int lc = 0;
	int wc = 0;
	int cc = 0;
	int handle = 0;
	
	if((handle = open(fn, O_RDONLY)) == -1)
	{
		printf("\nFile Not Found");
		return;
	}
	
	switch(c)
	{
		case 'c' :
			while(read(handle, &ch, 1) != 0)
				cc++;
			
			printf("\nTotal No. Of Character Count : %d", cc);
			break;
			
		case 'w' :
			while(read(handle, &ch, 1) != 0)
			{
				if(ch == ' ')
					wc++;
			}
			
			printf("\nTotal No. Of Character Count : %d", wc);
			break;
			
		case 'l' :
			while(read(handle, &ch, 1) != 0)
			{
				if('\n' == ch)
					lc++;
			}
			
			printf("\nTotal No. Of Lines : %d", lc);
			break;
			
		default :
			printf("command not found");
			return;
	}
}

