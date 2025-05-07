#define MAX 20
#include <stdio.h>

void mru(void);
void accept(void);
int get_mru(void);
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
	
	mru();
	
	display();
	
	return 0;
}

int get_mru(void)
{
	int i;
	int max_i;
	int max = 99;
	
	for(i = 0; i < n; i++)
	{
		if(time[i] > max)
		{
			max = time[i];
			max_i = i;
		}
	}
	
	return max_i;
}

void mru(void)
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
			sp = get_mru();
			
			frames[sp] = ref[i];
			fault++;
			
			time[sp] = i;
			
			
			for(j = 0; j < m; j++)
				mem[j][i] = frames[j];
		}
		else
			time[k] = i;
	}
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
	
	printf("\n\t4)[--Frame Representation During Paging--]");
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
	printf("--------------------------------");		
	
	printf("\n\n\t5)[Total Number Of Page Fault Occured : %d]\n\n", fault);
}

void accept(void)
{
	int i;
	
	printf("\n\t1)Enter Total Number Of Frames : ");
	scanf("%d", &n);
	
	printf("\n\t2)Enter Total Number Of Page Numbers : ");
	scanf("%d", &m);
	
	printf("\n\t3)Enter %d Page Numbers : \n", m);
	for(i = 0; i < m; i++)
	{
		printf("\n\t-->[Page %d] : ", (i + 1));
		scanf("%d", &ref[i]);
	}
}

