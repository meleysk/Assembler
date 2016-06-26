// Name: Meley Kifleyesus


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

//inc _lc takes the opcode and line as inputs 
// process and increment the lc based on opcode
void incr_lc(char* opc , char* line)
{
int n1;
int n2;
char* nptr; //pointer to read for strrchr

				if(searchArray(opc)!=(-1)) //optcode found
				{
				//increment LC
		 		lc++;
				}
	 	else if(strcmp(opc,".data")==0)
		 {
				; //do nothing
			}
		
		 else if(strcmp(opc,".resw")==0) 
		 {
		  //increment lc
		  sscanf(line,"%d", &n1);
		  lc=lc+n1;
		 }
		else if(strcmp(opc,".word")==0)
		 {
		 //get number of words specified 
		 //and add to lc
		  nptr= strrchr(line,':');//pointer to the last occurence of :
			 n2=atoi(nptr+1); //getting the number without the :
		 	lc=lc+n2; //add to lc the number specified
		 }
		 
		else 
		 {
		 	//insert error to opcode error
			insertErr(&(h),&(t),invalOpErr,line_num);
		 	} 
}//END INC_LC

//function to check if a line is blank
int is_blank(char *line)
{
 	int i=0;
 //if the first character is a new line then it is a blank line
 	if(line[0]=='\n')
 	{
 		return 1;
 	}
 	else{//here the first char is not a new line
 
 	while(i<LINE_LEN)
 	{
 	 if(line[i]==' '|| line[i]=='\t')//if  character at index i is new line,
 	 { 
 		 i++;  //increment and check each char till the end of line
  	} 
  //here it is a blank line
  	else 
  	{   //if encountered a non blank character
  	return 0;  //return 0
  	}//end else
 }//end while
 return 1;
}//end big else
} //end is_blank

//function to check if a line is comment
int is_comment(char* line)
{
int i=0;
	//get the first occurence of # 
	while(i<LINE_LEN)
	{
	 if(line[i]==' ') //if blank character
	 {
	  i++; 
	 }
	 else
	 {
	  if(line[i]=='#')//its a comment line
	  {
	  return 1;
	  } 
	  return 0; //her its not a comment so return false
	 }
	 
	}
return 0;
}//end is comment
	
	//FUNCTION TO SEARCH AN ARRAY
//takes a string parameter
//returns 1 if found and 0 if not found
int searchArray(char* str)
	{
	int i;
	
	 for(i=0;i<NUM_OPCODES;i++)
	 {
	 	if(strcmp(str,opcodes[i])==0)// opcode found
	 	{
	 	 
	 	 return i;
	 	}
	 }
	 return (-1);
	}//END SERCH ARRAY
	
 //FUNCTION TO INSERT NODES TO LIST
 // IT TAKES HEAD AND TAIL POINTERS, AND STRING AND LC VALUE TO BE INSERTED
	void insertSym(symNode** head,symNode**tail,char* str, int lc)
{
	symNode *temp;
	temp = (symNode*)malloc(sizeof(symNode));
	//Copy the value of string into the node and insert the node into it appropriate place 
	strcpy((temp)->label,str);
	(temp->address)= lc; //copying address 
	(temp->next) = NULL;
	
	if(*head == NULL)
	{
		//list is currently empty
		*head = *tail = temp;
		
	}	
	else
	{//the list is not empty. 			
		//add the node to the end of the list, 
		(*tail)->next = temp;
		*tail = (*tail)->next;
		
	}

}//END INSERT

//INSERT FOR ERROR ST
//takes head and tail of error list, 
//message to be inserted and line number wher error is
 void insertErr(errNode** head,errNode** tail,char* msg, int ln)
 {
 errNode *temp;
	temp = (errNode*)malloc(sizeof(errNode));
	//Copy the value of string into the node and insert the node into it appropriate place 
	strcpy((temp)->message,msg);
	(temp->line)= ln; //copying address 
	(temp->next) = NULL;
	
	if(*head == NULL)
	{
		//list is currently empty
		*head = *tail = temp;
		
	}	
	else
	{//the list is not empty. 			
		//add the node to the end of the list, 
		(*tail)->next = temp;
		*tail = (*tail)->next;
		
	}

 }//END INSERT ERR
 
 //insert for symbol table errors
 //takes, head, tail and symbol to be inserted
