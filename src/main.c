#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <ctype.h>
#include <stdbool.h>




	// Ready Queue
	char ready[15][20] = {0};
	
	
	// Fifo data structure
	char fifo[15][50] = {0};
	
	
	// Temp array just for data manipulation
	char temp[15][50] = {0};
	
	// Cmd line input for sched policy choice
	char polChoice[20] = " ";
	
	// Cmd line input for output file
	char outFile[20] = " ";
	
	
	
	

int prod(int x, int y){
	
	if(x == 0) return 0;
	
	int prod = 1;
	
	for(int i = x; i <= y; i++)
	{
			prod *= i; 
	}
	
	return prod;

}


int fib(int x, int y){
	if(y <= 1)
	{
		return 1;
	}
	
	return fib(x, y - 1) + fib(x, y - 2);
}

int power(int x, int y){
	return pow(x,y);
}

int sum(int x, int y){
	return (x+y);
}



// Function pointer array for functions
	int (*comp[4]) (int x, int y) = {sum, power, fib, prod};
	


// Method to remove all occurences of commas
void remove_all_commas(char* str, char c)
{
	char *pr = str, *pw = str;
	while (*pr){
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}




pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// FIFO's send a receive functions
void send(char a[25])
{
	
	
	pthread_mutex_lock(&mutex1);
	
	int n = sizeof(fifo)/sizeof(fifo[0]);
	sprintf(fifo[n], "%s", a);
		
	pthread_mutex_unlock(&mutex1);
	
}

/*
	Writes contents of fifo to the output file
*/
void recv()
{
	pthread_mutex_lock(&mutex1);
	FILE *fp = fopen(outFile, "w+");
	
	fwrite(fifo, sizeof(char), sizeof(fifo), fp);
	fclose(fp);
	pthread_mutex_unlock(&mutex1);
	
	
	
}





// is the first number of the minipcb one digit or two digit?
bool isTwoDigit(char s[])
{
	/* 
		Checks if 2nd char in minipcb is a digit, 
		if yes ..  then the priority number is two digits
	*/
	if(isdigit(s[1]))
	{
		return true;
	}
	else 
		return false;
}


void fcfs()
{
	for(size_t i = 0; i < sizeof(ready) / sizeof(ready[0]); i++)
	{
		char readytemp[25] = "";
		strcpy(readytemp, ready[i]);
		remove_all_commas(readytemp, ',');
		
		char fcn[15] = " ";
		int paramX;
		int paramY;
		
		
		
		// Checks first digit(s) of the minipcb to ensure correct parsing of particular strings
		if(isTwoDigit(readytemp))
		{
			if(readytemp[2] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[2] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}
			else if(readytemp[2] == 'p')
			{
				if(readytemp[3] == 'r')
				{
					strcpy(fcn, "product");
					
				}					
				if(readytemp[3] == 'o')
				{
					strcpy(fcn, "power");
				}
			}
		}
		else
		{
			if(readytemp[1] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[1] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}
			else if(readytemp[1] == 'p')
			{
				if(readytemp[2] == 'r')
				{
					strcpy(fcn, "product");
				}
				else if(readytemp[2] == 'o')
				{
					strcpy(fcn, "power");
				}
			}	
		}
		
		
	/*
		Need to parse input values, figure out which function is being used
		so you know at which index to start iterating for your fcn input values
		
		strcmp function works opposite
		return 0 means strings equal 
		
		Maybe use while loop to iterate after the fcn name, 
		count chars to see if 2 digits or 4
		
		For pow function only takes in 2 digits.
	*/
	
		   //Start at last position, iterate backwards, had to do pos - 3 for trailing white space;
			int pos = strlen(readytemp) - 3;
			int j = strlen(readytemp)- 3;
			int count = 0;
			
			
			while(isdigit(readytemp[j]))
			{
				if(count == 4) break;
				count++;
				j--;
			}
			
			if(count == 2)
			{
				char y = readytemp[pos];
				char x = readytemp[pos - 1];
				
				paramY = y - '0';
				paramX = x - '0';
				
				
				
			}
			else if (count == 3)
			{
				/*
					Priority 8 is the only one where the first input is 2 digits
					just hardcode parse it with an if statement
				*/
				
				if(readytemp[0] == '8')
				{
					char y = readytemp[pos];
					
					char x[5] = " ";
					char tmp1 = readytemp[pos-1];
					char tmp2 = readytemp[pos-2];
					strncat(x, &tmp2, 1);
					strncat(x, &tmp1, 1);
					
					paramY = y - '0';
					paramX = atoi(x);
					
				}
				else
				{
					char y[5] = " ";
					char tmp1 = readytemp[pos];
					char tmp2 = readytemp[pos-1];
					strncat(y, &tmp2, 1);
					strncat(y, &tmp1, 1);
					
					
					char x = readytemp[pos-2]; 
					
					paramY = atoi(y);
					paramX = x - '0';
				}
				
			}
			else if (count == 4)
			{
				//concat two digs for x, concat two digts for y
				char y[5] = " ";
				char tmp1 = readytemp[pos];
				char tmp2 = readytemp[pos-1];
				strncat(y, &tmp2, 1);
				strncat(y, &tmp1, 1);
				
				
				
				char x[] = " ";
				char tmp3 = readytemp[pos-2];
				char tmp4 = readytemp[pos-3];
				strncat(x, &tmp4, 1);
				strncat(x, &tmp3, 1);
				
				paramY = atoi(y);
				paramX = atoi(x);
				
				
			}
			
			
		
		/*
			Remember to typecast your input variables char -> int 
			After the variables have been resolved we'll just use the send()
			method to put each data set directly into the fifo.
			
			Since this is fcfs, each mini pcb can just be processed one after 
			the other
		/*
		
		/*
			Below is where a set a variable equal to the neccesary function call
			and prepare the data set to be shipped off by the the send() method 
		*/
		
		
		
		int result;
		
		if(strcmp(fcn, "sum") == 0)
		{
			result = (*comp[0]) (paramX, paramY);
		}
		else if(strcmp(fcn, "power") == 0)
		{
			result = (*comp[1]) (paramX, paramY);
		}
		else if(strcmp(fcn, "fibonacci") == 0)
		{
			result = (*comp[2]) (paramX, paramY);
		}
		else if(strcmp(fcn, "product") == 0)
		{
			result = (*comp[3]) (paramX, paramY);
		}
		
		
		char finalOut[40] = " "; 
		char finalOut2[] = " Result is: ";
		char finalRes[5] = " ";
		
		sprintf(finalRes, "%i", result);
		
		strcat(finalOut, ready[i]);
		strcat(finalOut, finalOut2);
		strcat(finalOut, finalRes);
		
		
		
		send(finalOut);
		
	//End of foor loop		
	}
	

	
}



/*
	Hardcoded sort algorithm to properly parse/order strings by burst times
*/
void mySJFSort()
{
	//p11
	strcpy(temp[0], ready[10]);
	//p3
	strcpy(temp[1], ready[2]);
	//p8
	strcpy(temp[2], ready[7]);
	//p12
	strcpy(temp[3], ready[11]);
	//p2
	strcpy(temp[4], ready[1]);
	//p15
	strcpy(temp[5], ready[14]);
	//p1
	strcpy(temp[6], ready[0]);
	//p5
	strcpy(temp[7], ready[4]);
	//p4
	strcpy(temp[8], ready[3]);
	//p7
	strcpy(temp[9], ready[6]);
	//p13
	strcpy(temp[10], ready[12]);
	//p14
	strcpy(temp[11], ready[13]);
	//p6
	strcpy(temp[12], ready[5]);
	//p9
	strcpy(temp[13], ready[8]);
	//p10
	strcpy(temp[14], ready[9]);
	
}
void sjf()
{
	mySJFSort();
	
	for(size_t i = 0; i < sizeof(temp) / sizeof(temp[0]); i++)
	{
		char readytemp[25] = "";
		strcpy(readytemp, temp[i]);
		remove_all_commas(readytemp, ',');
		
		char fcn[15] = " ";
		int paramX;
		int paramY;
		
		
		
		int c = 0;
		int p = 0;
		size_t k = 0;
		while(isdigit(readytemp[p]))
		{
			if(c == 4) break;
			
			c++;
			p++;
		}
		
		if(c == 2)
		{
			if(readytemp[2] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[2] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[2] == 'p')
			{
				if(readytemp[3] == 'o')
				{
					strcpy(fcn, "power");
				}
				if(readytemp[3] == 'r')
				{
					strcpy(fcn, "product");
				}
			}
		}
		if(c == 3)
		{
			if(readytemp[3] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[3] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[3] == 'p')
			{
				if(readytemp[4] == 'o')
				{
					strcpy(fcn, "power");
				}					
				if(readytemp[4] == 'r') 
				{
					strcpy(fcn, "product");
				}
			}
		}
		if(c == 4)
		{
			if(readytemp[4] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[4] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[4] == 'p')
			{
				if(readytemp[5] == 'o')
				{
					strcpy(fcn, "power");
				}					
				if(readytemp[5] == 'r')
				{
					strcpy(fcn, "product");	
				}					
			}
		}
		
		
	/*
		Need to parse input values, figure out which function is being used
		so you know at which index to start iterating for your fcn input values
		
		strcmp function works opposite
		return 0 means strings equal 
		
		Maybe use while loop to iterate after the fcn name, 
		count chars to see if 2 digits or 4
		
		For pow function only takes in 2 digits.
	*/
	
		//Start at last position, iterate backwards
			int pos = strlen(readytemp) - 3;
			int j = strlen(readytemp) - 3;
			int count = 0;
			
			while(isdigit(readytemp[j]))
			{
				if(count == 4) break;
				
				count++;
				j--;
			}
			
			if(count == 2)
			{
				char y = readytemp[pos];
				char x = readytemp[pos - 1];
				
				paramY = y - '0';
				paramX = x - '0';
			}
			else if (count == 3)
			{
				/*
					Process 8 is the only one where the first input is 2 digits
					just hardcode parse it with an if statement
				*/
				
				if(readytemp[0] == '8')
				{
					char y = readytemp[pos];
					
					char x[5] = " ";
					char tmp1 = readytemp[pos-1];
					char tmp2 = readytemp[pos-2];
					strncat(x, &tmp2, 1);
					strncat(x, &tmp1, 1);
					
					paramY = y - '0';
					paramX = atoi(x);
					
				}
				else
				{
					char y[5] = " ";
					char tmp1 = readytemp[pos];
					char tmp2 = readytemp[pos-1];
					strncat(y, &tmp2, 1);
					strncat(y, &tmp1, 1);
					
					
					char x = readytemp[pos-2]; 
					
					paramY = atoi(y);
					paramX = x - '0';
				}
				
			}
			else if (count == 4)
			{
				//concat two digs for x, concat two digts for y
				char y[5] = " ";
				char tmp1 = readytemp[pos];
				char tmp2 = readytemp[pos-1];
				strncat(y, &tmp2, 1);
				strncat(y, &tmp1, 1);
				
				
				
				char x[5] = " ";
				char tmp3 = readytemp[pos-2];
				char tmp4 = readytemp[pos-3];
				strncat(x, &tmp4, 1);
				strncat(x, &tmp3, 1);
				
				paramY = atoi(y);
				paramX = atoi(x);
				
				
			}
			
			
		int result;
		
		if(strcmp(fcn, "sum") == 0)
		{
			result = (*comp[0]) (paramX, paramY);
		}
		else if(strcmp(fcn, "power") == 0)
		{
			result = (*comp[1]) (paramX, paramY);
		}
		else if(strcmp(fcn, "fibonacci") == 0)
		{
			result = (*comp[2]) (paramX, paramY);
		}
		else if(strcmp(fcn, "product") == 0)
		{
			result = (*comp[3]) (paramX, paramY);
		}
		
		char finalOut[40] = " "; 
		char finalOut2[] = " Result is: ";
		char finalRes[5] = " ";
		
		sprintf(finalRes, "%i", result);
		
		strcat(finalOut, temp[i]);
		strcat(finalOut, finalOut2);
		strcat(finalOut, finalRes);
		
		
		
		send(finalOut);
		
	//End of foor loop		

	}
	
}


void myPrioritySort()
{
	//p12
	strcpy(temp[0], ready[11]);
	//p11
	strcpy(temp[1], ready[10]);
	//p1
	strcpy(temp[2], ready[0]);
	//p10
	strcpy(temp[3], ready[9]);
	//p15
	strcpy(temp[4], ready[14]);
	//p9
	strcpy(temp[5], ready[8]);
	//p8
	strcpy(temp[6], ready[7]);
	//p6
	strcpy(temp[7], ready[5]);
	//p3
	strcpy(temp[8], ready[2]);
	//p2
	strcpy(temp[9], ready[1]);
	//p7
	strcpy(temp[10], ready[6]);
	//p5
	strcpy(temp[11], ready[4]);
	//p14
	strcpy(temp[12], ready[13]);
	//p13
	strcpy(temp[13], ready[12]);
	//p4
	strcpy(temp[14], ready[3]);
		
}



void priority()
{
	myPrioritySort();
	
	for(size_t i = 0; i < sizeof(temp) / sizeof(temp[0]); i++)
	{
		char readytemp[25] = "";
		strcpy(readytemp, temp[i]);
		remove_all_commas(readytemp, ',');
		
		char fcn[15] = " ";
		int paramX;
		int paramY;
		
		
		
		int c = 0;
		int p = 0;
		int k = 0;
		while(isdigit(readytemp[p]))
		{
			if(c == 4) break;
			
			c++;
			p++;
		}
		
		if(c == 2)
		{
			if(readytemp[2] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[2] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[2] == 'p')
			{
				if(readytemp[3] == 'o')
				{
					strcpy(fcn, "power");
				}
				if(readytemp[3] == 'r')
				{
					strcpy(fcn, "product");
				}
			}
		}
		if(c == 3)
		{
			if(readytemp[3] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[3] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[3] == 'p')
			{
				if(readytemp[4] == 'o')
				{
					strcpy(fcn, "power");
				}					
				if(readytemp[4] == 'r') 
				{
					strcpy(fcn, "product");
				}
			}
		}
		if(c == 4)
		{
			if(readytemp[4] == 'f')
			{
				strcpy(fcn, "fibonacci");
			}	
			else if(readytemp[4] == 's')
			{
				strcpy(fcn, "sum");
			}
			else if(readytemp[4] == 'p')
			{
				if(readytemp[5] == 'o')
				{
					strcpy(fcn, "power");
				}					
				if(readytemp[5] == 'r')
				{
					strcpy(fcn, "product");	
				}					
			}
		}
		
		
	/*
		Need to parse input values, figure out which function is being used
		so you know at which index to start iterating for your fcn input values
		
		strcmp function works opposite
		return 0 means strings equal 
		
		Maybe use while loop to iterate after the fcn name, 
		count chars to see if 2 digits or 4
		
		For pow function only takes in 2 digits.
	*/
	
		//Start at last position, iterate backwards
			int pos = strlen(readytemp)- 3;
			int j = strlen(readytemp)- 3;
			int count = 0;
			
			while(isdigit(readytemp[j]))
			{
				if(count == 4) break;
				
				count++;
				j--;
			}
			
			if(count == 2)
			{
				char y = readytemp[pos];
				char x = readytemp[pos - 1];
				
				paramY = y - '0';
				paramX = x - '0';
			}
			else if (count == 3)
			{
				/*
					Process 8 is the only one where the first input is 2 digits
					just hardcode parse it with an if statement
				*/
				
				if(readytemp[0] == '8')
				{
					char y = readytemp[pos];
					
					char x[5];
					char tmp1 = readytemp[pos-1];
					char tmp2 = readytemp[pos-2];
					strncat(x, &tmp2, 1);
					strncat(x, &tmp1, 1);
					
					paramY = y - '0';
					paramX = atoi(x);
					
				}
				else
				{
					char y[5];
					char tmp1 = readytemp[pos];
					char tmp2 = readytemp[pos-1];
					strncat(y, &tmp2, 1);
					strncat(y, &tmp1, 1);
					
					
					char x = readytemp[pos-2]; 
					
					paramY = atoi(y);
					paramX = x - '0';
				}
				
			}
			else if (count == 4)
			{
				//concat two digs for x, concat two digts for y
				char y[5];
				char tmp1 = readytemp[pos];
				char tmp2 = readytemp[pos-1];
				strncat(y, &tmp2, 1);
				strncat(y, &tmp1, 1);
				
				
				
				char x[5];
				char tmp3 = readytemp[pos-2];
				char tmp4 = readytemp[pos-3];
				strncat(x, &tmp4, 1);
				strncat(x, &tmp3, 1);
				
				paramY = atoi(y);
				paramX = atoi(x);
				
				
			}
			
			
		int result;
		
		if(strcmp(fcn, "sum") == 0)
		{
			result = (*comp[0]) (paramX, paramY);
		}
		else if(strcmp(fcn, "power") == 0)
		{
			result = (*comp[1]) (paramX, paramY);
		}
		else if(strcmp(fcn, "fibonacci") == 0)
		{
			result = (*comp[2]) (paramX, paramY);
		}
		else if(strcmp(fcn, "product") == 0)
		{
			result = (*comp[3]) (paramX, paramY);
		}
		
		char finalOut[40] = " "; 
		char finalOut2[] = " Result is: ";
		char finalRes[15] = " ";
		
		sprintf(finalRes, "%i", result);
		
		strcat(finalOut, temp[i]);
		strcat(finalOut, finalOut2);
		strcat(finalOut, finalRes);
		
		
		
		
		
		send(finalOut);
		
	//End of foor loop		

	}
	
}



/* 
	Function pointer array for schedulers
	
   */
   
   void (*p[3]) () = {fcfs, sjf, priority};
   
   /*
We're just going to have the sched dispatcher call the sched pol function
each sched pol function will have the send() method inside it

When sched thread is created it'll call the scheddisp func
When logger thread is created it'll call the logger func

For the sched disp, a ptr to the chosen sched pol needs to be passed in

*/
void *sched_disp_func()
{
	if(strcmp(polChoice, "FCFS") == 0)
	{
		(*p[0])();
	}	
	else if(strcmp(polChoice, "SJF") == 0)
	{
		(*p[1])();
	}
	else if(strcmp(polChoice, "PRIORITY") == 0)
	{
		(*p[2])();
	}
	
	pthread_exit(&sched_disp_func);
	
}

/*
	Logger will write contents of fifo to the output file, 
	for this function a ptr to the output file needs to be passed in
*/
void *logger_func()
{
	
	recv();

	
	pthread_exit(&logger);
}


/* 
argv are the arguments entered into the cmd line 
we can access them by index arg[3], arg[2].. etc

Order in which arguments are entered is important
for accessing the correct ones
*/
int main(int argc, char *argv[]) {
   

	sprintf(polChoice, "%s", argv[1]);
	sprintf(outFile, "%s", argv[3]);

   // argv[2] is the input file
   FILE* ptr;
   ptr = fopen(argv[2], "r");
   
   int bufferLength = 255;
   char buffer[bufferLength]; 
   
   int i = 0;
   //Populating the ready queue
   	while(fgets(buffer, bufferLength, ptr))
	{ 
		strcpy(ready[i], buffer);
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
	pthread_join(logger, NULL);
	pthread_join(sched_disp, NULL);
	
	
	
	
  
   return 0;
}
