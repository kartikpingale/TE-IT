/*
	ASSIGNMENT 2(B)
	
	Implement the C program in which main program accepts an integer array. Main program uses the FORK system call to create a new process called a child process. Parent process sorts an integer array and passes the sorted array to child process through the command line arguments of EXECVE system call. The child process uses EXECVE system call to load new program that uses this sorted array for performing the binary search to search the particular item in the array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void bubble(int arr[], int n);
void swap(int* x, int* y);
void display(int arr[], int n);

int main(int argc, char* argv[])
{
	pid_t p_id;
	int num[20], count, key, i;
	char* argp[10];
	
	/* accept integers to be sorted */
	printf("\nEnter no. of integers to be sorted: ");
	scanf("%d", &count);
	
	printf("\nEnter integers\n");
	for(i=0; i<count; i++)
	{
		scanf("%d", &num[i]);
	}
	
	/* sort integers */
	bubble(num, count);
	
	/* print sorted integers */
	printf("\nSorted integers\n");
	display(num, count);
	
	/* get integer to search */
	printf("\nEnter integer to search: ");
	scanf("%d", &key);
	
	num[i] = key;
	
	/* convert int to string */
	for(i=0; i < count+1; i++)
	{
		char a[count];
		snprintf(a,sizeof(int),"%d",num[i]);
		
		argp[i] = malloc(sizeof(a));
		strcpy(argp[i],a);
		/*
		char arr[count*2];
		snprintf(arr, sizeof(int), "%d", num[i]);
		printf("%s\t", arr);
		printf("%s\t", arr);
		*/
	}
	argp[i] = NULL;
	
	/* fork system call to create a child process */
	p_id = fork();
	
	if(p_id == 0) /* child process */
	{
		execve(argv[1], argp, NULL);
		perror("Cannot search for the number!");
	}
	
	return 0;
}

/* function to sort integers using bubble sort */
void bubble(int arr[], int n)
{
	int i,j;
	
	for(i=0; i<n-1; i++)
	{
		for(j=0; j<n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(&arr[j], &arr[j+1]);
			}
		}
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

/* function to print sorted array */
void display(int arr[], int n)
{
	for(int i=0; i<n; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}