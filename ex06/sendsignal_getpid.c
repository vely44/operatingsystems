#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> //open()


int main(void)
{
	int file;
	int x; //PID
	
	file=open("PIDpipe",O_RDONLY); 
	read(file, &x, sizeof(x));
	close(file);
	
	while(1)
	{
	sleep(3);
	
	kill(x,25);//kill signal(25) to process x
	}
}
