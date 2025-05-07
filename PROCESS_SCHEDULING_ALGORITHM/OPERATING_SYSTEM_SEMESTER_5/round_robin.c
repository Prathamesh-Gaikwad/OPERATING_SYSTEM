void RoundRobin(void)
{
	int i;
	int flag = 0;
	int time = 0;
	int finish = 0;
	
	while(finish != 1)
	{
		flag = 0;
		
		for(i = 0; i < size; i++)
		{
			if(arr[i].at <= time && arr[i].bt1 != 0)
			{
				printf("|%d--%s", time, arr[i].name);
				
				if(arr[i].bt1 > timeQuantum)
				{
					time = time + timeQuantum;
					arr[i].bt1 = arr[i].bt1 - timeQuantum;
				}
				else
				{
					time = time + arr[i].bt1;
					arr[i].bt1 = 0;
					arr[i].ct = time;
				}
				
				printf("--%d|", time);
				flag = 1;
			}
		}
		
		if(0 == flag)
		{
			printf("|%d--*", time);
			time++;
			printf("--%d|", time);
		}
		
		for(i = 0; i < size; i++)
		{
			if(0 == arr[i].bt1)
				continue;
			else
				break;
		}
		
		if(i == size)
			finish = 1;
	}
}

