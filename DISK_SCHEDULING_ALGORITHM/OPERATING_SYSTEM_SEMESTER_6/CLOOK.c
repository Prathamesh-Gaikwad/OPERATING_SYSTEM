#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    int j;
    int n;
    int head;
    int dst[20];
    int item[20];
    int cylinders = 0;
    
    printf("\n\t1)Enter No. Of Locations : ");
    scanf("%d",&n);

    printf("\n\t2)Enter Positions Of Head : ");
    scanf("%d", &head);

    printf("\n\t3)Enter Elements Of Disk Queue : ");
    for(i = 0; i < n; i++)
    {
        printf("\n\t-->Request[%d] : ", i+1);
        scanf("%d", &item[i]);
        dst[i] = (head - item[i]);
    }
    
    //selection sort
    for(i = 0; i < n-1; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(dst[j] > dst[i])
            {
                int temp = dst[j];
                dst[j] = dst[i];
                dst[i] = temp;
                
                temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        if(item[i] >= head)
        {
            j = i;
            break;
        }
    }
    
    printf("\n\t4)Order Of Disk Allocation Is As Follows : ");
    for(i = j; i < n; i++)
    {
        printf("-->%d", item[i]);
        cylinders = cylinders + abs(head-item[i]);
        head = item[i];
    }
    
    for(i = 0; i < j; i++)
    {
        printf("-->%d", item[i]);
        cylinders = cylinders + abs(head-item[i]);
        head = item[i];
    }
    
    printf("\n\n\t5)Cylinder Movement : %d", cylinders);
    
    return 0;
}
