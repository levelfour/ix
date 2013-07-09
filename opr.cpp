#include "opr.h"
#include <string>
using namespace std;

OpType::OpType(std::string str) {
	_type = OP_NULL;
	for(int i = 0; i < OPERATOR_N; i++) {
		if(str == op_tok[i]) _type = (OPTYPE)i;
	}
}

OpType::OpType(int n) { _type = (OPTYPE)n; }

OPTYPE OpType::type() { return _type; }

// overrided method for algorithm 'max_element()'
bool OpType::operator<(OpType op) {
	if(OP_MUL <= _type && _type <= OP_MOD
	&& OP_MUL <= op.type() && op.type() <= OP_MOD) return false;
	if(OP_ADD <= _type && _type <= OP_SUB
	&& OP_ADD <= op.type() && op.type() <= OP_SUB) return false;
	if(OP_SHL <= _type && _type <= OP_SHR
	&& OP_SHL <= op.type() && op.type() <= OP_SHR) return false;
	if(OP_LT <= _type && _type <= OP_GTE
	&& OP_LT<= op.type() && op.type() <= OP_GTE) return false;
	if(OP_LT <= _type && _type <= OP_GTE
	&& OP_LT<= op.type() && op.type() <= OP_GTE) return false;
	if(OP_EQ <= _type && _type <= OP_NEQ
	&& OP_EQ<= op.type() && op.type() <= OP_NEQ) return false;
	return (_type < op.type());
}

void OpType::operator=(int n) { _type = (OPTYPE)n; }

//////////////////////////////////////////// 
// operator implementation method
//////////////////////////////////////////// 
int op_mul(Expr *op1, Expr *op2) { return op1->evaluate() * op2->evaluate(); }
int op_div(Expr *op1, Expr *op2) { return op1->evaluate() / op2->evaluate(); }
int op_mod(Expr *op1, Expr *op2) { return op1->evaluate() % op2->evaluate(); }

int op_add(Expr *op1, Expr *op2) { return op1->evaluate() + op2->evaluate(); }
int op_sub(Expr *op1, Expr *op2) { return op1->evaluate() - op2->evaluate(); }

int op_shl(Expr *op1, Expr *op2) { return op1->evaluate() << op2->evaluate(); }
int op_shr(Expr *op1, Expr *op2) { return op1->evaluate() >> op2->evaluate(); }

int op_lt(Expr *op1, Expr *op2) { return op1->evaluate() < op2->evaluate(); }
int op_lte(Expr *op1, Expr *op2) { return op1->evaluate() <= op2->evaluate();}
int op_gt(Expr *op1, Expr *op2) { return op1->evaluate() > op2->evaluate(); }
int op_gte(Expr *op1, Expr *op2) { return op1->evaluate() >= op2->evaluate(); }

int op_eq(Expr *op1, Expr *op2) { return op1->evaluate() == op2->evaluate(); }
int op_neq(Expr *op1, Expr *op2) { return op1->evaluate() != op2->evaluate(); }

// bit and
int op_b_and(Expr *op1, Expr *op2) { return op1->evaluate() & op2->evaluate(); }

int op_xor(Expr *op1, Expr *op2) { return op1->evaluate() ^ op2->evaluate(); }

// bit or
int op_b_or(Expr *op1, Expr *op2) { return op1->evaluate() | op2->evaluate(); }

// logical and
int op_l_and(Expr *op1, Expr *op2) { return op1->evaluate() && op2->evaluate(); }

// logical or
int op_l_or(Expr *op1, Expr *op2) { return op1->evaluate() || op2->evaluate(); }

// substitution
int op_mov(Expr *op1, Expr *op2) {
	throw string(__func__) + string(": substitution has not yet supported");
	return op2->evaluate();
}

FuncTbl op_tbl = {
	op_mul, op_div, op_mod,
	op_add, op_sub,
	op_shl, op_shr,
	op_lt, op_lte, op_gt, op_gte,
	op_eq, op_neq,
	op_b_and,
	op_xor,
	op_b_or,
	op_l_and,
	op_l_or,
	op_mov,
};
