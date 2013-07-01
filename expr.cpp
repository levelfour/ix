#include <sstream>
#include "expr.h"
#include "token.h"
#include "term.h"
#include "opr.h"
using namespace std;

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
		if(root <= 0 || tokarray->size() < root) {
			throw string(__func__) + (": out of range");
		}
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

Expr::~Expr() {
	delete _parent;
	//delete _instance;
}

int Expr::evaluate() {
	return _instance->evaluate();
}
