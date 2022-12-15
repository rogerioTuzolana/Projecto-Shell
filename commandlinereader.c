/*
// Command line reader (header file), version 3
// Sistemas Operativos, DEI-CC/FC/UAN 2020
// Professor Joao Costa
*/

#include <string.h>
#include <stdio.h>

/* 
Reads up to 'vectorSize' space-separated arguments from the standard input
and saves them in the entries of the 'argVector' argument.
This function returns once enough arguments are read or the end of the line 
is reached

Arguments: 
 'argVector' should be a vector of char* previously allocated with
 as many entries as 'vectorSize'
 'vectorSize' is the size of the above vector. A vector of size N allows up to 
 N-1 arguments to be read; the entry after the last argument is set to NULL.
 'buffer' is a buffer with 'buffersize' bytes, which will be 
 used to hold the strings of each argument.  

Return value:
 The number of arguments that were read, or -1 if some error occurred.
*/
int readLineArguments(char **argVector, int vectorSize, char *buffer)
{
  int numtokens = 0;
  char *s = " \r\n\t";

  int i;

  char *token;

  if (argVector == NULL || vectorSize == 0)
    return 0;

  /*if (fgets(buffer, buffersize, stdin) == NULL) {
    return -1;
  }*/
   
  /* get the first token */
  token = strtok(buffer, s);
   
  /* walk through other tokens */
  while( numtokens < vectorSize-1 && token != NULL ) {
    argVector[numtokens] = token;
    numtokens ++;
    
    token = strtok(NULL, s);
  }
   
  for (i = numtokens; i<vectorSize; i++) {
    argVector[i] = NULL;
  }
   
  return numtokens;
}

