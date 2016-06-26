//LINKED LIST STRUCTURE FOR SYMBOL TABLE
	struct symbol_node{
		char label[LABEL_LEN]; 
		int  address;
		struct symbol_node* next;
	};
	typedef struct symbol_node symNode;

	//linked list to store the errors and their corresponding 
	//error messages
		
	//STRUCTURE TO STORE THE ILLEGAL OPCODE ERROR MESSAGE AND LINE WHERE THEY OCCUR
	struct error_node{
		char message[MESG_LEN]; 
		int  line;
		struct error_node* next;
	};
	typedef struct error_node errNode;
	
	
	//STRUCTURE TO STORE OPCODES
	struct symErr_node{
		char symbol[LABEL_LEN]; 
		struct symErr_node* next;
	};
	typedef struct symErr_node serrNode;
