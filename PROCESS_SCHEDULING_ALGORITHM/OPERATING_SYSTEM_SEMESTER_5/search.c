#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

void search(char, char *, char *);

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
				if(!fork())
				{
					execlp(t1, t1, t2, t3, NULL);
					perror(t1);
				}
				
				break;
				
			case 4 :
				if(strcmp(t1, "search") == 0)
					search(t2[0], t3, t4);
				else
				{
					if(!fork())
					{
						execlp(t1, t1, t2, t3, t4, NULL);
						perror(t1);
					}
				}
				
				break;
				
			default :
				printf("\nCommand Not Found");
				exit(0);
		}
	}
	
	return 0;
}

void search(char c, char *s, char *fn)
{
	char ch;
	int i = 1;
	int j = 0;
	int handle;
	int cnt = 0;
	char buff[80];
	char *p = NULL;
	
	if((handle  = open(fn, O_RDONLY)) == -1)
	{
		printf("\nFile Not Found");
		return;
	}
	
	switch(c)
	{
		case 'f' :
				while((read(handle, &ch, 1)) != 0)
				{
					if(ch == '\n')
					{
						buff[j] = '\0';
						j = 0;
						
						if(strstr(buff, s) != NULL)
						{
							printf("\n%d : %s", i, buff);
							break;
						}	
						i++;
					}
					else
						buff[j++] = ch;
				}
				
				break;
		
		case 'c' :
				while((read(handle, &ch, 1)) != 0)
				{
					if(ch == '\n')
					{
						buff[j] = '\0';
						j = 0;
						
						if(strstr(buff, s) != NULL)
						{
							p = buff;
							while((p = strstr(p, s)) != NULL)
							{
								cnt++;
								p++;
							}
						}							
					}
					else
						buff[j++] = ch;
				}
				
				printf("\nTotal No. Of Occurrences : %d", cnt);
				break;
		
		case 'a' :
				while((read(handle, &ch, 1)) != 0)
				{
					if(ch == '\n')
					{
						buff[j] = '\0';
						j = 0;
						
						if(strstr(buff, s) != NULL)
							printf("\n%d : %s", i, buff);
							
						i++;
					}
					else
						buff[j++] = ch;
				}
				
				break;
		
		default :
			printf("\nCommand Not Found");
			exit(0);
	}
}

