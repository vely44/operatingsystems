/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include "sys/wait.h"
#include "unistd.h"
#include "displayFunctions.h"
#include "syntaxCheck.h"

int main(int argc, char *argv[]) {
  
  unsigned long int numOfTimes;
  int niceIncr;
  char printMethod, printChar;
  ErrCode err;
  pid_t kid;
  int numofchar = (argc-4);
  err = SyntaxCheck(argc, argv, numofchar);  // Check the command-line parameters
  
    if(err != NO_ERR) {
        DisplayError(err);        // Print an error message
  } else {
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
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
            printChar=argv[iChild+4][0];
            printf("Child No. %d \nWith PID: %d\nPrinting %c \n*started with %d as a nice value \n", iChild+1,getpid(),printChar,iChild*niceIncr);
            if(nice(iChild*niceIncr)==-1)
            {
                perror("nice() - Failed!\n");
            }
            PrintCharacters(printMethod, numOfTimes, printChar);
            printf("\nThe priority of the child with no. %d is %d \n",iChild+1,getpriority(PRIO_PROCESS,getpid()));
            break;

        default:
            break;
        }//Switch End
        

        if(kid==0){break;}
      }//For End
    

    for(int x = 0; x< numofchar;x++)
    {
    wait(NULL);
    }


  }//Else End
  printf("\n");  // Newline at end
  return 0;
}
