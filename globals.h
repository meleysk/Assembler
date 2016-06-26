// GLOBAL VARIABLES
	FILE* in_ptr; //file pointer for input file
	FILE* obj_ptr; //file pointer for input file
	FILE* sym_ptr; //file pointer for input file
	FILE* err_ptr; //file pointer for input file
	
	symNode* head; //head of symbol table linked list
	symNode* tail; //tail for symbol table linked list
	
	errNode* h; //head for illegal error linked list
	errNode* t; //tail for illegal error linked list
	
	serrNode* headM; //head for multiply defined symbol error linked list
	serrNode* tailM; //tail for multiply defined symbol error 
	
	serrNode* headU; //head for undefined symbol error list
	serrNode* tailU; //tail for undefined symbol error list
	
	int lc;//to store lc value
	int line_num=0;
		//string array to hold opcodes 
	char* opcodes[]={"hlt","add","sub","mul","div","mod","move","and","or","xor","com","sll","srl","sra","jr","rdr","prr","prh","li","addi","subi","muli","divi","modi","lwb","swb","lwa","swa","j","jal","jeq","jne","jlt","jle","jgt","jge"};
	
int mem[MAX_MEM]; //array to hold the final instructions
char* invalOpErr="Error: Illegal optcode";
