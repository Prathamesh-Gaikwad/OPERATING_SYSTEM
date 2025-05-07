#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int j;
	int n;
	int size;
	int move;
	int index;
	int initial;
	int RQ[100];
	int TotalHeadMoment = 0;
	
	printf("\n\t1)Enter No. Of Request : ");
	scanf("%d", &n);
	
	printf("\n\t2)Enter The Request Sequence : ");
	for(i = 0; i < n; i++)
	{
		printf("\n\t\t-->Request[%d] : ", i+1);
		scanf("%d", &RQ[i]);
	}
		
	printf("\n\t3)Enter The Inital Head Position : ");
	scanf("%d", &initial);

	printf("\n\t4)Enter Total Disk Size : ");
	scanf("%d", &size);
	
	printf("\n\t5)Enter The Head Movement Direction For High 1 and For Low 0 : ");
	scanf("%d", &move);
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n-1; j++)
		{
			if(RQ[j] > RQ[j+1])
			{
				int temp;
				temp = RQ[j];
				RQ[j] = RQ[j+1];
				RQ[j+1] = temp;
			}
		}
	}
	
	for(i = 0; i < n; i++)
	{
		if(initial < RQ[i])
		{
			index = i;
			break;
		}
	}
	
	if(1 == move)
	{
		for(i = index; i < n; i++)
		{
			TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);			
			initial = RQ[i];
		}
		
		TotalHeadMoment = TotalHeadMoment + abs(size - RQ[i-1] - 1);
		initial = size - 1;
		
		for(i = index - 1; i >= 0; i--)
		{
			TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);			
			initial = RQ[i];			
		}
	}
	else
	{
		for(i = index-1; i >= 0; i--)
		{
			TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);			
			initial = RQ[i];					
		}
		TotalHeadMoment = TotalHeadMoment + abs(RQ[i+1] - 0);			
		initial = 0;
		
		for(i = index; i < n; i++)
		{
			TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);			
			initial = RQ[i];					
		}				
	}

	printf("\n\t6)Total Head Movement : %d", TotalHeadMoment);
	
	return 0;
}
