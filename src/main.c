#include "operations.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


	
// Will be used to create the readyq array to store multiple types
struct pcb {
	int pid;
	int priority;
	int exec_time;
	char fcn[5];
	int x;
	int y;
};

// Struct for operation results to be printed to user
struct output {
	int pid;
	int result;
};

struct output fifo[10];

// Ready Queue, 10 subarrays
struct pcb readyq[10];

// Declared globally to be accessed by helper functions
char sched_choice[] = "";

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int compare_by_exec(const void *a, const void *b)
{
	struct pcb *pcb_a = (struct pcb *)a;
	struct pcb *pcb_b = (struct pcb *)b;
	
	return pcb_a->exec_time - pcb_b->exec_time;
}

int compare_by_priority(const void *a, const void *b)
{
	struct pcb *pcb_a = (struct pcb *)a;
	struct pcb *pcb_b = (struct pcb *)b;
	
	return pcb_a->priority - pcb_b->priority;
}


void fcfs()
{
	pthread_mutex_lock(&mutex1);
	
	for(int i = 0; i < 10; i++)
	{
		fifo[i].pid = readyq[i].pid;
		
		int x = readyq[i].x;
		int y = readyq[i].y;
		
		if(strcmp(readyq[i].fcn, "fib") == 0)
		{
			fifo[i].result = fib(x);
		}
		else if(strcmp(readyq[i].fcn, "prod") == 0)
		{
			fifo[i].result = prod(x, y);
		}
		else if(strcmp(readyq[i].fcn, "pow") == 0)
		{
			fifo[i].result = power(x, y);
		}
		else if(strcmp(readyq[i].fcn, "sum") == 0)
		{
			fifo[i].result = sum(x, y);
		}
	}
	
	pthread_mutex_unlock(&mutex1);
};

void sjf()
{
	pthread_mutex_lock(&mutex1);
	
	qsort(readyq, 10, sizeof(struct pcb), compare_by_exec);
	
	for(int i = 0; i < 10; i++)
	{
		fifo[i].pid = readyq[i].pid;
		
		int x = readyq[i].x;
		int y = readyq[i].y;
		
		if(strcmp(readyq[i].fcn, "fib") == 0)
		{
			fifo[i].result = fib(x);
		}
		else if(strcmp(readyq[i].fcn, "prod") == 0)
		{
			fifo[i].result = prod(x, y);
		}
		else if(strcmp(readyq[i].fcn, "pow") == 0)
		{
			fifo[i].result = power(x, y);
		}
		else if(strcmp(readyq[i].fcn, "sum") == 0)
		{
			fifo[i].result = sum(x, y);
		}
	}
	
	pthread_mutex_unlock(&mutex1);

}; 



void priority()
{
	pthread_mutex_lock(&mutex1);
	
	qsort(readyq, 10, sizeof(struct pcb), compare_by_priority);
	
	for(int i = 0; i < 10; i++)
	{
		fifo[i].pid = readyq[i].pid;
		
		int x = readyq[i].x;
		int y = readyq[i].y;
		
		if(strcmp(readyq[i].fcn, "fib") == 0)
		{
			fifo[i].result = fib(x);
		}
		else if(strcmp(readyq[i].fcn, "prod") == 0)
		{
			fifo[i].result = prod(x, y);
		}
		else if(strcmp(readyq[i].fcn, "pow") == 0)
		{
			fifo[i].result = power(x, y);
		}
		else if(strcmp(readyq[i].fcn, "sum") == 0)
		{
			fifo[i].result = sum(x, y);
		}
	}
	
	pthread_mutex_unlock(&mutex1);
	
}; 
// End of sched alg func declarations


   
// May need to clean this up a bit
void *sched_disp_func()
{
	if(strcmp(sched_choice, "fcfs") == 0)
	{
		fcfs();
	}
	else if(strcmp(sched_choice, "sjf") == 0)
	{
		sjf();
	}
	else if(strcmp(sched_choice, "priority") == 0)
	{
		priority();
	}
	
	pthread_exit(0);
};


