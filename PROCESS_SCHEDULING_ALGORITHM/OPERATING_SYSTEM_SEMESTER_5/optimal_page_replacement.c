#define MAX 20
#include <stdio.h>

void opt(void);
int search(int);
void accept(void);
void display(void);
int get_opt(int, int);

int n;
int m;
int sp;
int fault;
int ref[MAX];
int frames[MAX];
int mem[MAX][MAX];

int main(void)
{
	accept();
	
	opt();
	
	display();
	
	return 0;
}

int get_opt(int sp, int s)
{
	int i;
	int j;
	int pos_i = -1;
	int pos_j = -1;
	
	j = sp;
	do
	{
		for(i = s; i < m; i++)
		{
			if(ref[i] == frames[i])
			{
				if(i > pos_i)
				{
					pos_i = i;
					pos_j = j;
					break;
				}
			}
		}
		
		if(i == m)
			return j;
			
		j = (j + 1) % n;
		
	}while(j != sp);
	
	return pos_j;
}

void opt(void)
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
			
			sp++;
			
			for(j = 0; j < n; j++)
				mem[j][i] = frames[j];
		}
	}
	
	sp = 0;
	for(; i < m; i++)
	{
		k = search(ref[i]);
		
		if(-1 == k)
		{
			sp = get_opt(sp, i);
			
			frames[sp] = ref[i];
			fault++;
			
			sp = (sp + 1) % n;
			
			for(j = 0; j < n; j++)
				mem[j][i] = frames[j];
		}
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
	printf("\n\t4)Output Section :- \n");
	printf("\n\t[Frame Representation Durng Page Fault]");
	printf("\n\t---------------------------------\n\t");
	for(i = 0; i < m; i++)
		printf("%3d", ref[i]);
	printf("\n\t---------------------------------\n\t");
		
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
	printf("---------------------------------\n\t");

	printf("\n\t[Total Page Fault Occured : %d]\n\n", fault);
}

void accept(void)
{
	int i;
	
	printf("\n\t1)Enter Total Number Of Frames : ");
	scanf("%d", &n);
	
	printf("\n\t2)nEnter Total Number Of Page Numbers : ");
	scanf("%d", &m);
	
	printf("\n\t3)Enter %d Page Numbers : \n", m);
	for(i = 0; i < m; i++)
	{
		printf("\n\t-->[Page %d] : ", (i + 1));
		scanf("%d", &ref[i]);
	}
}