void insertSymErr(serrNode** head,serrNode**tail, char* sym)
{
 serrNode *temp;
	temp = (serrNode*)malloc(sizeof(serrNode));
	//Copy the value of string into the node and insert the node into it appropriate place 
	strcpy((temp)->symbol,sym);
	(temp->next) = NULL;
	
	if(*head == NULL)
	{
		//list is currently empty
		*head = *tail = temp;
		
	}	
	else
	{//the list is not empty. 			
		//add the node to the end of the list, 
		(*tail)->next = temp;
		*tail = (*tail)->next;
		
	}

}//END insertSymErr

//function that searches the symbol table
//takes head of list and string to be found
//if found returns 1, if not returns 0
int search_sym(symNode **head, char* str){
	symNode* head2;
	head2=*head;
	while (head2 != NULL) {
		if (strcmp((head2)->label, str) ==0)//string is found
			return 1;
		head2 = head2->next;
	} 
	/*here, there is no node with the string*/
	return 0;
} /*end of search_list*/

//print the linked list
//takes head of list as parameter
void print_sym(symNode** head){
	if(*head == NULL){
		printf("No symbol\n");
	}
	else{
		
		while ((*head) != NULL){
			fprintf(sym_ptr,"%s\t %d \n",(*head)->label, (*head)->address);//CHANGE TO FPRINTF!!!!
			*head = (*head)->next; 
		}
	}
}//end print

//takes head of the error list as parameter
//prints opcode error messages and lines
void print_err(errNode** head)
{
if(*head == NULL){
		printf("No errors\n");
	}
	else{
		//printf("Symbols in the list and their respective counts: \n");
		while ((*head) != NULL){
			fprintf(err_ptr,"line:%d\t %s \n",(*head)->line,(*head)->message );
 			*head = (*head)->next; 
		}
	}
}//END PRINT ERR

//function that prints symbol error lists to file
//takes the head of error list as parameter
void print_symErr(serrNode** head)
{
if(*head == NULL){
		printf("No errors\n");
	}
	else{
		//printf("Symbols in the list and their respective counts: \n");
		while ((*head) != NULL)
		{
			fprintf(err_ptr,"%s \n",(*head)->symbol);
 			*head = (*head)->next; 
		}
	}
	
}//END PRINT_SYMERR
	
//function that takes string input file name as a parameter
//and returns the string  with .obj extension attached
	char*  createObjFile(char* str)
	{
	 strcat(str, ".obj");
	 return str;
	}//END CREATE OBJFILE
	
 //function that creates file with .sym extension
 //takes string input file name as parameter
//returns the string with attached .sym      
	char*  createSymFile(char* str)
	{
	 strcat(str, ".sym");
	 return str;
	}//END CREATE SYMFILE

     //function that takes string input file name as a parameter
     //returns the string with .err extention attached	
	char*  createErrFile(char* str)
	{
	 strcat(str, ".err");
	 return str;
	}//END CREATE OBJECT
	
	//FUNCTION THAT CHECKS THE FORMAT OF INSTRUCTION
	// TAKES MNEMONIC FOR PARAMETER AND RETURNS THE FORMAT CHARACTEr
		char check_format(char* mnem)
	{
			int opc;
			char c;
	//serchArray returns the numberic opcode of the given instruction
	 opc=searchArray(mnem);
		
		if(opc >=0 && opc <= MAX_R)
		{
		 c='R';
		}
	 else if((opc>MAX_R) && (opc<=MAX_I))
		{
		c='I';
		
		}
		else if((opc>MAX_I) && (opc <=MAX_J))
		{
		c='J';
		}
		else
		{
		c=' ';
		//	return ' '; //here it is not found in the  array so return empty
		}
		return c;
	}//END CHECK_FORMAT

