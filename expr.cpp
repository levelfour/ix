#include "expr.h"

OPTYPE getOpType(string opstr) {
	for(int i = 0; i < OPERATOR_N; i++) {
		if(opstr == op_tok[i]) return (OPTYPE)i;
	}
}


