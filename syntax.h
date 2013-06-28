#ifndef __SYNTAX_H__
#define __SYNTAX_H__

#include "token.h"
#include "expr.h"

class SyntaxTree {
public:
	SyntaxTree() {

	}

	~SyntaxTree() {
		//delete _tree;
	}

	void parser(TokenArray *tokarray) {
		_tree = new Expr(tokarray, true);
	}

	int exec() {
		return _tree->evaluate();
	}

	void clear() {
		//delete _tree;
	}

private:
	Expr *_tree;
};


#endif // __SYNTAX_H__
