#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
	int at;
	int bt;
	int ct;
	int bt1;
	int p;
	char name[5];
}tab[10];

struct ganttchart
{
	int start;
	int end;
	char name[5];
}s[10], s1[10];

void sort(void);
void accept(void);
void printinput(void);
void printoutput(void);
void processinput(void);
void print_gantt_chart(void);

int n;
int k;
int time;
int prev;
int finish;

int main(void)
{
	int i;
	
	accept();
	
	sort();
	
	processinput();
	
	printoutput();
	
	print_gantt_chart();
	
	for(i = 0; i < n; i++)
	{
		tab[i].bt1 = tab[i].bt = rand()%10+1;
		tab[i].at = tab[i].ct+2;
	}

	processinput();
	
	printoutput();
	
	print_gantt_chart();

	return 0;
}

void processinput(void)
{
	int i;
	
	k = finish = 0;
	
	while(finish != n)
	{
		outside :
			for(i = 0; i < n; i++)
			{
				if(tab[i].at <= time && tab[i].bt1 != 0)
				{
					time++;
					tab[i].bt1--;
					
					printinput();
					
					s[k].start = prev;
					s[k].end = time;
					strcpy(s[k++].name, tab[i].name);
					
					prev = tab[i].ct = time;
					
					if(0 == tab[i].bt1)
						finish++;
					
					goto outside;
				}
			}
			
			if(finish != n)
			{
				time++;
				
				s[k].start = prev;
				s[k].end = time;
				strcpy(s[k].name, "*");
				
				prev = time;
			}
	}
}

void printinput(void)
{
	int i;
	
	printf("\nName\tAT\tBT\tP\n");
	for(i = 0; i < n; i++)
	{
		printf("%s\t%d\t%d\t%d\n", tab[i].name, tab[i].at, tab[i].bt, tab[i].p);
	}
}

void sort(void)
{
	int i;
	int j;
	struct node t;
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n-1-i; j++)
		{
			if(tab[j].p > tab[j+1].p)
			{
				t = tab[i];
				tab[i] = tab[j];
				tab[j] = t;
			}
		}
	}
}

void print_gantt_chart(void)
{
	int i;
	int j;
	
	s1[0] = s[0];
	for(i = 1; i < k; i++)
	{
		if(strcmp(s1[j+1].name, s[i].name) == 0)
			s1[j+1].end = s[i].end;
		else
			s1[j++] = s[i];
	}
	
	for(i = 0; i < j; i++)
		printf("%d--%s--%d-",s1[i].start, s1[i].name, s1[i].end);
}

void accept(void)
{
	int i;
	
	printf("Enter Total Number Of Process : ");
	scanf("%d", &n);
	
	for(i = 0; i < n; i++)
	{
		printf("\nEnter Process Name : ");
		scanf("%s", tab[i].name);
		
		printf("\nEnter Arrival Time : ");
		scanf("%d", &tab[i].at);

		printf("\nEnter Burst Time : ");
		scanf("%d", &tab[i].bt);

		printf("\nEnter Process Priority : ");
		scanf("%d", &tab[i].p);
		
		tab[i].bt1 = tab[i].bt;
	}
}

void printoutput(void)
{
	int i;
	int tat;
	int wt;
	float total_tat;
	float total_wt;
	
	printf("\nName\tAT\tBT\tCT\tTAT\tWT\n");
	for(i = 0; i < n; i++)
	{
		tat = tab[i].ct - tab[i].at;
		wt = tat - tab[i].bt;
		total_tat = total_tat + tat;
		total_wt = total_wt + wt;
		
		printf("%s\t%d\t%d\t%d\t%d\t%d\t\n", tab[i].name, tab[i].at, tab[i].bt, tab[i].ct, tat, wt);
	}
	
	printf("\nAverage TAT = %f\nAverage WT = %f\n", (total_tat/n), (total_wt/n));
}

