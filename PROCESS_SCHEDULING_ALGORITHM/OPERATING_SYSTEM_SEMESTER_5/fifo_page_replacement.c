#include <stdio.h>
#define MAX 20

void disp(void);
void fifo(void);
void accept(void);
int search(int pno);

int n;
int m;
int sp;
int fault;
int frames[MAX];
int mem[MAX][MAX];
int RefString[MAX];

int main(void)
{
	accept();
	
	fifo();
	
	disp();
	
	return 0;
}

void accept(void)
{
	int i;
	
	printf("\nEnter Total Number Of Frames : ");
	scanf("%d", &n);
	
	printf("\nEnter Total Number Of Page Numbers : ");
	scanf("%d", &m);
	
	printf("\nEnter %d Page Numbers : ", m);
	for(i = 0; i < m; i++)
	{
		printf("\n[Page %d] = ", (i + 1));
		scanf("%d", &RefString[i]);
	}	
}

void fifo(void)
{
	int i;
	int j;
	
	for(i = 0; i < m; i++)
	{
		if(search(RefString[i]) == -1)
		{
			frames[sp] = RefString[i];
			fault++;

			sp = (sp + 1) % n;

			for(j = 0; j < n; j++)
				mem[j][i] = frames[j];						
		}
	}
}

int search(int pno)
{
	int i;
	
	for(i = 0; i < n; i++)
	{
		if(frames[i] == pno)
			return i;
	}
	
	return -1;
}

void disp(void)
{
	int i;
	int j;
	
	for(i = 0; i < m; i++)
		printf("%3d", RefString[i]);
	
	printf("\n\n");
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(mem[i][j])
				printf("%3d", mem[i][j]);
			else
				printf("   ");
		}
		printf("\n");
	}
	
	printf("\n\nTotal Page Fault : %d\n\n", fault);
}

