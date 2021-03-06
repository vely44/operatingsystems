/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

#include <stdlib.h>
#include "syntaxCheck.h"
#include <string.h>


// Test whether an argument is one character long and has the correct value (e,p,w):
ErrCode TestType(char *printMethod) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code
  
    if(*printMethod == 'e')
    fout= NO_ERR;
  else if (*printMethod == 'p')
    fout = NO_ERR;
  else if (*printMethod == 'w')
    fout = NO_ERR;
  else
    fout = ERR_TYPE;

  return fout;
}


// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code
  int x  = atoi(numberOfTimes);
  if(x <= 0)
    {
      fout = ERR_NR;
    }
  return fout;
 }


// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar) {
  ErrCode fout = NO_ERR;
  
  // Add the missing code

    
  if(strlen(printChar)>1)
    fout=ERR_CHAR;
  
  return fout;
}
