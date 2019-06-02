#define _POSIX_C_SOURCE 199309L
#define _XOPEN_SOURCE 500 

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> //mkfifo()
#include <fcntl.h> //open()

volatile char character = '0';
void myhandle(int sig);

int main(void)
{
	struct sigaction act;
    	int file;
    	int x = getpid(); //PID 

	// SHR Setup
	memset(&act,'\0',sizeof(act)); // Set act to NULL
    	act.sa_handler = myhandle; // Define the function
    	act.sa_flags = 0; // No flags
    	sigemptyset(&act.sa_mask);// No signal masking
	//Turn on
	sigaction(25, &act, NULL);
	
	printf("PID is:%d \n",x);
	//FIFO 
	file=open("PIDpipe", O_WRONLY);
	write(file, &x, sizeof(x));
	close(file);

	while(1)
	{
		write(1, &character,1);
		sleep(1);
	}
	return 0;
	
}
//Handle Function
void myhandle(int sig)
{
	if(++character > '9')
	{
		character = '0';
	}
}
