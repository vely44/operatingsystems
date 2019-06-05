
#include <unistd.h>  // read(), write()
#include <ctype.h>   // toupper()
#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#define ESC 0x1B
int main(void){
	char letter;
	int pipe1[2];
	int pipe2[2];

	//Start pipes
	int x = pipe(pipe1);
	int y = pipe(pipe2);

	if (x==-1){
	perror("pipe");
	exit(1);
	}

	if (y==-1){
	perror("pipe");
	exit(1);
	}

	//fork a kid
	switch(fork()){
	case -1:
		perror("fork");
		exit(1);
	case 0: // Kid 
		close(pipe1[1]);//NOT USED END
		close(pipe2[0]);//NOT USED END
		
		//Do filter.c with the _letter
		//
		dup2(pipe1[0],0);//open pipe1 output (read)//read(pipe1[0],teleported_letter,1);
		dup2(pipe2[1],1);//open pipe2 input (write)//write(pipe2[1],new_letter,1);
		
		close(pipe1[0]);//close output USED END
		close(pipe2[1]);//close input USED END	
		execlp("./filter","filter",(char *) NULL);
		perror("execlp");
		exit(1);
		break;

	default:// Parent 
		
		close(pipe1[0]);//NOT USED END
		close(pipe2[1]);//NOT USED END
			
		while(letter!=ESC)
		{
			read(0,&letter,1);
			write(pipe1[1],&letter,1);//Redirect input from stdin (keyboard) to the stdin of filter
			read(pipe2[0],&letter,1);//redirect the stdout from filter to redirect stdout 
			write(1,&letter,1);
		}
		wait(NULL);//the kid...
		close(pipe1[1]);//close input USED END
		close(pipe2[0]);//close output USED END
		break;


		}
	
	return 0;
}

