#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <cstdarg>
#include <string>
#include <sstream>
#include "token.h"
#include "types.h"
using namespace std;

class Expr;
class Term;
class TermInt;
class TermOp;

OPTYPE getOpType(string opstr);

// abstruct term class
class Term {
public:
	Term() {};
	virtual ~Term() {};
	virtual Term *evaluate() = 0;
	virtual int value() { return 1; };
};

// integer value term
class TermInt : public Term {
public:
	TermInt(int arg) : _integer(arg) {}
	TermInt(Term *term) {
		//_integer = term->evaluate();
		delete term;
	}
	~TermInt() {}
	Term *evaluate() {
		return this;
	}
	int value() { return _integer; }
private:
	int _integer;
};

typedef TermInt* (*op_func)(Expr *op1, Expr *op2);
typedef op_func FuncTbl[OPERATOR_N];
extern FuncTbl func_tbl;

// operator value term (reference to a new expression)
class TermOp : public Term {
public:
	TermOp(OPTYPE type, Expr *op1, Expr *op2) :_type(type) {
		_args.push_back(op1); _args.push_back(op2);
		//_tbl_ = func_tbl;
	}
	virtual ~TermOp() {
		for(int i = 0; i < _args.size(); i++) {
			cout << __func__ << ": delete" << endl;
			//delete _args[i];
		}
	}
	Term *evaluate() {
		//return _tbl_[_type](_args[0], _args[1]);
	}
private:
	OPTYPE			_type;
	vector<Expr*>	_args;
	static FuncTbl	_tbl_;
};

class Expr {
public:
	Expr(TokenArray *tokarray, bool is_root = false);
	virtual ~Expr() {
		delete _parent;
		//delete _instance;
	}
	int evaluate() {
		return _instance->value();
	}

private:
	Expr		*_parent;	// parent of this expression
	TOKTYPE		_type;		// token type
	Term		*_instance;	// the instance of the term
};

#endif // __EXPR_H__