//function that takes the input file name and error file name as parameters
//prints each lines in the input file followed by the error lists to the error file	
void print_errFile(char* errfile)
{
char line[LINE_LEN];
char errDet[]="Errors detected:";
char mulSym[]="Multiply defined symbol(s):";
char undfSym[]= "Undefined symbol(s):";

//opening error file for writing
	if ((err_ptr= fopen(errfile,"w"))==NULL)// if error opening  file
	{ 
	 fprintf(stderr, "Could not open file %s for reading.\n", errfile); //write error message to stderr
	 exit(1); //stop the program
	}
	rewind(in_ptr); //pointer set back to top of input file
	
	//copy each line of input file to error file
		while(fgets(line,LINE_LEN,in_ptr)!=NULL)
		{
	 fprintf(err_ptr,"%s\n",line);

		}
		//print errors
		
		if(h!=NULL)// if there is illegal opcode error
		{
		fprintf(err_ptr,"%s\n",errDet);
		print_err(&h); //printing illegal opcode error list
		}
		//if Multiple definition error exists
		if(headM!=NULL)
		{
		fprintf(err_ptr,"%s\n",mulSym);
		print_symErr(&headM); //printing multiply defined symbols
		}
		//if undefined symbol exists
		if(headU!=NULL)
		{
		fprintf(err_ptr, "%s\n",undfSym);//print message
		print_symErr(&headU); //printing undefined symbol errors list
		}
}//end print_errFile

//function that takes the objectfile name as parameter
// and prints the assembled object code to the objfile
void print_objFile(char* objfile)
{
int i;

//opening object file for writing
	if ((obj_ptr= fopen(objfile,"w"))==NULL)// if error opening  file
	{ 
	 fprintf(stderr, "Could not open file %s for reading.\n", objfile); //write error message to stderr
	 exit(1); //stop the program
	}
 
 //serch the memory array and print only the indexes with instructions in them
 //the index is also the lc value so once instruction is found print its index first
 for(i=0;i<MAX_MEM;i++)
 {
 if(mem[i]==0)//array at index i is empty
 {
 	;
 }
 else //here its not empty so print it
 {
 fprintf(obj_ptr,"%x\t %x\n",i,mem[i]);

 }
}

}

//takes symbol file name as parameter
//prints the symbol table to the symbol file
void print_symFile(char* symFile)
{
if ((sym_ptr= fopen(symFile,"w"))==NULL)// if error opening  file
	{ 
	 fprintf(stderr, "Could not open file %s for reading.\n", symFile); //write error message to stderr
	 exit(1); //stop the program
	}
 //calling the print symbol method
 print_sym(&head);

}
	
//function that checks the R format mnemonics in a line that has a label
//it takes the mnemonic string and line as parameters
//it parses the line to its components 
void	check_mnemRL(char* mnem,char* line)
{
char* rs1; //register 1
char* rs2; //register2
char* rt; //target register
char* sa; //shift amout
int opc; //this is the decimal value of opcode
char* label; //to store label
char* str;
//firrst get the decimal opcode of themnemonic
opc=searchArray(mnem); //this will return the decimal opcde value

if(strcmp(mnem,"hlt")==0)
{//hlt instruction has no operands
	assemble_R(opc,0,0,0,0); //all arguments are 0 
}
else if((strcmp(mnem,"jr")==0)||(strcmp(mnem,"rdr")==0)||(strcmp(mnem,"prr")==0)||(strcmp(mnem,"prh")==0))
{// all have 1 operand rt
 label= strtok(line,":");//getting label
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," $\t\n"); //getting rt
 assemble_R(opc,0,0,atoi(rt),0);
	
}
else if((strcmp(mnem,"move")==0)||(strcmp(mnem,"com")==0))
{ //each have two operands
  label= strtok(line,":");//getting label
 
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL," $\t\n"); //first register
  assemble_R(opc,atoi(rs1),0,atoi(rt),0);
}
else if((strcmp(mnem,"sll")==0)||(strcmp(mnem,"srl")==0)||(strcmp(mnem,"sra")==0))
{// all have 3 operands
	//get operands
	label= strtok(line,":");//getting label
	 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL,"$,"); //first register
 sa= strtok(NULL," \t\n"); //getting shift amount
	assemble_R(opc,atoi(rs1),0,atoi(rt),atoi(sa));
}
else //here the instruction is one of add,sub,mul,div,mod,and,or,xor
{// 3 register operands
 //get operands
 label= strtok(line,":");//getting label
  str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL,"$,"); //first register
 rs2= strtok(NULL," $\t\n"); //getting second register
 assemble_R(opc,atoi(rs1),atoi(rs2),atoi(rt),0);
}

}//END CHECK_MNEMRL

//checks J format mnem in a line that has a label
//mnemonic name and line as parameters
//parses line based on mnemonic name

