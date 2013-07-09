#include <iostream>
#include "term.h"
#include "opr.h"
using namespace std;

OPTYPE getOpType(string opstr) {
	for(int i = 0; i < OPERATOR_N; i++) {
		if(opstr == op_tok[i]) return (OPTYPE)i;
	}
}

TermOp::TermOp(OpType type, Expr *op1, Expr *op2) :_type(type.type()) {
	_args.push_back(op1); _args.push_back(op2);
}

TermOp::~TermOp() {
	for(int i = 0; i < _args.size(); i++) {
		cout << __func__ << ": delete" << endl;
		//delete _args[i];
	}
}

int TermOp::evaluate() {
	return op_tbl[_type](_args[0], _args[1]);
}
