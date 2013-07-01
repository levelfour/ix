#ifndef __EXPR_H__
#define __EXPR_H__

#include "types.h"
using namespace std;

class TokenArray;
class Term;

class Expr {
public:
	Expr(TokenArray *tokarray, bool is_root = false);
	virtual ~Expr();
	int evaluate();

private:
	Expr		*_parent;	// parent of this expression
	TOKTYPE		_type;		// token type
	Term		*_instance;	// the instance of the term
};

#endif // __EXPR_H__
