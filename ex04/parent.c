#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "sys/wait.h"
#include "unistd.h"
#include "displayFunctions.h"


int main(int argc, char *argv[]) {
  
  int niceIncr;
  ErrCode err;
  pid_t kid;
  int numofchar = (argc-4);
  err = SyntaxCheck(argc, argv, numofchar);  // Check the command-line parameters
  
  if(err != NO_ERR) {
        DisplayError(err);        // Print an error message
  } else {

    niceIncr = strtoul(argv[3], NULL, 10); // String to unsigned long
    printf("No. of Input Characters: %d\n", numofchar);

    for(int iChild=0;iChild<numofchar;iChild++)
      {
        kid = fork();
        
        switch(kid){
        case -1:
            perror("fork() - Failed\n");
            perror("No Child Created\n");
            exit(1);
            break;

        case 0:
            setpriority(PRIO_PROCESS,getpid(),(niceIncr*iChild));
            printf("The Child with No.%d has %d priority\n",iChild,getpriority(PRIO_PROCESS,getpid()));
            execl("../ex02/display","display",argv[1],argv[2],argv[4+iChild],(char*)NULL);
            perror("Child Failed");
            exit(1);

        default:
            break;
        }
      }
      for (int i=0;i<numofchar;i++)
      {
          wait(NULL);
      }
      printf("All the children processes are done.\n");
  }
  printf("\n");
  return 0;
}
