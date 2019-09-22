/*
	ASSIGNMENT 2(A)
	
	Implement the C program in which main program accepts the integers to be sorted. Main program uses the FORK system call to create a new process called a child process. Parent process sorts the integers using sorting algorithm and waits for child process using WAIT system call to sort the integers using any sorting algorithm. Also demonstrate zombie and orphan states
*/

#include <stdio.h>
#include <unistd.h>

void quicksort(int arr[], int f, int l);
void swap(int* x, int* y);
void partition(int arr[], int l, int h);
void mergesort(int list[], int low, int mid, int high);
void display(int arr[], int n);

int main()
{
	pid_t p_id;
	int num[20], count, i;
	
	/* accept integers to be sorted */
	printf("\nEnter no. of integers to be sorted: ");
	scanf("%d", &count);
	
	printf("\nEnter integers\n");
	for(i=0; i<count; i++)
	{
		scanf("%d", &num[i]);
	}
	
	/* fork system call to create a child process */
	p_id = fork();
	
	if(p_id > 0) /* parent process */
	{
		/* parent waits for child to complete sorting */
		wait(NULL);
		printf("\n********************");
		printf("\nIN PARENT PROCESS");
		printf("\nProcess ID: %d", getpid());
		printf("\n********************\n");
		
		quicksort(num, 0, count-1);
		
		printf("\nIntegers sorted using Quicksort\n");
		display(num, count);
		printf("\n");
	}
	else if(p_id == 0) /* child process */
	{
		printf("\n********************");
		printf("\nIN CHILD PROCESS");
		printf("\nProcess ID: %d", getpid());
		printf("\n********************\n");
		
		partition(num, 0, count-1);
		
		printf("\nIntegers sorted using Mergesort\n");
		display(num, count);
	}
	else /* failed to create child process */
	{
		printf("\nChild process could not be created!\n");
	}
	
	return 0;
}

/* function for quicksort */
void quicksort(int arr[], int f, int l)
{
	int pivot,i,j;	
	
	if(f < l)
	{
		pivot = f;
		i = f;
		j = l;
		
		while(i < j)
		{
			while(arr[i] <= arr[pivot])
			{
				i++;
			}
			while(arr[j] > arr[pivot])
			{
				j--;
			}
			if(i < j)
			{
				swap(&arr[i], &arr[j]);
			}
		}
		
		swap(&arr[pivot], &arr[j]);
		
		quicksort(arr, f, j-1);
		quicksort(arr, j+1, l);
	}
}

/* function to swap integers */
void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* function to create partition */
void partition(int arr[], int l, int h)
{
	if(l < h)
	{
		int m = (l+h)/2;
		partition(arr, l, m);
		partition(arr, m+1, h);
		mergesort(arr, l, m, h);
	}
}

/* function for mergesort */
void mergesort(int list[], int low, int mid, int high)
{
	int i, mi, k, lo, temp[50];

    lo = low;
	i = low;
	mi = mid + 1;

    while((lo <= mid) && (mi <= high))
	{
		if(list[lo] <= list[mi])
		{
			temp[i] = list[lo];
			lo++;
		}
		else
		{
			temp[i] = list[mi];
			mi++;
		}
		i++;
	}

    if (lo > mid)
	{
		for (k = mi; k <= high; k++)
		{
			temp[i] = list[k];
			i++;
		}
	}
	else
	{
		for (k = lo; k <= mid; k++)
		{
			temp[i] = list[k];
			i++;
		}
	}
	
	for(k = low; k <= high; k++)
	{
		list[k] = temp[k];
	}
}

/* function to print sorted array */
void display(int arr[], int n)
{
	for(int i=0; i<n; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
