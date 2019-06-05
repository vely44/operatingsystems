
#include <unistd.h>  // read(), write()
#include <ctype.h>   // toupper()
#include <stdio.h>
#define ESC 0x1B


int main(void){
	char letter, teleported_letter,new_letter,another_letter;
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
		//Redirect input from stdin (keyboard) to the stdin of filter 
		close(pipe1[1]);//NOT USED END
		read(pipe1[0],teleported_letter,1);// open pipe1 output (read)
		close(pipe1[0]);//close output USED END
		printf("Arrived at parent from kid(PIPE1 - WORKING)");
		//Do filter.c with the teleported_letter
		//
		//redirect the stdout from filter to redirect stdout 
		close(pipe2[0]);//NOT USED END
		write(pipe2[1],new_letter,1);//open pipe2 input (write)
		close(pipe2[1]);//close input USED END	
		printf("Send from kid to parent (PIPE2 - WORKING)");
		break;

	default:// Parent 
		//// read first char from stdin
		read(0, &letter, 1);
		//Redirect input from stdin (keyboard) to the stdin of filter
		close(pipe1[0]);//NOT USED END
		write(pipe1[1],letter,1);//open pipe1 input (write)
		close(pipe1[1]);//close input USED END
		printf("Sent from parent to kid(PIPE1 - WORKING)");
		//Wait now? 
		//
		//redirect the stdout from filter to redirect stdout 
		close(pipe2[1]);//NOT USED END
		read(pipe2[0],another_letter,1);// open pipe2 output (read)
		close(pipe2[0]);//close output USED END	
		printf("Arrived at parrent from kid(PIPE2 - WORKING)");

		wait(NULL);//the kid...



	
	while(letter!=ESC){
	


	

	

	read(0, &letter, 1); //read next char
	}
	return 0;
}

