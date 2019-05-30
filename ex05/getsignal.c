#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void myhandle(int sig);
 

int main(void)
{
    struct sigaction act;
    int i =0;
    long int x = (long)getpid();
    char y = stroul(x);
    const char msg[] = "0";

    
    
    memset(&act,'\0',sizeof(act));
    act.sa_handler = myhandle;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGINT, &act, NULL);
      
    while(1)
    {

    write(STDOUT_FILENO, msg, sizeof(msg)-1);
    sleep(1);
    }

    return 0;
}


void myhandle(int sig)
{
    printf("Handle with signal %d\n",sig);
}
