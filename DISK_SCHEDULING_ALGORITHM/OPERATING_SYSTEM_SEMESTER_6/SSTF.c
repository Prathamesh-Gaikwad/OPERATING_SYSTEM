#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int n;
	int d;
	int index;
	int RQ[100];
	int cnt = 0;
	int initial;
	int TotalHeadMoment = 0;
	
	printf("\n\t1)Enter No. Of Request : ");
	scanf("%d", &n);
	
	printf("\n\t2)Enter The Request Sequence : ");
	for(i = 0; i < n; i++)
	{
		printf("\n\t\t-->Request[%d] : ", i+1);
		scanf("%d", &RQ[i]);
	}
		
	printf("\n\t3)Enter Initial Head Position : ");
	scanf("%d", &initial);
	
	while(cnt != n)
	{
		int min = 1000;
		
		for(i = 0; i < n; i++)
		{
			d = abs(RQ[i] - initial);
			
			if(min > d)
			{
				min = d;
				index = i;
			}
		}
		
		TotalHeadMoment = TotalHeadMoment + min;
		initial = RQ[index];
		
		RQ[index] = 1000;
		cnt++;
	}
	
	printf("\n\t4)Total Head Moment Is : %d", TotalHeadMoment);
	
	return 0;
}
