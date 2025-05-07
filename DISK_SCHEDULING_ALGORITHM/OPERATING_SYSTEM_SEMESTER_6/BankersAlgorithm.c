#include <stdio.h>

void Banker();
void CalNeed();
void NewRequest();
void AcceptInput();
void PrintSafeSeq();
int IsFeasible(int Pno);
void DisplayMatrix(int a[10][10], int N, int M);

int N;
int M;
int Available[10];
int tempAvailable[10];
int Max[10][10];
int Alloc[10][10];
int Need[10][10];
int safeseq[10];

int main(void)
{
	AcceptInput();
	
	CalNeed();
	
	printf("\n\tMax : ");
	DisplayMatrix(Max, N, M);
	
	printf("\n\tNeed : ");
	DisplayMatrix(Need, N, M);
	
	Banker();
	
	PrintSafeSeq();
	
	NewRequest();
	
	return 0;
}

void AcceptInput()
{
	int i;
	int j;
	
	printf("\n\tEnter No. Of Processes : ");
	scanf("%d", &N);

	printf("\n\tEnter No. Of Resource Types : ");
	scanf("%d", &M);
	
	printf("\n\tEnter Available : ");
	for(i = 0; i < M; i++)
	{
		printf("\n\tEnter No. Of Instances For Resource Types %c : ", (65+i));
		scanf("%d", &Available[i]);
		tempAvailable[i] = Available[i];
	}
	
	printf("\n\tEnter Max : ");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("\n\tEnter Max For Process %d, Res[%c] : ", i, (65+j));
			scanf("%d", &Max[i][j]);
		}
	}
	
	printf("\n\tEnter Allocation : ");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("\n\tEnter Allocation For Process P%d, res[%c] : ", i, (65+j));
			scanf("%d", &Alloc[i][j]);
		}
	}
	
	for(i = 0; i < N; i++)
		safeseq[i] = -1;
}

void DisplayMatrix(int a[10][10], int N, int M)
{
	int i;
	int j;
	
	printf("\n\t");
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			printf("%5d", a[i][j]);
		
		printf("\n\t");
	}
}

void CalNeed()
{
	int i;
	int j;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			Need[i][j] = Max[i][j] - Alloc[i][j];
	}
}

int IsFeasible(int Pno)
{
	int i;
	
	for(i = 0; i < M; i++)
	{
		if(Need[Pno][i] > Available[i])
			return 0;
	}
	
	return 1;
}

void Banker()
{
	int i;
	int j;
	int k = 0;
	int finish = 0;
	int flags[5] = {0, 0, 0, 0, 0};

	while(finish != 1)
	{
		for(i = 0; i < N; i++)
		{
			if(IsFeasible(i) && flags[i] != 1)
			{
				for(j = 0; j < M; j++)
					Available[j] = Available[j] - Need[i][j];
					
				for(j = 0; j < M; j++)
					Alloc[i][j] = Alloc[i][j] + Need[i][j];

				for(j = 0; j < M; j++)
					Available[j] = Available[j] + Alloc[i][j];
				
				safeseq[k++] = i;
				flags[i] = 1;
			}
		}
		
		for(i = 0; i < N; i++)
		{
			if(flags[i] == 1)
				continue;
			else
				break;
		}
		
		if(i == N)
			finish = 1;
	}
}

void PrintSafeSeq()
{
	int i;
	
	printf("\n\tSafe Sequence : < ");
	for(i = 0; i < N; i++)
	{
		printf("P%d, ", safeseq[i]);
	}
	printf("\b>\n");
}

void NewRequest()
{
	int i;
	int NewReq[10];
	
	for(i = 0; i < M; i++)
	{
		printf("\n\tEnter %c : ", (65+i));
		scanf("%d", &NewReq[i]);
	}
	
	for(i = 0; i < M; i++)
	{
		if(NewReq[i] > tempAvailable[i])
			break;
		else
			continue;
	}
	
	if(i != M)
		printf("\n\tNot Feasible, Hence Resource Can't be Granted");
	else
		printf("\n\tFeasible, Hence Resource Can be Granted");
}

/*
	o/p : 

        Enter No. Of Processes : 5

        Enter No. Of Resource Types : 3

        Enter Available : 
        Enter No. Of Instances For Resource Types A : 10

        Enter No. Of Instances For Resource Types B : 5

        Enter No. Of Instances For Resource Types C : 7

        Enter Max : 
        Enter Max For Process 0, Res[A] : 7

        Enter Max For Process 0, Res[B] : 5

        Enter Max For Process 0, Res[C] : 3

        Enter Max For Process 1, Res[A] : 3

        Enter Max For Process 1, Res[B] : 2

        Enter Max For Process 1, Res[C] : 2

        Enter Max For Process 2, Res[A] : 9

        Enter Max For Process 2, Res[B] : 0

        Enter Max For Process 2, Res[C] : 2

        Enter Max For Process 3, Res[A] : 2

        Enter Max For Process 3, Res[B] : 2

        Enter Max For Process 3, Res[C] : 2

        Enter Max For Process 4, Res[A] : 4

        Enter Max For Process 4, Res[B] : 3

        Enter Max For Process 4, Res[C] : 3

        Enter Allocation : 
        Enter Allocation For Process P0, res[A] : 0

        Enter Allocation For Process P0, res[B] : 1

        Enter Allocation For Process P0, res[C] : 0

        Enter Allocation For Process P1, res[A] : 2

        Enter Allocation For Process P1, res[B] : 0

        Enter Allocation For Process P1, res[C] : 0

        Enter Allocation For Process P2, res[A] : 3

        Enter Allocation For Process P2, res[B] : 0

        Enter Allocation For Process P2, res[C] : 2

        Enter Allocation For Process P3, res[A] : 2

        Enter Allocation For Process P3, res[B] : 1

        Enter Allocation For Process P3, res[C] : 1

        Enter Allocation For Process P4, res[A] : 0

        Enter Allocation For Process P4, res[B] : 0

        Enter Allocation For Process P4, res[C] : 2

        Max : 
            7    5    3
            3    2    2
            9    0    2
            2    2    2
            4    3    3

        Need : 
            7    4    3
            1    2    2
            6    0    0
            0    1    1
            4    3    1

        Safe Sequence : < P0, P1, P2, P3, P4,>

        Enter A : 8

        Enter B : 15

        Enter C : 9

        Not Feasible, Hence Resource Can't be Granted  	
*/
