#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t x = atoi(argv[1]);//read argument (PID)
	
	while(1)
	{
	sleep(3);
	
	kill(x,25);//kill signal(25) to process x
	}
}
