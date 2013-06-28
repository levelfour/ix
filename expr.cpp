#include "expr.h"

OPTYPE getOpType(string opstr) {
	for(int i = 0; i < OPERATOR_N; i++) {
		if(opstr == op_tok[i]) return (OPTYPE)i;
	}
}

TermInt *op_mul(Expr *op1, Expr *op2) {
	return new TermInt(op1->evaluate()// * op2->evaluate());
	);
}

TermInt *op_div(Expr *op1, Expr *op2) {
	return new TermInt(op1->evaluate()// / op2->evaluate());
	);
}

TermInt *op_add(Expr *op1, Expr *op2) {
	return new TermInt(op1->evaluate()// + op2->evaluate());
	);
}

TermInt *op_sub(Expr *op1, Expr *op2) {
	return new TermInt(op1->evaluate()// - op2->evaluate());
	);
}

FuncTbl func_tbl = {
	op_mul, op_div, op_add, op_sub
};

// Expr Constructor
Expr::Expr(TokenArray *tokarray, bool is_root) {
	vector<OPTYPE> optype;	// contain operator type
	if(is_root) _parent = NULL;
	// labeling operator type for all tokens
	for(int i = 0; i < tokarray->size(); i++) {
		// switch for token type
		switch(tokarray->type(i)) {
		case TOK_NUMBER:
			optype.push_back(OP_NULL);
			break;
		case TOK_OPERATOR:
			optype.push_back(getOpType(tokarray->str(i)));
			break;
		default:
			throw string(__func__) + string(": unsupported token");
		}
	}


	// reverse vector order
	// in order to use max_element (max_element pick up element from front)
	// vector must be evaluated from back
	reverse(optype.begin(), optype.end());
	// root is the most unprior term searched from back
	int root = optype.size() - 1
		- (max_element(optype.begin(), optype.end()) - optype.begin());
	reverse(optype.begin(), optype.end());

	_type = tokarray->type(root); // determine token type

	// make instance for each type
	switch(_type) {
	case TOK_NUMBER:
	{
		int value; // instance value
		stringstream ss;
		ss << tokarray->str(root);
		ss >> value;
		_instance = new TermInt(value);
		break;
	}
	case TOK_OPERATOR:
	{
		TokenArray tok_front = tokarray->sub(0, root);
		TokenArray tok_back = tokarray->sub(root+1, tokarray->size());
		Expr *op1 = new Expr(&tok_front);
		Expr *op2 = new Expr(&tok_back);
		_instance = new TermOp(optype[root], op1, op2);
		break;
	}
	default:
		throw string(__func__) + string(": unsupported token");
	}
}
