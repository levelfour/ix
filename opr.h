#ifndef __OPR_H__
#define __OPR_H__

#include <string>
#include "expr.h"
#include "types.h"

const int OPERATOR_N = 19;
const char op_tok[OPERATOR_N][3] = {
	"*","/","%",
	"+","-",
	"<<",">>",
	"<","<=",">",">=",
	"==","!=",
	"&",
	"^",
	"|",
	"&&",
	"||",
	"=",
};

// wrapper of OPTYPE
// add operator< method (overrided) for max_element algorithm
class OpType {
public:
	OpType(std::string str);
	OpType(int n);
	OPTYPE type();
	bool operator<(OpType op);
	void operator=(int n);
private:
	OPTYPE _type;
};

typedef int (*op_func)(Expr *op1, Expr *op2);
typedef op_func FuncTbl[OPERATOR_N];
extern FuncTbl op_tbl; // operator function table

int op_mul(Expr *op1, Expr *op2);
int op_div(Expr *op1, Expr *op2);
int op_mod(Expr *op1, Expr *op2);

int op_add(Expr *op1, Expr *op2);
int op_sub(Expr *op1, Expr *op2);

int op_shl(Expr *op1, Expr *op2);
int op_shr(Expr *op1, Expr *op2);

int op_lt(Expr *op1, Expr *op2);
int op_lte(Expr *op1, Expr *op2);
int op_gt(Expr *op1, Expr *op2);
int op_gte(Expr *op1, Expr *op2);

int op_eq(Expr *op1, Expr *op2);
int op_neq(Expr *op1, Expr *op2);

int op_b_and(Expr *op1, Expr *op2); // bit and

int op_xor(Expr *op1, Expr *op2);

int op_b_or(Expr *op1, Expr *op2); // bit or

int op_l_and(Expr *op1, Expr *op2); // logical and

int op_l_or(Expr *op1, Expr *op2); // logical or

int op_mov(Expr *op1, Expr *op2); // substitution

#endif // ___OPR_H__
