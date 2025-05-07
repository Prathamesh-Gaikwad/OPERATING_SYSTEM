#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int at;
	int bt;
	int ct;
	int bt1;
	char name[5];
	struct node *pNext;
};

struct ganttChart
{
	int start;
	char name[5];
	int end;
};

void sort(void);
void sjf_np(void);
void output(void);
void accept_info(void);
struct node* get_p(void);
void print_gantt_chart(void);

int k;
int time;
int size;
struct ganttChart s[10];
struct ganttChart s1[10];
struct node *pFirst = NULL;
struct node *pLast = NULL;

int main(void)
{
	accept_info();
	sort();
	sjf_np();
	output();
	print_gantt_chart();
	
	return 0;
}

void accept_info(void)
{
	int i;
	struct node *pNewNode = NULL;
	
	printf("\n\tEnter Total No. Of Processes : ");
	scanf("%d", &size);
	
	for(i = 0; i < size; i++)
	{
		pNewNode = (struct node *) malloc(sizeof(struct node));
		
		if(NULL == pNewNode)
		{
			printf("\n\tMemory Allocation Failed");
			return;
		}
		
		printf("\n\tEnter Process %d Details :- ", (i + 1));
		
		printf("\n\n\t\t1)Enter Process Name : ");
		scanf("%s", pNewNode->name);

		printf("\n\t\t2)Enter Process Arrival Time : ");
		scanf("%d", &pNewNode->at);
		
		printf("\n\t\t3)Enter Process Burst Time : ");
		scanf("%d", &pNewNode->bt);
		
		pNewNode->bt1 = pNewNode->bt;
		pNewNode->pNext = NULL;
		
		if(NULL == pFirst)
			pFirst = pLast = pNewNode;
		else
		{
			pLast->pNext = pNewNode;
			pLast = pNewNode;
		}
	}
}

void sort(void)
{
	char name[5];
	struct node *pTemp1 = NULL;
	struct node *pTemp2 = NULL;
	
	pTemp1 = pFirst;
	while(pTemp1->pNext != NULL)
	{
		pTemp2 = pTemp1->pNext;
		
		while(pTemp2 != NULL)
		{
			if(pTemp1->at > pTemp2->at)
			{
				strcpy(name, pTemp1->name);
				strcpy(pTemp1->name, pTemp2->name);
				strcpy(pTemp2->name, name);
				
				pTemp1->at = pTemp1->at + pTemp2->at;
				pTemp2->at = pTemp1->at - pTemp2->at;
				pTemp1->at = pTemp1->at - pTemp2->at;
				
				pTemp1->bt = pTemp1->bt + pTemp2->bt;
				pTemp2->bt = pTemp1->bt - pTemp2->bt;
				pTemp1->bt = pTemp1->bt - pTemp2->bt;
				
				pTemp1->bt1 = pTemp1->bt1 + pTemp2->bt1;
				pTemp2->bt1 = pTemp1->bt1 - pTemp2->bt1;
				pTemp1->bt1 = pTemp1->bt1 - pTemp2->bt1;
			}
			
			pTemp2 = pTemp2->pNext;
		}
		
		pTemp1 = pTemp1->pNext;
	}
}

void sjf_np(void)
{
	int n1 = 0;
	int prev = 0;
	struct node *pTemp = NULL;
	
	while(n1 != size)
	{
		pTemp = get_p();
		
		if(NULL == pTemp)
		{
			time++;
			
			s[k].start = prev;
			strcpy(s[k].name, "*");
			s[k].end = time;
			
			prev = time;
			
			k++;
		}
		else
		{
			time = time + pTemp->bt1;
			
			s[k].start = prev;
			strcpy(s[k].name, pTemp->name);
			s[k].end = time;
			
			pTemp->bt1 = 0;
			prev = pTemp->ct = time;
			
			k++;
			n1++;
		}
	}
}

struct node* get_p(void)
{
	int min = 99;
	struct node *min_p = NULL;
	struct node *pTemp = NULL;
	
	pTemp = pFirst;
	while(pTemp != NULL)
	{
		if(pTemp->at <= time && pTemp->bt1 != 0 && pTemp->bt1 < min)
		{
			min = pTemp->bt1;
			min_p = pTemp;
		}
		
		pTemp = pTemp->pNext;
	}
	
	return min_p;
}

void print_gantt_chart(void)
{
	int i;
	int j;
	int m;
	
	s1[0] = s[0];
	
	for(i = 1, j = 0; i <= k; i++)
	{
		if(strcmp(s[i].name, s1[j].name) == 0)
			s1[j].end = s[i].end;
		else
			s1[++j] = s[i];
	}
	
	printf("\n\t%d", s1[0].start);
	
	for(i = 0; i < j; i++)
	{
		m = s1[i].end - s1[i].start;
		
		for(k = 0; k < m/2; k++)
			printf("-");
		
		printf("-%s-", s1[i].name);
		
		for(k = 0; k < (m + 1)/2; k++)
			printf("-");
			
		printf("%d", s1[i].end);
	}
	printf("\n");
}

void output(void)
{
	int tat;
	int wt;
	float total_tat = 0;
	float total_wt = 0;
	struct node *pTemp = NULL;
	
	pTemp = pFirst;
	
	printf("\n\tName\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n");
	
	while(pTemp != NULL)
	{
		tat = pTemp->ct - pTemp->at;
		wt = tat - pTemp->bt;
		
		total_tat = total_tat + tat;
		total_wt = total_wt + wt;
		
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\n", pTemp->name, pTemp->at, pTemp->bt, pTemp->ct, tat, wt);
		pTemp = pTemp->pNext;
	}
	printf("\n\t1)Average TAT = %f\n\t2)Average WT = %f\n", (total_tat/size), (total_wt/size));
}