void check_mnemJL(char* mnem,char* line)
{
	int opc;
	char* rs;
	char* rt;
	char* symbol;
	int lc_val; //to store the lc value of the specified label
	char undefErr[]="Undefined symbol";
	char* label; //to store label
char* str;

 opc=searchArray(mnem); //this will return the decimal opcde value

 if((strcmp(mnem,"j")==0)||(strcmp(mnem,"jal")==0))
	{// all have 1 operand symbol
 	label= strtok(line,":");//getting label
 	str= strtok(NULL," \t"); //getting the mnemonic strig
 	symbol= strtok(NULL," \t\n"); //getting symbol
 	lc_val=get_lc((head),symbol); //getting lc value
 
 if (lc_val==(-1)) //here symbol was not found
 {
 	//inser to undefined error list
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {
 assemble_J(opc,0,0,lc_val);
 }
}//end if j, jal
	else if((strcmp(mnem,"lwa")==0)||(strcmp(mnem,"swa")==0))
{// all have 2 operands rt and symbol
 label= strtok(line,":");//getting label
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," $\t,"); //getting rt
 symbol= strtok(NULL," \t\n"); 
 lc_val=get_lc((head),symbol); //getting lc value
 
 if (lc_val==(-1)) //here symbol was not found
 {
 	//insert the symbol to undefined symbol error list
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {
 assemble_J(opc,0,atoi(rt),lc_val);
 }
	
}//end else if lwa, swa
else //here mnemonic is one of jeq, jne jlt,jle,jgt,jge
{//have 3 operands rt, rs and symbol

 label= strtok(line,":");//getting label
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs= strtok(NULL, "$,"); //getting rs
 symbol= strtok(NULL," \t\n");
 
 lc_val=get_lc((head),symbol); //getting lc value
 if (lc_val==(-1)) //here symbol was not found
 {
 	//insert error to undefined list
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {
 assemble_J(opc,atoi(rs),atoi(rt),lc_val);
 }
 }//end else
}//END CHECK_MNMEJL

//function that checks I format mnemonic in line with label
//takes mnemonic and line as parameters
//parses line based on mnemonic to use for assembly
void check_mnemIL(char* mnem,char* line)
{
 int opc;
	char* rs;
	char* rt;
	char* imd;// immediate operand
	char* label; //to store label
 char* str;
 opc=searchArray(mnem); //getting opc int
 if(strcmp(mnem,"li")==0)
{ // has two operands
  label= strtok(line,":");//getting label
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 imd = strtok(NULL," \t\n"); //getting the immediate operand
  assemble_I(opc,0,atoi(rt),atoi(imd));
}
else if((strcmp(mnem,"lwb")==0)||(strcmp(mnem,"swb")==0))
{ //each have two operands
  label= strtok(line,":");//getting label
 	str= strtok(NULL," \t"); //getting the mnemonic strig
 	rt= strtok(NULL," \t$,"); //getting rt
 	imd=strtok(NULL,"("); //getting immediate value
 	rs= strtok(NULL,"$)"); //getting the register inside the brace
  assemble_I(opc,atoi(rs),atoi(rt),atoi(imd));
}
else  //here mnemonic is one of subi,muli,divi,modi
{ //each have 3 operands
  
  label= strtok(line,":");//getting label
 str= strtok(NULL," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs=strtok(NULL,"$,"); //registerrs
 imd= strtok(NULL," \t\n"); //immediate value
  assemble_I(opc,atoi(rs),atoi(rt),atoi(imd));
 }
}//END CHECK_MNEMIL

	//this is the same as check_mnemRL but line has no label
	//takes mnemonic and line as parameters
//parses line based on mnemonic to use for assembly
void check_mnemR(char* mnem,char* line)
{
	char* rs1; //register 1
char* rs2; //register2
char* rt; //target register
char* sa; //shift amout
int opc; //this is the decimal value of opcode
char* str;
//firrst get the decimal opcode of themnemonic
opc=searchArray(mnem); //this will return the decimal opcde value

if(strcmp(mnem,"hlt")==0)
{//hlt instruction has no operands
	assemble_R(opc,0,0,0,0); //all arguments are 0 
}
else if((strcmp(mnem,"jr")==0)||(strcmp(mnem,"rdr")==0)||(strcmp(mnem,"prr")==0)||(strcmp(mnem,"prh")==0))
{// all have 1 operand rt
 //label= strtok(line,":");//getting label
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," $\t\n"); //getting rt
 assemble_R(opc,0,0,atoi(rt),0);
	
}
else if((strcmp(mnem,"move")==0)||(strcmp(mnem,"com")==0))
{ //each have two operands
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL," $\t\n"); //first register
  assemble_R(opc,atoi(rs1),0,atoi(rt),0);
}
else if((strcmp(mnem,"sll")==0)||(strcmp(mnem,"srl")==0)||(strcmp(mnem,"sra")==0))
{// all have 3 operands
  str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL,"$,"); //first register
 sa= strtok(NULL," \t\n"); //getting shift amount
	assemble_R(opc,atoi(rs1),0,atoi(rt),atoi(sa));
}
else //here the instruction is one of add,sub,mul,div,mod,and,or,xor
{// 3 register operands
 //get operands
  str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs1=strtok(NULL,"$,"); //first register
 rs2= strtok(NULL," $\t\n"); //getting second register
 assemble_R(opc,atoi(rs1),atoi(rs2),atoi(rt),0);
 }
}//END CHECK_MNEMR

