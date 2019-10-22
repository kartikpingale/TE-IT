/*
ASSIGNMENT 7-A

Pipes: Full duplex communication between parent and child processes. Parent process writes a pathname of a file (the contents of the file are desired) on one pipe to be read by child process and child process writes the contents of the file on second pipe to be read by parent process and displays on standard output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX 10
#define read_end 0
#define write_end 1

int main()
{
	pid_t pid;
	int fd[2];			
	char write_msg[MAX] = "Hey!";
	char read_msg[MAX];
	
	if((pipe(fd) == -1))		
	{
		printf("\nFailed to create a pipe!");
	}
	else
	{
		pid=fork();
		
		if(pid < 0)
		{
			printf("\nFailed to create a child process!");
		}
		else if(pid > 0)				
		{
			close(fd[read_end]);
			write(fd[write_end], write_msg, strlen(write_msg)+1);
			close(fd[write_end]);
			/*
			printf("\nEnter the file name to be read : \n");
			scanf(" %s",write_msg);
					
			
			read(fd2[read_end],read_msg,sizeof(read_msg)+1);		
			
			printf("\nThe contents of the file are as follows : \n");	
			printf("%s",read_msg);
			printf("\n");
			wait(NULL);*/
		}
		else if(pid == 0)			
		{
			close(fd[write_end]);
			read(fd[read_end], read_msg, strlen(read_msg)+1);	
			printf("\nThe message is %s \n",read_msg);
			close(fd[read_end]);
			/*
			fp=fopen(read_msg,"r");		
			i=0;			
			while((ch = fgetc(fp)) != EOF )			
			{
				write_msg[i]=ch;
				i++;
			}
			write(fd2[write_end],write_msg,sizeof(write_msg)+1);		
			close(fd2[write_end]);
			*/
		}
	}		

	return 0;
}
