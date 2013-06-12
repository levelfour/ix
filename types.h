#ifndef __TYPES_H__
#define __TYPES_H__

// token types
enum TOKTYPE {
	TOK_UNKNOWN = 0,
	TOK_NUMBER,
	TOK_IDENTIFIER,
	TOK_OPERATOR,
	TOK_STRING,
};
 
// operator types
enum OPTYPE {
	OP_NULL = -1,
	OP_MUL = 0,
	OP_DIV,
	OP_ADD,
	OP_SUB
};

#endif // __TYPES_H__
