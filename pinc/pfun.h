#include <stdlib.h>
#include <stdio.h>
void nline(int t)	
{
	if (t<=0) {
		printf("\n\e[0;91mt=%d, by the way\e[0m\n",t);
		exit(1);
	}
	for (int i=0;i<t;i++)
	{
		printf("\n");
	}
}
void ssort (int *arr, int size, int SL) //SL=1 or 0
{
	int p=0, c=1, k=0;
	while (1)
	{
		if (p>=size-1) p=0;
		if ((arr[p]>arr[p+1] && SL) || (arr[p]<arr[p+1] && !SL))
		{
			int t=arr[p];
			arr[p]=arr[p+1];
			arr[p+1]=t;
		}
		k=0;
		for (int a=0;a<size-1;a++) 
		{
			if ((arr[a]<=arr[a+1] && SL) || (arr[a]>=arr[a+1] && !SL))
				k++;	
			else
				break;
		}
		if (k==size-1) break;
		p++, c++;
	}
}
