#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int iArrival;
	int iBurst;
	int iComplete;
	int iTempBurst;
	char strName[5];
	struct node *pNext;
};

struct ganttchart
{
	int iStart;
	char strName[5];
	int iEnd;
};

void Sort(void);
void SJFP(void);
void Output(void);
void AcceptInfo(void);
struct node *GetSJF(void);
void PrintGanttChart(void);

int iTime;
int iSize;
int iCounter1;
struct node *pLast = NULL;
struct node *pFirst = NULL;
struct ganttchart arrPP[10];
struct ganttchart arrPP1[10];

int main(void)
{
	AcceptInfo();
	
	Sort();
	
	SJFP();
	
	Output();
	
	PrintGanttChart();
	
	return 0;
}

void Sort(void)
{
	char strName[5];
	struct node *pTemp1 = NULL;
	struct node *pTemp2 = NULL;
	
	pTemp1 = pFirst;
	
	while(pTemp1->pNext != NULL)
	{
		pTemp2 = pTemp1->pNext;
		
		while(pTemp2 != NULL)
		{
			if(pTemp1->iArrival > pTemp2->iArrival)
			{
				strcpy(strName, pTemp1->strName);
				strcpy(pTemp1->strName, pTemp2->strName);
				strcpy(pTemp2->strName, strName);
				
				pTemp1->iArrival = pTemp1->iArrival + pTemp2->iArrival;
				pTemp2->iArrival = pTemp1->iArrival - pTemp2->iArrival;
				pTemp1->iArrival = pTemp1->iArrival - pTemp2->iArrival;
				
				pTemp1->iBurst = pTemp1->iBurst + pTemp2->iBurst;
				pTemp2->iBurst = pTemp1->iBurst - pTemp2->iBurst;
				pTemp1->iBurst = pTemp1->iBurst - pTemp2->iBurst;
				
				pTemp1->iTempBurst = pTemp1->iTempBurst + pTemp2->iTempBurst;
				pTemp2->iTempBurst = pTemp1->iTempBurst - pTemp2->iTempBurst;
				pTemp1->iTempBurst = pTemp1->iTempBurst - pTemp2->iTempBurst;				
			}
			
			pTemp2 = pTemp2->pNext;
		}
		
		pTemp1 = pTemp1->pNext;
	}
}

void SJFP(void)
{
	int iPrev = 0;
	int iCount = 0;
	struct node *pTemp = NULL;
	
	while(iCount != iSize)
	{
		pTemp = GetSJF();
		
		if(NULL == pTemp)
		{
			iTime++;
			
			arrPP[iCounter1].iStart = iPrev;
			strcpy(arrPP[iCounter1].strName, "*");
			arrPP[iCounter1].iEnd = iTime;
			
			iPrev = iTime;
			iCounter1++;
		}
		else
		{
			iTime = iTime + pTemp->iTempBurst;
			
			arrPP[iCounter1].iStart = iPrev;
			strcpy(arrPP[iCounter1].strName, pTemp->strName);
			arrPP[iCounter1].iEnd = iTime;
			
			pTemp->iTempBurst--;
			iPrev = pTemp->iComplete = iTime;
			iCounter1++;
			
			if(0 == pTemp->iTempBurst)
				iCount++;
		}
	}
}

void Output(void)
{
	int iWT;
	int iTAT;
	float iTotalWT = 0;
	float iTotalTAT = 0;
	struct node *pTemp = NULL;
	
	pTemp = pFirst;
	
	printf("\n\tNAME\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n");
	
	while(pTemp != NULL)
	{
		iTAT = pTemp->iComplete - pTemp->iArrival;
		iWT = iTAT - pTemp->iBurst;
		
		iTotalTAT = iTotalTAT + iTAT;
		iTotalWT = iTotalWT + iWT;
		
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\n", pTemp->strName, pTemp->iArrival, pTemp->iBurst, pTemp->iComplete, iTAT, iWT);
		
		pTemp = pTemp->pNext;
	}
	
	printf("\n\n\t1)Average TAT = %f\n\t2)Average WT = %f\n", (iTotalTAT/iSize), (iTotalWT/iSize));
}

void AcceptInfo(void)
{
	int iCounter;
	struct node *pNewNode = NULL;
	
	printf("\n\t-->Enter Total No. Of Processes : ");
	scanf("%d", &iSize);
	
	for(iCounter = 0; iCounter < iSize; iCounter++)
	{
		pNewNode = (struct node *)malloc(sizeof(struct node));
		
		if(NULL == pNewNode)
		{
			printf("\n\t[Memory Allocation Failed]");
			return;
		}
		
		printf("\n\t----------------------------------------------------");
		printf("\n\t-->Enter Process %d Details :- ", (iCounter + 1));
		
		printf("\n\t\t1)Enter Process Name : ");
		scanf("%s", pNewNode->strName);

		printf("\n\t\t2)Enter Process Arrival Time : ");
		scanf("%d", &pNewNode->iArrival);
		
		printf("\n\t\t3)Enter Process Burst Time : ");
		scanf("%d", &pNewNode->iBurst);
		
		pNewNode->iTempBurst = pNewNode->iBurst;
		pNewNode->pNext = NULL;
		
		if(NULL == pFirst)
			pFirst = pLast = pNewNode;
		else
		{
			pLast->pNext = pNewNode;
			pLast = pNewNode;
		}
		
		printf("\n\t----------------------------------------------------");
	}
}

struct node *GetSJF(void)
{
	int iMin = 99;
	struct node *pTemp1 = NULL;
	struct node *pTemp2 = NULL;
	
	pTemp1 = pFirst;
	
	while(pTemp1 != NULL)
	{
		if(pTemp1->iArrival <= iTime && pTemp1->iTempBurst != 0 && pTemp1->iTempBurst < iMin)
		{
			iMin = pTemp1->iTempBurst;
			pTemp2 = pTemp1;
		}
		
		pTemp1 = pTemp1->pNext;
	}
	
	return pTemp2;
}

void PrintGanttChart(void)
{
	int iCounter2;
	int iCounter3;
	int iDifference;

	arrPP1[0] = arrPP[0];
	
	for(iCounter2 = 1, iCounter3 = 0; iCounter2 <= iCounter1; iCounter2++)
	{
		if(strcmp(arrPP[iCounter2].strName, arrPP1[iCounter3].strName) == 0)
			arrPP1[iCounter3].iEnd = arrPP[iCounter2].iEnd;
		else
			arrPP1[++iCounter3] = arrPP[iCounter2];
	}
	
	printf("\n\tGantt Chart :-\n\t%d", arrPP1[0].iStart);
	
	for(iCounter2 = 0; iCounter2 < iCounter3; iCounter2++)
	{
		iDifference = arrPP1[iCounter2].iEnd - arrPP1[iCounter2].iStart;
		
		for(iCounter1 = 0; iCounter1 < (iDifference/2); iCounter1++)
			printf("-");
		
		printf("-%s-", arrPP1[iCounter2].strName);
		
		for(iCounter1 = 0; iCounter1 < (iDifference + 1/2); iCounter1++)
			printf("-");
		
		printf("%d", arrPP1[iCounter2].iEnd);
	}
	
	printf("\n");
}

