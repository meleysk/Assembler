 // Name: Meley Kifleyesus


//given a .asm file, the program producs the symbol table(.sym), object code(.obj) if there are no errors
//and an error file(.err) if errors are found.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "structdef.h"
#include "globals.h" 
#include "prototypes.h"  

 int main(int argc, char* argv[])
	{
	
	char inStr[IN_LEN]; // to hold the input file name
	char inStr1[IN_LEN]; // to hold copy of the input file name
	char inStr2[IN_LEN]; // to hold copy of the input file name
	int length; //to store the length of the input string
	char objStr[IN_LEN]; //to hold the input string with .obj extension
	char errStr[IN_LEN]; //to hold the input string with .err extension
	char symStr[IN_LEN]; //to hold the input string with .sym extension
	int c='.';
	char* ptr; //pointer to get extension
	int ext; //to be used for extension length

	 
	 //checking for 2 command line arguments
	if(argc!= ARG_NUM)
	 {
	  fprintf(stderr,"usage: p4 inputfile  \n"); //writes error message to stderr if not correct number
	  exit(1); 
	 }
	
	//opening input file for reading
	if ((in_ptr= fopen(argv[INPUT],"r"))==NULL)// if error opening configuration file
	{ 
	 fprintf(stderr, "Could not open file %s for reading.\n", argv[INPUT]); //write error message to stderr
	 exit(1); //stop the program
	}
	
	//CHEKING IF THE INPUT STRING HAS EXTENSION 
 	ptr=strrchr(argv[INPUT],c); //getting the last occurance of '.' if any
 	if(ptr==NULL)//if no '.' occurs
 	{
 	 strcpy(inStr,argv[INPUT]); 
 	}
 	else //here the '.' occurs
 	{
 	 length=strlen(argv[INPUT]); //Getting lengh of original input
 	 ptr=strrchr(argv[INPUT],c); //getting last occurence of '.'
 	 ext=strlen(ptr); //getting length of the extension found
 	 strlcpy(inStr,argv[INPUT],(length-ext+1)); //copy to new string variable without the extension
 	                                            //adding one space at the end for the null character
 	}
	 
	 strcpy(inStr1,inStr); //making a copy to use to create symbol file
	 strcpy(inStr2,inStr); //making a copy to use to create error file
	 
	 //creating the object,symbol and error file names
	 //and storing the returned strings in varibles
	 strcpy(objStr,createObjFile(inStr));
	 strcpy(symStr,createSymFile(inStr1));
	 strcpy(errStr,createErrFile(inStr2));
	 //pass one populates the symbol table and checks errors
  passOne(argv[INPUT]);
  //checks invalid opcode errors and assembles the instruction
  passTwo(argv[INPUT]);
  
  //if error table is not empty, print_errFile(argv[INPUT],errStr);
  if((h==NULL)&&(headM==NULL)&&(headU)==NULL) //here all the error lists are empty,no need for error file
  {
  	print_symFile(symStr); //printing symbol table file
  	print_objFile(objStr); //printing object file
  }
  else// here error lists are not empty so we only print error file
  {
  	print_errFile(errStr);
  }
	return 0;
	}//END MAIN
	
