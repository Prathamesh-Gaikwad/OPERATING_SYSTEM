#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	int i;
	int j;
	int k;
	int max;
	int diff;
	int head;
	int seek = 0;
	int queue[20];
	
	float avg;
	
	printf("\n\t1)Enter The MAX Range Of Disk : ");
	scanf("%d", &max);
	
	printf("\n\t2)Enter The Size Of Queue Request : ");
	scanf("%d", &n);
	
	printf("\n\t3)Enter The Queue Of Disk Position To Be Read : ");
	for(i = 1; i <= n; i++)
	{
		printf("\n\t\t-->Request[%d] : ", i);
		scanf("%d", &queue[i]);
	}
		
	printf("\n\t4)Enter The Initial Head Position : ");
	scanf("%d", &head);
	
	queue[0] = head;
	for(j = 0; j <= n-1; j++)
	{
		diff = abs(queue[j+1]-queue[j]);
		seek = seek + diff;
	}
	
	printf("\n\t5)Total Seek Time : %d", seek);
	
	avg = seek /(float)n;
	printf("\n\n\t6)Average Seek Time Is : %f", avg);
	
	return 0;
}
