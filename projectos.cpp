#include<stdio.h>
int main()
{
	int size,i;
	printf("Enter the number of process : ");
	scanf("%d",&size);
	int p[size];
	int pp,AT[size],BT[size],pr[size],BT1[size],CT[size],TAT[size],WT[size];
	for(i=0;i<size;i++)
	{
		printf("\n\nenter the process number : ");
		scanf("%d",&p[i]);
		printf("enter the Arrival Time of P%d : ",p[i]);
		scanf("%d",&AT[i]);
		printf("enter the Burst Time of P%d : ",p[i]);
		scanf("%d",&BT[i]);
		printf("enter the Priority of P%d : ",p[i]);
		scanf("%d",&pr[i]);
	}
	int j,min,pos,temp,TQ=4;
	int l,k,a=0,limit[50];
	int process[50];
	for(i=0;i<size;i++)
	{
		min=AT[i];
		pos=i;
		for(j=i+1;j<size;j++)
		{
			if(AT[j]<min)
			{
				min=AT[j];
				pos=j;
			}
		}
		// ARRIVAL TIME SWAPPING
		temp=AT[i];
		AT[i]=AT[pos];
		AT[pos]=temp;
		// BURST TIME SWAPPING
		temp=BT[i];
		BT[i]=BT[pos];
		BT[pos]=temp;
		// PRIORITY SWAPPING
		temp=pr[i];
		pr[i]=pr[pos];
		pr[pos]=temp;
		// PROCESS NUMBER SWAPPING
		temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
		// COPYING BURST TIME
		BT1[i]=BT[i];
	}
	min=pr[0];
	for(i=1;i<size;i++)
		if(pr[i]<min)
			min=pr[i];
	i=0;
	k=1;
	do{
		if(k==0)
			a++;
		//for(l=0;l<=a;l++)
			for(j=0;j<size;j++)
				if(AT[j]<=a && pr[i]<pr[j])
					i=j;
		k=0;
	}while(AT[0]!=a);
	int s=0;
	limit[0]=0;
	if(a>0)
	{
		limit[k+1]=a;
		process[k]='-';
		k++;
	}
	while(s!=size)
	{
		//printf("%d %d %d\n",a,i,s);
		if(i==size)
			i=0;
		else if(BT1[i]<=TQ && BT1[i]!=0)
		{	
			a+=BT1[i];
			limit[k+1]=a;
			CT[i]=a;
			process[k]=p[i];
			BT1[i]=0;
			pr[i]=min-1;
			min=pr[i];
			k++;
			i++;
			s++;
			//for(l=0;l<=a;l++)
				for(j=0;j<size;j++)
					if(AT[j]<=a && pr[i]<pr[j])
						i=j;
		}
		else if(BT1[i]>TQ && BT1[i]!=0)
		{
			a+=TQ;
			limit[k+1]=a;
			process[k]=p[i];
			BT1[i]-=TQ;
			pr[i]=min-1;
			min=pr[i];
			k++;
			i++;
		//	for(l=0;l<=a;l++)
				for(j=0;j<size;j++)
					if(AT[j]<=a && pr[i]<pr[j])
						i=j;
		}
		else
			i++;
	}
	
	for(i=0;i<size;i++)
	{
		TAT[i]=CT[i]-AT[i];
		WT[i]=TAT[i]-BT[i];
	}
	float awt=0,atat=0;
	printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
	for(i=0;i<size;i++)
	{
		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
		awt+=WT[i];
		atat+=TAT[i];
	}
	printf("\nAverage Waiting Time : %.2f\n",(awt/size));
	printf("Average Turn-around Time : %.2f",(atat/size));
}