/*
	Logger will write contents of fifo to the output file, 
	for this function a ptr to the output file needs to be passed in
*/
void *logger_func()
{
	
	pthread_mutex_lock(&mutex1);
	for(int i = 0; i < 10; i++)
	{
		printf("PID: %d, Result: %d\n", fifo[i].pid, fifo[i].result);
	}
	pthread_mutex_unlock(&mutex1);
	
	
	pthread_exit(0);
};


/* 
argv are the arguments entered into the cmd line 
we can access them by index arg[3], arg[2].. etc

Order in which arguments are entered is important
for accessing the correct ones
*/
int main(int argc, char *argv[]) {
	
	strcpy(sched_choice, argv[1]);
	
   // argv[2] is the input file
	FILE* ptr;
	ptr = fopen(argv[2], "r");
   
	int buflen = 50;
	char buffer[buflen]; 
	
	// iterator for readyq
	int i = 0; 


   //Populating the ready queue
   	while(fgets(buffer, buflen, ptr) && i < 10)
	{ 
		
		// Values to be placed in the struct, need to be type casted first
		char pid[3] = "";
		char priority[3] = "";
		char exec_time[3] = "";
		char fcn[5] = "";
		char x[5] = "";
		char y[5] = "";
	
		// comma counter. each comma reps a new element in the pcb
		int c_cnt = 0;
		
		// target comma value for comparison 
		char cma = ',';
		
		// iterator for buffer line
		int j = 0;
		
		int line_sz = strlen(buffer);
		
		// iterate over the current line of the buffer
		while (j < line_sz)
		{
	
			if(buffer[j] == cma)
			{
				c_cnt++;
				j++;
			} 
			
			if(c_cnt == 0) // parsing the pid
			{
				int idx = 0;
				
				while(buffer[j] != cma)
				{
					pid[idx++] = buffer[j++];
				}
				pid[strlen(pid)] = '\0';
			}
			else if(c_cnt == 1) // parsing the priority
			{
				int idx = 0;
				
				while(buffer[j] != cma)
				{
					priority[idx++] = buffer[j++];
				}
				priority[strlen(priority)] = '\0';
					
			}
			else if(c_cnt == 2) // parsing the execution time
			{
				int idx = 0;
				
				while(buffer[j] != cma)
				{
					exec_time[idx++] = buffer[j++];
				}
				exec_time[strlen(exec_time)] = '\0';
			}
			else if(c_cnt == 3) // parsing the fcn
			{
				int idx = 0;
				
				while(buffer[j] != cma)
				{
					fcn[idx++] = buffer[j++];
				}
				fcn[strlen(fcn)] = '\0';
			}
			else if(c_cnt == 4) // parsing operand 1
			{	
				int idx = 0;
				
				while(buffer[j] != cma)
				{
					x[idx++] = buffer[j++];
				}
				x[strlen(x)] = '\0';
			}
			else if(c_cnt == 5) // parsing operand 2
			{		
				int idx = 0;
				
				while(buffer[j] != cma && j < line_sz)
				{
					y[idx++] = buffer[j++];
				}
				y[strlen(x)] = '\0';
			}
						
		} // end of iterating buffer current line

		
		// Add pcb values from current line to the struct readyq
		readyq[i].pid = atoi(pid);
		readyq[i].priority = atoi(priority);
		readyq[i].exec_time = atoi(exec_time);
		strcpy(readyq[i].fcn, fcn);
		readyq[i].x = atoi(x);
		readyq[i].y = atoi(y);
		
		i++;	 	
	}
	 
	fclose(ptr);
	
	
	//Creation of needed threads
	pthread_t sched_disp, logger;
	
	//Creation of scheddisp thread passes in cmd line argument for chosen sched policy 
	pthread_create(&sched_disp, NULL, &sched_disp_func, NULL);
	
	//Creation of logger thread passes in cmd line argument for ouput file
	pthread_create(&logger, NULL, &logger_func, NULL);
	
	
	// pthread_join(sched_disp, NULL);
	pthread_join(sched_disp, NULL);
	pthread_join(logger, NULL);
	
	
	
	
   return 0;
}
