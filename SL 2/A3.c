/*
	ASSIGNMENT 3
	Implement multithreading for matrix multiplication using pthreads
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* define size of matrices and no. of threads */
#define MAX_SIZE 5
#define MAX_THREAD 25

/* matrices and no. of rows and cols */
int matA[MAX_SIZE][MAX_SIZE], matB[MAX_SIZE][MAX_SIZE], matC[MAX_SIZE][MAX_SIZE];
int rowA, colA, rowB, colB;

/* struct to store row and col index */
struct matIndex
{
	int i, j;
};

void* mulThread();

int main()
{
	/* input no. of rows and cols of matrices A and B */
	printf("\nEnter rows and columns of matrix A: ");
	scanf("%d %d", &rowA, &colA);
	
	printf("\nEnter rows and columns of matrix B: ");
	scanf("%d %d", &rowB, &colB);
	
	if(colA == rowB)
	{
		int i, j;
		
		/* input matrices A and B */
		printf("\nEnter matrix A\n");
		for(i=0; i<rowA; i++)
		{
			for(j=0; j<colA; j++)
			{
				scanf("%d", &matA[i][j]);
			}
		}
	
		printf("\nEnter matrix B\n");
		for(i=0; i<rowB; i++)
		{
			for(j=0; j<colB; j++)
			{
				scanf("%d", &matB[i][j]);
			}
		}
		
		/* define threads */
		pthread_t tid[MAX_THREAD];
		int count=0;
		
		for(i=0; i<rowA; i++)
		{
			for(j=0; j<colB; j++)
			{
				/* save current row and col index in struct matIndex */
				struct matIndex* data = (struct matIndex*) malloc(sizeof(struct matIndex));
				data->i = i;
				data->j = j;
				
				/* create a thread and pass struct matIndex */
				pthread_create(&tid[count], NULL, mulThread, data);
				
				/* wait for completion of all threads */
				pthread_join(tid[count], NULL);
				
				count++;
			}
		}
	
		/* print resultant matrix */
		printf("\nResultant matrix\n");
		for(i=0; i<rowA; i++)
		{
			for(j=0; j<colB; j++)
			{
				printf("%d\t", matC[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		printf("\nCannot multiply matrices!\n");
	}
	
	return 0;
}

void* mulThread(void* arg)
{
	struct matIndex* index = arg;
	int k, sum=0;
	
	/* multiply row of A with col of B */
	for(k=0; k<rowB; k++)
	{
		sum += matA[index->i][k] * matB[k][index->j];
	}
	
	/* assign value to resultant matrix */
	matC[index->i][index->j] = sum;
	
	/* exit the thread */
	pthread_exit(0);
}
