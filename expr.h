#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <cstdarg>
#include <string>
#include <sstream>
#include "token.h"
#include "types.h"
using namespace std;

class Term;
class TermInt;
class TermOp;

OPTYPE getOpType(string opstr);

// abstruct term class
class Term {
public:
	Term() {};
	virtual ~Term() {};
	virtual int evaluate() = 0;
};

// integer value term
class TermInt : public Term {
public:
	TermInt(int arg) : _integer(arg) {}
	~TermInt() {}
	int evaluate() {
		return _integer;
	}
private:
	int _integer;
};

typedef TermInt* (*op_func)(Term *op1, Term *op2);
typedef op_func FuncTbl[OPERATOR_N];

TermInt *op_mul(Term *op1, Term *op2) {
	return new TermInt(op1->evaluate() * op2->evaluate());
}

TermInt *op_div(Term *op1, Term *op2) {
	return new TermInt(op1->evaluate() / op2->evaluate());
}

TermInt *op_add(Term *op1, Term *op2) {
	return new TermInt(op1->evaluate() + op2->evaluate());
}

TermInt *op_sub(Term *op1, Term *op2) {
	return new TermInt(op1->evaluate() - op2->evaluate());
}

FuncTbl func_tbl = {
	op_mul, op_div, op_add, op_sub
};

// operator value term (reference to a new expression)
class TermOp : public Term {
public:
	TermOp();
	int evaluate() {
		return _tbl_[_type](_args[0], _args[1]).evaluate();
	}
private:
	OPTYPE			_type;
	vector<Term*>	_args;
	static FuncTbl	_tbl_;
};

class Expr {
public:
	Expr(TokenArray *tokarray, bool is_root = false) {
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
			- (max_element(optype.begin(), optype.end()) -optype.begin());
		reverse(optype.begin(), optype.end());

		_type = tokarray->type(root); // determine token type
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
			break;
		default:
			throw string(__func__) + string(": unsupported token");
		}
	}

	virtual ~Expr() {
		delete _parent;
		delete _instance;
	}

private:
	Expr		*_parent;	// parent of this expression
	TOKTYPE		_type;		// token type
	Term		*_instance;	// the instance of the term

	TOKTYPE getType(string tok) {
		return TOK_UNKNOWN;
	}
};

#endif // __EXPR_H__
