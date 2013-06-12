#ifndef __SYNTAX_H__
#define __SYNTAX_H__

#include "token.h"
#include "expr.h"

class SyntaxTree {
public:
	SyntaxTree() {

	}

	~SyntaxTree() {

	}

	void parser(TokenArray *tokarray) {
		tree = new Expr(tokarray, true);
	}

	int exec() {
		return 0;
	}

private:
	Expr *tree;

};


#endif // __SYNTAX_H__
