#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
	int i, j, arr[argc], key, mid, n;
	
	for(j=0; j < argc-1; j++)
	{
	 	n = atoi(argv[j]);
		arr[j] = n;
	}
	
	key = atoi(argv[j]);
	i = 0;
	j = argc-1;
	mid = (i+j)/2;
	
	while((arr[mid] != key) && (i <= j))
	{
		if(key > arr[mid])
		{
			i = mid+1;
		}
		else
		{
			j = mid-1;
		}
		
		mid=(i+j)/2;
	}
	
	if(i<=j)
	{
		printf("\n%d is present in the given array\n", key);
	}
	else
	{
		printf("\n%d is NOT present in the given array\n", key);
	}
	
	return 0;
}
