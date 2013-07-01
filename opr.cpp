#include "opr.h"

int op_mul(Expr *op1, Expr *op2) {
	return op1->evaluate() * op2->evaluate();
}

int op_div(Expr *op1, Expr *op2) {
	return op1->evaluate() / op2->evaluate();
}

int op_add(Expr *op1, Expr *op2) {
	return op1->evaluate() + op2->evaluate();
}

int op_sub(Expr *op1, Expr *op2) {
	return op1->evaluate() - op2->evaluate();
}

FuncTbl op_tbl = {
	op_mul, op_div, op_add, op_sub
};
