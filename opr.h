#ifndef __OPR_H__
#define __OPR_H__

#include "expr.h"

const int OPERATOR_N = 4;
const char op_tok[OPERATOR_N][2] = {
	"*","/","+","-"
};

typedef int (*op_func)(Expr *op1, Expr *op2);
typedef op_func FuncTbl[OPERATOR_N];
extern FuncTbl op_tbl; // operator function table

int op_mul(Expr *op1, Expr *op2);
int op_div(Expr *op1, Expr *op2);
int op_add(Expr *op1, Expr *op2);
int op_sub(Expr *op1, Expr *op2);

#endif // ___OPR_H__
