#ifndef __TERM_H__
#define __TERM_H__

#include <vector>
#include <string>
#include "expr.h"
#include "types.h"

OPTYPE getOpType(std::string opstr);

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
	TermInt(Term *term) {
		//_integer = term->evaluate();
		delete term;
	}
	~TermInt() {}
	int evaluate() { return _integer; }
private:
	int _integer;
};

// operator value term (reference to a new expression)
class TermOp : public Term {
public:
	TermOp(OPTYPE type, Expr *op1, Expr *op2);
	virtual ~TermOp();
	int evaluate();

private:
	OPTYPE				_type;
	std::vector<Expr*>	_args;
};

#endif // __TERM_H__
