#include "header/expression.h"
#include "header/func.h"
#include "header/enum.h"
using namespace std;

const int NEXT = INT_MAX;
const int PREV = SHRT_MAX;

// 式クラス
// コンストラクタ
// tokarray:トークン配列 index:述部トークンのインデックス
Expression::Expression(const TokenArray tokarray, int index) : _value(0)
{
	switch(tokarray[index].type())
	{
			// 述部が演算子なら
		case TOK_OPERATOR:
			_expr_type	= EXPR_OPERATION;
			_sub_type	= operator_type(tokarray[index].str().c_str());

			int op_prev, op_this, op_next;	// 前/現在/次の演算子
			// 1つ前の演算子があればそれを、なければ0を格納
			if(index >= 2) {
				op_prev = operator_type(tokarray[index-2].str().c_str());
			} else { op_prev = 0; }
			op_this = _sub_type;
			// 1つ後の演算子があればそれを、なければ0を格納
			if(index <= tokarray.size() - 3) {
				op_next = operator_type(tokarray[index+2].str().c_str());
			} else { op_next = 0; }

			// 前後の演算子と優先度の高低を比較する
			// 優先度が等しい場合は、前の式と等しいならPREVを、後ろの式と等しいなら即値を引数とする
			Expression op1, op2;	// 左右オペランド
			// 1つ前の演算子の優先度と比較
			if(is_same_priority(op_this, op_prev) > 0) {
				// 即値を引数に取る
				op1	= Expression(VAL_NUMBER,icast(tokarray[index-1].str()));
			} else {
				// PREV(評価結果)を引数に取る
				op1 = Expression(VAL_EXPRESSION, PREV);
			}
			// 1つ後の演算子の優先度と比較
			if(is_same_priority(op_this, op_next) >= 0) {
				// 即値を引数に取る
				op2 = Expression(VAL_NUMBER,icast(tokarray[index+1].str()));
			} else {
				// NEXT(評価結果)を引数に取る
				op2 = Expression(VAL_EXPRESSION, NEXT);
			}
			// 左右オペランドを引数として追加
			_arg.push_back(op1); _arg.push_back(op2);
			break;
	}
}

// 値式のコンストラクタ
Expression::Expression(VALUE_TYPE type, int value) : _value(value)
{
	// 式は値を表す
	_expr_type = EXPR_VALUE;
	_sub_type = type;
}

Expression::~Expression() {}

// _expr_typeに対するアクセサ
EXPR_TYPE Expression::expr_type() { return _expr_type; }

// _sub_typeに対するアクセサ
int Expression::sub_type() { return _sub_type; }

// 演算処理の実体
Expression Expression::calc(Expression e1, Expression e2)
{
	Expression result;	// 返却値
	// 演算式の場合
	if(_expr_type == EXPR_OPERATION)
	{
		//　op_func[演算子の識別値]で演算関数の呼び出し
		result = op_func[_sub_type](e1, e2);
		cout << "type: " << _sub_type << ", e1=" << e1.value()
			 << ", e2=" << e2.value() << endl;
	}

	return result;
}

// 式の値を返す(前後の式の評価結果を使わない場合)
Expression Expression::result()
{
	if(is_use_next() || is_use_prev())
	{
		cerr << "ERROR!: in Expression::result(),"
				"insufficient arguments" << endl;
		throw;
	}

	return calc(_arg[0], _arg[1]);
}

// 式の値を返す(前後どちらか一方の式の評価結果を使う場合)
// 足りない式を引数で渡す
Expression Expression::result(Expression e)
{
	// 前の式の値を使う場合
	if(_arg[0].value() == PREV) return calc(e, _arg[1]);
	// 次の式の値を使う場合
	else if(_arg[1].value() == NEXT) return calc(_arg[0], e);
	else
	{
		cerr << "ERROR!: in Expression::result(Expression e), "
				"invalid arguments" << endl;
		throw;
	}
}

// 式の値を返す(前後の式の評価結果をともに使う場合)
Expression Expression::result(Expression prev, Expression next)
{
	return calc(prev, next);
}

// 式の最終評価結果の値を返す
int Expression::value() const { return _value; }

// スタックに一時退避させるべきかどうかを返す
// 式はキューから1つずつ取り出して評価する
// そのときに次の式の評価結果を利用する場合は一時退避させる
bool Expression::is_use_next() const
{
	if(_arg.size() >= 2 && _arg[1].value() == NEXT) return true;
	else return false;
}

// 前の式の評価結果を利用するかどうか
bool Expression::is_use_prev() const
{
	if(!_arg.empty() && _arg[0].value() == PREV) return true;
	else return false;
}

// 演算子の種類を返す関数
int operator_type(const char *op)
{
	if(!strncmp(op, "+", 2)) return OP_ADD;
	if(!strncmp(op, "-", 2)) return OP_SUB;
	if(!strncmp(op, "*", 2)) return OP_MUL;
	if(!strncmp(op, "/", 2)) return OP_DIV;
}

// 2つの演算子の優先度が等しいかどうか比較する
int is_same_priority(int op1, int op2)
{
	// 優先度が等しい演算子は、演算子の識別値の10の位が等しい
	if(-10 < (op1-op2) && (op1-op2) < 10) return 0;
	else return op1 - op2;
}

// 2つの演算子の優先度が等しいかどうか比較する（引数に式を渡す場合）
int is_same_priority(Expression e1, Expression e2)
{
	if(e1.expr_type() != EXPR_OPERATION || e2.expr_type() != EXPR_OPERATION)
	{
		cerr << "ERROR!: in function 'is_same_priority()'"
				"some expressions for arguments are not operative expression" << endl;
		throw;
	}
	// 演算子の種類を取得して処理を投げる
	int op1 = e1.sub_type();
	int op2 = e2.sub_type();
	return is_same_priority(op1, op2);
}

// 演算関数配列
// 演算関数の個数
const int op_func_num = 4;

OP_FUNC op_func_null = NULL;

Expression op_func_add(Expression e1, Expression e2)
{
	Expression result;
	result = Expression(VAL_NUMBER, e1.value()+e2.value());
	return result;
}

Expression op_func_sub(Expression e1, Expression e2)
{
	Expression result;
	result = Expression(VAL_NUMBER, e1.value()-e2.value());
	return result;
}

Expression op_func_mul(Expression e1, Expression e2)
{
	Expression result;
	result = Expression(VAL_NUMBER, e1.value()*e2.value());
	return result;
}

Expression op_func_div(Expression e1, Expression e2)
{
	Expression result;
	result = Expression(VAL_NUMBER, e1.value()/e2.value());
	return result;
}

// 演算関数配列の実体
// op_func[演算子の識別値]で呼ぶことができる
OP_FUNC op_func[] = {
	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
	op_func_add,
	op_func_sub, 
	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
	op_func_mul, 
	op_func_div,
};