// same as check_mnemJL but line has no label
//takes mnemonic and line as parameters
//parses line based on mnemonic to use for assembly
void check_mnemJ(char* mnem,char* line)
	{
	int opc;
	char* rs;
	char* rt;
	char* symbol;
	int lc_val; //to store the lc value of the specified label
	char undefErr[]="Undefined symbol";
 char* str;

 opc=searchArray(mnem); //this will return the decimal opcde value

 if((strcmp(mnem,"j")==0)||(strcmp(mnem,"jal")==0))
{// all have 1 operand symbol
 str= strtok(line," \t"); //getting the mnemonic strig
 symbol= strtok(NULL," \t\n"); //getting symbol
 lc_val=get_lc((head),symbol); //getting lc value
 if (lc_val==(-1)) //here symbol was not found
 {
 	//insert symbol to undefined symbol list
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {//assemble the instruction
 assemble_J(opc,0,0,lc_val);
 }
}//end if j, jal
	else if((strcmp(mnem,"lwa")==0)||(strcmp(mnem,"swa")==0))
{// all have 2 operands rt and symbol
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," $\t,"); //getting rt
 symbol= strtok(NULL," \t\n");
 lc_val=get_lc((head),symbol); //getting lc value
 
 if (lc_val==(-1)) //here symbol was not found
 {
 //insert symb to unidefined symbol
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {
 assemble_J(opc,0,atoi(rt),lc_val);
 }
	
}//end else if lwa, swa
else //here mnemonic is one of jeq, jne jlt,jle,jgt,jge
{//have 3 operands rt, rs and symbol
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs= strtok(NULL, "$,"); //getting rs
 symbol= strtok(NULL," \t\n");
 
 lc_val=get_lc(head,symbol); //getting lc value
 if (lc_val==(-1)) //here symbol was not found
 {
 //insert undefined symbol error
 	insertSymErr(&(headU),&(tailU),symbol);
 }
 else
 {
 assemble_J(opc,atoi(rs),atoi(rt),lc_val);
 
 }
 }//end else
	
}//END CHEK_MNEMJ

//same as Check_mnemIL	but line has no label
//takes mnemonic and line as parameters
//parses line based on mnemonic to use for assembly
void check_mnemI(char* mnem,char* line)
{
 int opc;
	char* rs;
	char* rt;
	char* imd;// immediate operand
 char* str;
 opc=searchArray(mnem); //getting opc int
 if(strcmp(mnem,"li")==0)
{ // has two operands
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 imd = strtok(NULL," \t\n"); //getting the immediate operand
  assemble_I(opc,0,atoi(rt),atoi(imd));
}
else if((strcmp(mnem,"lwb")==0)||(strcmp(mnem,"swb")==0))
{ //each have two operands
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 imd=strtok(NULL,"("); //getting immediate value
 rs= strtok(NULL,"$)"); //getting the register inside the brace
  assemble_I(opc,atoi(rs),atoi(rt),atoi(imd));
}
else  //here mnemonic is one of subi,muli,divi,modi
{ //each have 3 operands
 str= strtok(line," \t"); //getting the mnemonic strig
 rt= strtok(NULL," \t$,"); //getting rt
 rs=strtok(NULL,"$,"); //registerrs
 imd= strtok(NULL," \t\n"); //immediate value
  assemble_I(opc,atoi(rs),atoi(rt),atoi(imd));
 }

}//END CHECK_MNEMI

//function that takes a directive name and line number as parameters
//checks which directive it is and assembles instruction accordingly
	void check_directive(char* dirStr,char* line)
	{
		char* label;
		char* str;
		char* initial;
		char* incr;
	
		if (strcmp(dirStr,".word")==0)
		{
		 label=strtok(line,":"); //getting label
		 str= strtok(NULL, " \t");// getting opcod
		 initial= strtok(NULL, " \t:");//getting the number before the :
		 incr=strtok(NULL, " \t\n"); // getting number after the :
		 assemble_Dir(atoi(initial),atoi(incr)); 
		}
	//if directive is .resw
		else if(strcmp(dirStr,".resw")==0)
		{
		label=strtok(line,":");
		str= strtok(NULL, " \t");
		incr=strtok(NULL, " \t\n"); //only an increment value after label and opcode
		assemble_Dir(0,atoi(incr));
		}
		else
		{
		; //do nothing
		}
	
	}//END CHECK_DIRECTIVE
	
	//takes the initialization vale and increment vale of the LC as parameters
	//performs the assembly of a directivd
	void assemble_Dir(int initial, int inc)
	{
		int instr=0; 
		int i; //index
		//lc++;
		for(i=0;i<inc;i++)
		{
			instr=initial; //initialized to specified amount
			mem[lc]=instr; //putting instruction in the array at index lc
		 lc++;
		}
	}//END ASSEMBLE_DIR
	
	
	//assembles R format instruction
	//takes the opcode, first , second and target register,hift amount
	//as parameters
void assemble_R(int opcode, int rs1,int rs2, int rt,int sft)
{
	int inst=0; //to store the assembled instruction
	opcode=opcode<< OC; //shift left by 26 to get to right position
	inst=inst|opcode; //oring instwith opcode,first 6 bits of inst now contain opcode
	rs1=rs1<< REG1;//shifting rs1 left by 21
	inst=inst|rs1;//now rs1 in 5 bits after opcode
	rs2=rs2<<REG2; //rs2 shiftleft by 16
	inst=inst|rs2; //rs2 stored after rs1
	rt=rt<<REG3; //shift left by 11
	inst=inst|rt; //rt stored after rs2
	sft=sft<<SA; //sht shifted by 6
	inst=inst|sft; //sft stored after rt
	mem[lc]=inst; //storing instruction in memory array
	
}
void assemble_J(int opcode, int rs, int rt, int lc_v)
{
int inst=0; //to store the assembled instruction
	opcode=opcode<< OC; //shift left by 26 to get to right position
	inst=inst|opcode; //oring instwith opcode,first 6 bits of inst now contain opcode
	rs=rs<< REG1;//shifting rs left by 21
	inst=inst|rs;//now rs in 5 bits after opcode
	rt=rt<<REG2; //rt shiftleft by 16
	inst=inst|rt; //rt stored after rs
	inst=inst|lc_v; //lc value now stored in the last 16 bits
	mem[lc]=inst;
	
}
void assemble_I(int opcode,int rs, int rt, int immed)
{
int inst=0; //to store the assembled instruction
int num=0x0000FFFF;
	opcode=opcode<< OC; //shift left by 26 to get to right position
	inst=inst|opcode; //oring instwith opcode,first 6 bits of inst now contain opcode
	rs=rs<< REG1;//shifting rs left by 21
	inst=inst|rs;//now rs in 5 bits after opcode
	rt=rt<<REG2; //rt shiftleft by 16
	inst=inst|rt; //rt stored after rs
	immed=immed&num; //anding immediate with FFFF incase the immediate is a -ve#
																					//we want to get the last 16 bits 
	inst=inst|immed;	//storing the immediate value in the last 16 bits	
 mem[lc]=inst;
	
}

//takes the head of the symbol table and a label as parameters
//if symbol is found in the table, returns the lc value of the symbol
//if not found, returns -1
int get_lc(symNode* head, char* symbol)
{
		int lc_v;
		symNode* head2;
		head2= head;

	while (head2 != NULL) 
	{
		if (strcmp((head2)->label, symbol) ==0)//string is found
		{
				lc_v= (head2)->address; //lc_v now has the lc value of symbol found
			return lc_v; //return lc value
		}
		head2 = head2->next;

}//end while
	/*here, symbol not found so return -1*/
	return (-1);
} //end of get_lc


