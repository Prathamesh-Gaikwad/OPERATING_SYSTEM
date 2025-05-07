#include <stdio.h>
#define MAX 20

void lru(void);
int get_lru(void);
void accept(void);
void display(void);
int search(int pNo);

int n;
int m;
int sp;
int fault;
int ref[MAX];
int time[MAX];
int frames[MAX];
int mem[MAX][MAX];

int main(void)
{
	accept();
	
	lru();
	
	display();
	
	return 0;
}

void lru(void)
{
	int i;
	int j;
	int k;
	
	for(i = 0; i < m && sp < n; i++)
	{
		k = search(ref[i]);
		
		if(-1 == k)
		{
			frames[sp] = ref[i];
			fault++;

			time[sp] = i;

			sp++;
			
			for(j = 0; j < n; j++)
				mem[j][i] = frames[j];
		}
		else
			time[k] = i;
	}
	
	for(; i < m; i++)
	{
		k = search(ref[i]);
		
		if(-1 == k)
		{
			sp = get_lru();
			
			frames[sp] = ref[i];
			fault++;
			
			time[sp] = i;	

			for(j = 0; j < n; j++)
				mem[j][i] = frames[j];
		}
		else
			time[k] = i;
	}
}

int get_lru(void)
{
	int i;
	int min_i;
	int min = 99;
	
	for(i = 0; i < n; i++)
	{
		if(time[i] < min)
		{
			min = time[i];
			min_i = i;
		}
	}
	
	return min_i;
}

int search(int pNo)
{
	int i;
	
	for(i = 0; i < n; i++)
	{
		if(frames[i] == pNo)
			return i;
	}
	
	return -1;
}

void display(void)
{
	int i;
	int j;
	
	printf("\n\n\t[--Frame Representation During Paging--]\n");
	printf("\n\t--------------------------------\n\t");
	for(i = 0; i < m; i++)
		printf("%3d", ref[i]);
		
	printf("\n\t--------------------------------\n\t");
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(mem[i][j])
				printf("%3d", mem[i][j]);
			else
				printf("   ");
		}
		printf("\n\t");
	}
	printf("\b\n\t--------------------------------\n");
	
	printf("\n\t[Total Number Of Page Fault Occured = %d]\n\n", fault);
}

void accept(void)
{
	int i;
	
	printf("\n\tEnter Total Number Of Frames : ");
	scanf("%d", &n);
	
	printf("\n\tEnter Total Number Of Reference String : ");
	scanf("%d", &m);
	
	printf("\n\tEnter %d Page Numbers : \n", m);
	for(i = 0; i < m; i++)
	{
		printf("\n\t-->[page %d] : ", (i + 1));
		scanf("%d", &ref[i]);
	}
	
}

