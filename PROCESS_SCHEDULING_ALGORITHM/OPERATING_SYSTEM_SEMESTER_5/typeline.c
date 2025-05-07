#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void typeline(char *, char *);

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
				if(strcmp(t1, "typeline") == 0)
					typeline(t2, t3);
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
				printf("\nCommand Not Found");
				exit(0);
		}
	}
	
	return 0;
}

void typeline(char *s, char *fn)
{
	int n;
	char ch;
	int i = 0;
	int handle;
	int cnt = 0;
	
	if((handle = open(fn, O_RDONLY)) == -1)
	{
		printf("\nfile not found");
		return;
	}
	
	if(strcmp(s, "a") == 0)
	{
		while(read(handle, &ch, 1) != 0)
		{
			printf("%c", ch);
		}
		return;
	}
	
	n = atoi(s);
	
	if(n > 0)
	{
		while(read(handle, &ch, 1) != 0)
		{
			if('\n' == ch)
				i++;
				
			if(n == i)
				break;
			
			printf("%c", ch);
		}
	}
	
	if(n < 0)
	{
		while(read(handle, &ch, 1) != 0)
			if('\n' == ch)
				cnt++;
		
		lseek(handle, 0, SEEK_SET);
		
		while(read(handle, &ch, 1) != 0)
		{
			if('\n' == ch)
				i++;
			
			if(i == (cnt + n - 1))
				break;
		}
		
		while(read(handle, &ch, 1) != 0)
			printf("%c", ch);
	}
}

