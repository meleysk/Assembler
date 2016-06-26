extern FILE* in_ptr; //file pointer for input file
extern FILE* obj_ptr; //file pointer for input file
extern FILE* sym_ptr; //file pointer for input file
extern FILE* err_ptr; //file pointer for input file
extern symNode* head; //head of symbol table linked list
extern symNode* tail; //tail for symbol table linked list
extern errNode* h; //head for error linked list
extern errNode* t; 
extern int lc;//to store lc value
extern int line_num;
		//string array to hold opcodes 
extern char* opcodes[];
extern int mem[MAX_MEM];
extern serrNode* headM; 
extern serrNode* tailM;  
	
extern serrNode* headU; 
extern serrNode* tailU;
extern char* invalOpErr;//="Error: Illegal optcode";
