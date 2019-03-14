//  OPS exercise 1: Command-line parameters

// Include the needed header files
#include <stdio.h>    // file IO, perror()
#include <string.h>   // str(n)cpy()
#include <stdbool.h>  // Bool type
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
// Function prototypes:
void print_help();
void read_file(char *fileName, bool lastLine);
void print_env(char* envp[]);


int main(int argc, char* argv[], char* envp[]) {
  // If no arguments are given, print help
  int c;
  int digit_optind = 0;
  // Set up struct option array long_options[]
                 static struct option long_options[] = {
                   {"help",     no_argument, 0, 'h' },
                   {"file",  required_argument,  0,  'f' },
                   {"end",  required_argument, 0,  'e' },
                   {"env", no_argument,       0,  'v' }
               };
  // Scan the different command-line arguments and options

 while(1)
        {
	 int option_index = 0;
	 c = getopt_long(argc, argv, "hf:e:v",
                        long_options, &option_index);
         if (c == -1)
                   break;
	 switch (c) {
               case 'h':
                   printf("option  %s", long_options[option_index].name);
                   print_help();
                   printf("\n");
                   break;

               case 'f':
		   printf("option  %s", long_options[option_index].name);
                   read_file(optarg,0);
                   printf("\n");
                   break;
               case 'e':
		   printf("option  %s", long_options[option_index].name);
		   read_file(optarg,1);
                   printf("\n");
                   break;
               case 'v':
		   printf("option  %s", long_options[option_index].name);
                   print_env(envp);
                   printf("\n");
                   break;
               default:
                   printf("?? getopt returned character code 0%o ??\n", c);
               }
	}

		     
           if (optind < argc) {
               printf("non-option ARGV-elements: ");
               while (optind < argc)
                   printf("%s ", argv[optind++]);
               printf("\n");
           }
		 
		 
  return 0;
}


// Print program help:
void print_help() {
  printf("Available program options:\n\
  -h --help                  Print this help and exit\n\
  -f --file <file name.txt>  Specify a text file and print its FIRST line\n\
  -e --end  <file name.txt>  Specify a text file and print its LAST line\n \
  -v --env                   Print environment variables\n");
}


// Read the input file.  lastLine is 0 or 1, depending on whether the first or last line should be printed:
void read_file(char *fileName, bool lastLine) {
  
  // Verify the file's extension
  char ext[5];
  strncpy(ext, fileName+strlen(fileName)-4,5);  // Get the last 4 characters of the string + \0 !
  if(strcmp(ext,".txt") != 0) {
    fprintf(stderr, "%s:  the input file should be a text file, with the extention '.txt'\n", fileName);
    return;
  }
  
  FILE *inFile = fopen(fileName, "r");  // NOTE: C stdlib fopen() rather than system call open()
  if( inFile  == NULL) {
    perror(fileName);
    return;
  }
  
  int iLine = 0;
  char line[1024], firstLine[1024];
  while( fgets(line, 1024, inFile) != NULL ) {
    iLine++;
    if(iLine==1) strncpy(firstLine, line, 1024);  // Save the first line
  }
  fclose(inFile);
  
  if(lastLine) {
    printf("The last line of the file %s reads:\n%s\n", fileName, line);
  } else {
    printf("The first line of the file %s reads:\n%s\n", fileName, firstLine);
  }
}


// Print environment variables:
void print_env(char* envp[]) {
  
  int nPar = 0;
  printf("print_env():\n");
  
  // Scan and print the different environment variables:
  while(envp[nPar]) {
    printf("%s\n", envp[nPar]);
    nPar++;
  }
  
  printf("\nA total of %i environment variables was found.\n\n", nPar);
}
