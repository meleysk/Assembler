//PROTOTYPES
	char*  createObjFile(char* str);
	char*  createSymFile(char* str);
	char*  createErrFile(char* str);
 void insertSym(symNode** head,symNode** tail,char* str, int lc);
 void insertErr(errNode** h,errNode** t,char* msg, int ln);
 int search_sym(symNode **head, char* str);
 void print_sym(symNode** head);
 void print_err(errNode** head);
 int searchArray(char* str);
	void passOne(char* inputfile);
	int is_comment(char* line);
	int is_blank(char *line);
	void incr_lc(char* opc , char* line);
	char check_format(char* mnem);
	void passTwo(char* infile);
	
void	check_mnemRL(char* opcStr,char* line);
void check_mnemJL(char* opcStr,char* line);
void check_mnemIL(char* opcStr,char* line);
	
void check_mnemR(char* opcStr,char* line);
void check_mnemJ(char* opcStr,char* line);
void check_mnemI(char* opcStr,char* line);
void assemble_R(int opcode, int rs1,int rs2, int rt,int sft);
void assemble_J(int opcode, int rs, int rt, int lc);
void assemble_I(int opcode,int rs, int rt, int immed);

int get_lc(symNode* head, char* symbol);
void insertSymErr(serrNode** head,serrNode**tail, char* sym);
void print_symErr(serrNode** head);

void print_errFile(char* errfile);
void print_objFile(char* objfile);
void print_symFile(char* symFile);
void check_directive(char* dirStr,char* line);
void assemble_Dir(int initial, int inc);
void printMemArray();
