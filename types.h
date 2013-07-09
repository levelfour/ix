#ifndef __TYPES_H__
#define __TYPES_H__

// token types
enum TOKTYPE {
	TOK_UNKNOWN = 0,
	TOK_NUMBER,
	TOK_IDENTIFIER,
	TOK_OPERATOR,
	TOK_STRING,
	TOK_DELIMITER, // (, ), {, },
};

enum OPTYPE {
	OP_NULL = -1,
	OP_MUL = 0,
	OP_DIV,
	OP_MOD,
	OP_ADD,
	OP_SUB,
	OP_SHL,
	OP_SHR,
	OP_LT,
	OP_LTE,
	OP_GT,
	OP_GTE,
	OP_EQ,
	OP_NEQ,
	OP_B_AND,
	OP_XOR,
	OP_B_OR,
	OP_AND,
	OP_OR,
	OP_MOV,
}; 

// symbol types
enum SYMBTYPE {
	SYMB_VARIABLE,
	SYMB_FUNCTION,
};

#endif // __TYPES_H__
