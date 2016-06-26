 // Name: Meley Kifleyesus
// NetID: mk198716
// email: meleysennaycollege@gmail.com

//Program 4: Assembler for TMIPS. 
//given a .asm file, the program producs the symbol table(.sym), object code(.obj) if there are no errors
//and an error file(.err) if errors are found.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "structdef.h"
#include "externs.h"
#include "prototypes.h"  

//first pass takes input file as a parameter
//it serches through file and finds and store symbols
//and their lc values to symbol table
//it also perfomrs multiplell symbol definition error check 
void passOne(char* infile)
{
	
	char line[LINE_LEN]; //to store each line
	char tempStr[LABEL_LEN]; //to hold the label/opcode
char tempStr1[LABEL_LEN]; //to copy tempStr
	char* ptr; 
	char opcStr[OP_LEN];
	int n1;
	int n2;
	char c;
	char *nptr; //to be used to get the number from .word opcode
	int length;
	//opening input file for reading
	if ((in_ptr= fopen(infile,"r"))==NULL)// if error opening configuration file
	{ 
	 fprintf(stderr, "Could not open file %s for reading.\n", infile); //write error message to stderr
	 exit(1); //stop the program
	}

			while(fgets(line,LINE_LEN,in_ptr)!=NULL)
			{
				line_num++; //increment line number
		
				if(is_blank(line)==1)//line is blank or comment
				{
					; //do nothing
				}
				
			 else if(is_comment(line)==1)//line is blank or comment
				{
					;//do nothing
					}
				
			else
			{
			//here it is not a line or a comment, so get the first string
			//if its .txt initialize lc,
			//if not .txt checking last occurance of : to check if it is label
			
			//storing the first string in line in temp line
		 sscanf(line,"%s",tempStr);
		//if the string is .text
		if(strcmp(tempStr,".text")==0)
		{
		 //initialize lc
		 lc=0;
	
		}//end if .txt
		else if(strcmp(tempStr,".data")==0)
		{
		 ; //do nothing
		}//end if .data
		else{ //***here it is not .txt or .data so check for label***
			ptr=strchr(tempStr,':'); //check the first occurence of :
			
				if(ptr!=NULL)//here label is found
				{
				 //remove the : from label
				 length=strlen(tempStr); //get the length
				 strlcpy(tempStr1,tempStr,length); //removing the :
				 //check if label is already in the symbol table
				if( search_sym(&(head),tempStr1)==1)//it is found
				{
				//search if it is already in the multiple symbolerror list
				//if it is not found, insert it
				insertSymErr(&(headM),&(tailM),tempStr1);
				}
				else //here it is not found so insert in symbol table
				{
				//insert the symbol and lc value to the linked list
				 insertSym(&(head),&(tail), tempStr1,lc);
				 //store opcode in tempStr
				 sscanf(line,"%s %s",tempStr,opcStr); //getting the optcode
				//incrementing lc
				incr_lc(opcStr,line);
				 
				}//END ELSE 
			}//END LABEL FOUND
			
	  else{ //here there is no label so opcode is stored in tempStr
	  //copying contents of tempStr to opcStr
	  strlcpy(opcStr,tempStr,OP_LEN);
	  
	  //increment lc based on opcode
	  incr_lc(opcStr,line);
			
		 }//END ELSE IF NOT A LABEL
		 }//***end else if not .txt***
		}//END ELSE IF NOT A COMMENT OR BLANK
		}//END WHILE	
}//END PASS ONE

void passTwo(char* infile)
	{
	char line[LINE_LEN]; //to store each line
	char tempStr[LABEL_LEN]; 
 char tempStr1[LABEL_LEN]; 
	char* ptr; 
	char* undefSymErr="Error: Undefined symbol";
	char opcStr[OP_LEN];
	int n1;
	int n2;
	char c;
	char *nptr; //to be used to get the number from .word opcode
	int length;
	char format;
	//char* label;
//	char* mnem
//	char* 
	rewind(in_ptr); //going back to top of infile
	line_num=0; //setting line number back to zero
	lc=0; //resetting lc to 0
		while(fgets(line,LINE_LEN,in_ptr)!=NULL)
			{
				line_num++; //increment line number
		
				if(is_blank(line)==1)//line is blank or comment
				{
					; //do nothing
				}
				
			 else if(is_comment(line)==1)//line is blank or comment
				{
					;//do nothing
					}
				
			else
			{
			//here it is not a line or a comment, so get the first string
			//if its .txt initialize lc,
			//if not .txt checking last occurance of : to check if it is label
			
			//storing the first string in line in temp line
		 sscanf(line,"%s",tempStr);
		//if the string is .text
		if(strcmp(tempStr,".text")==0)
		{
	  lc=0;
		}//end if .txt
		else{ //***here it is not .txt so check for label***
			ptr=strchr(tempStr,':'); //check the first occurence of :
			
				if(ptr!=NULL)//here label is found
				{
				 //remove the : from label
				 length=strlen(tempStr); //get the length
				 strlcpy(tempStr1,tempStr,length); //removing the :
				 //check if label is already in the symbol table
				if( search_sym(&(head),tempStr1)==1)//it is found so get instruction to be asesmbled
				{
			  //get the instruction format
			  sscanf(line,"%s %s",tempStr,opcStr);
			  
			  format=check_format(opcStr);
			  
			  //assemble based on the format type
			  if(format=='R')
			  {
			  
			  check_mnemRL(opcStr,line);
		   lc++; //incrementin lc
			  }//end if R
			  else if(format=='J')
			  {
			  
			  check_mnemJL(opcStr,line);
			  lc++;
			   
			  }//end if J
			  else if (format== 'I')
			  {
			  
			  check_mnemIL(opcStr,line);
			  lc++;
			  }//end if I
			  else//here it is neither one of instructions so it is a directive
			  {
			  //
			  
			  check_directive(opcStr,line);
			  }//end else
				 
				}
				else //here it is not found report undefined symbol error
				{
				//insert the symbol in the undefined symbols list
				insertSymErr(&(headU),&(tailU),tempStr1);//
				 
				}//END ELSE
				 
				
			}//END LABEL FOUND
			
	  else{ //here there is no label so opcode is stored in tempStr
	  //copying contents of tempStr to opcStr
	  strlcpy(opcStr,tempStr,OP_LEN);
	  
	  format=check_format(opcStr);
			  //assemble based on the format type
			  if(format=='R')
			  {
			  
			  check_mnemR(opcStr,line);
			  lc++;
			  }//end if R
			  else if(format=='J')
			  {
			 
			  check_mnemJ(opcStr,line);
			   lc++;
			  }//end if J
			  else if (format== 'I')
			  {
			  
			  check_mnemI(opcStr,line);
			   lc++;
			  }//end if I
			  else
			  {
			   ;
			  }//end else
			  //TEST	
			  
		 }//END ELSE IF NOT A LABEL
		 
		 }//***end else if not .txt***
		}//END ELSE IF NOT A COMMENT OR BLANK
		}//END WHILE
	
	}//END PASSTWO
	

