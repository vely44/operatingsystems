#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile char character = '0';
void myhandle(int sig);

int main(void)
{
	struct sigaction act;
    	
    	long int x = (long)getpid();

	
	memset(&act,'\0',sizeof(act)); // Set act to NULL
    	act.sa_handler = myhandle; // Define the function
    	act.sa_flags = 0; // No flags
    	sigemptyset(&act.sa_mask);// No signal masking

	sigaction(25, &act, NULL);

	printf("PID is:%ld \n",x);

	while(1)
	{
	write(1, &character,1);
	sleep(1);
	}
	return 0;
	
}

void myhandle(int sig)
{
	if(++character > '9')
	{
	character = '0';
	}
}
