#include <stdio.h>
#include <string.h>

struct node
{
	int iArrival;
	int iBurst;
	int iComplete;
	int iTempBurst;
	char strName[5];
};

void Sort(void);
void FCFS(void);
void Output(void);
void AcceptInfo(void);

int iSize;
struct node arr[10];

int main(void)
{
	AcceptInfo();
	
	Sort();
	
	FCFS();
	
	Output();
	
	return 0;
}

void AcceptInfo(void)
{
	int i;
	
	printf("\n\t-->Enter Total No. Of Processes ; ");
	scanf("%d", &iSize);
	
	for(i = 0; i < iSize; i++)
	{
		printf("\n\t---------------------------------------------------\n");
		printf("\n\tEnter Process %d Details :- ", (i + 1));
		
		printf("\n\t\t1)Enter Process Name : ");
		scanf("%s", arr[i].strName);
		
		printf("\n\t\t2)Enter Process Arrival Time : ");
		scanf("%d", &arr[i].iArrival);
		
		printf("\n\t\t3)Enter Process Burst Time : ");
		scanf("%d", &arr[i].iBurst);
		
		arr[i].iTempBurst = arr[i].iBurst;
		printf("\n\t---------------------------------------------------\n");
	}
}

void Sort(void)
{
	int i;
	int j;
	char name[5];
	
	for(i = 0; i < (iSize - 1); i++)
	{
		for(j = (i + 1); j < iSize; j++)
		{
			if(arr[i].iArrival > arr[j].iArrival)
			{
				strcpy(name, arr[i].strName);
				strcpy(arr[i].strName, arr[j].strName);
				strcpy(arr[j].strName, name);
				
				arr[i].iArrival = arr[i].iArrival + arr[j].iArrival;
				arr[j].iArrival = arr[i].iArrival - arr[j].iArrival;
				arr[i].iArrival = arr[i].iArrival - arr[j].iArrival;

				arr[i].iBurst = arr[i].iBurst + arr[j].iBurst;
				arr[j].iBurst = arr[i].iBurst - arr[j].iBurst;
				arr[i].iBurst = arr[i].iBurst - arr[j].iBurst;

				arr[i].iTempBurst = arr[i].iTempBurst + arr[j].iTempBurst;
				arr[j].iTempBurst = arr[i].iTempBurst - arr[j].iTempBurst;
				arr[i].iTempBurst = arr[i].iTempBurst - arr[j].iTempBurst;
			}
		}
	}
}

void FCFS(void)
{
	int i;
	int iFlag;
	int iTime = 0;
	int iFinish = 0;

	printf("\n\t------------------Gantt Chart-----------------------\n\t");	
	while(iFinish != 1)
	{
		iFlag = 0;
		
		for(i = 0; i < iSize; i++)
		{
			if(arr[i].iArrival <= iTime && arr[i].iTempBurst != 0)
			{
				printf("|%d--%s", iTime, arr[i].strName);
				
				iTime = iTime + arr[i].iTempBurst;
				arr[i].iTempBurst = 0;
				arr[i].iComplete = iTime;

				printf("--%d|", iTime);
				iFlag = 1;
			}
		}
		
		if(0 == iFlag)
		{
			printf("|%d--*", iTime);
			iTime++;
			printf("--%d|", iTime);
		}
		
		for(i = 0; i < iSize; i++)
		{
			if(0 == arr[i].iTempBurst)
				continue;
			else
				break;
		}
		
		if(i == iSize)
			iFinish = 1;
	}
}

void Output(void)
{
	int i;
	int iWT;
	int iTAT;
	float iTotalWT = 0;
	float iTotalTAT = 0;
	
	printf("\n\t---------------------------------------------------\n");
	printf("\n\n\tNAME\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n");
	for(i = 0; i < iSize; i++)
	{
		iTAT = arr[i].iComplete - arr[i].iArrival;
		iWT = iTAT - arr[i].iBurst;
		
		iTotalTAT = iTotalTAT + iTAT;
		iTotalWT = iTotalWT + iWT;
		
		printf("\t%d)%s\t%d\t%d\t%d\t%d\t%d\n", (i + 1), arr[i].strName, arr[i].iArrival, arr[i].iBurst, arr[i].iComplete, iTAT, iWT);
	}
	printf("\n\t---------------------------------------------------\n");
	
	printf("\n\n\t1)Average TAT = %f\n\t2)Average WT = %f\n\n", (iTotalTAT / iSize), (iTotalWT / iSize));
}

