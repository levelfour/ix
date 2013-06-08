#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <cstring>
#include <climits>
#include <vector>
#include <stack>
#include <queue>

#include "parse.h"

class Expression;
typedef std::queue<Expression> ExpressionQueue;
// 左辺値スタックには常に1つ以下の式しかないように保つ
typedef std::stack<Expression> LvalueStack;

// 次の式を示す定数
extern const int NEXT;
// 前の式を示す定数
extern const int PREV;

// 演算関数ポインタ
typedef Expression (*OP_FUNC)(Expression e1, Expression e2);
extern OP_FUNC op_func[];
extern const int op_func_num;

// Expressionクラス:「式」を保持するクラス
class Expression
{
private:
	EXPR_TYPE _expr_type;			// 式の種類
	int _sub_type;					// 式の詳しい種類
	int _value;						// 値
	std::vector<Expression> _arg;	// 式の引数リスト

	Expression calc(Expression e1, Expression e2);	// 演算処理の実体

public:
	// コンストラクタ
	// tokarray:トークン配列 index:述部トークンのインデックス
	Expression(const TokenArray tokarray, int index);
	Expression(VALUE_TYPE type, int value);
	Expression() : _value(0) {}
	virtual ~Expression();
	// _expr_typeに対するアクセサ
	EXPR_TYPE expr_type();
	// _sub_typeに対するアクセサ
	int sub_type();
	// 式の最終評価結果の値
	Expression result();
	Expression result(Expression e);	// 前または次の式の評価結果を使う
	// 前後の式の評価結果を使う
	Expression result(Expression prev, Expression next);
	// 式の最終評価結果の値を即値で返す
	int value() const;
	// 次の式の評価結果を利用するかどうか
	// 利用するならば、この式をスタックに一時退避させなければならない
	bool is_use_next() const;
	// 前の式の評価結果を利用するかどうか
	bool is_use_prev() const;
};

// 演算子の識別値を返す関数
int operator_type(const char *op);
// 2つの演算子の優先度が等しいかどうか比較する
// 等しい時は0、op1>op2のときは正の値、op1<op2のときは負の値
int is_same_priority(int op1, int op2);
// 引数に式を渡す場合のオーバーローディング（演算式でないと例外発生）
int is_same_priority(Expression e1, Expression e2);

#endif // __EXPRESSION_H__
