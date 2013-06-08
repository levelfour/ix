#include "header/main.h"
#include "header/parse.h"
#include "header/expression.h"
#include "header/func.h"
using namespace std;

int main()
{
	string str;				// 入力された文字列のバッファ
	ExpressionQueue exprq;	// 未処理式キュー
	LvalueStack		lvs;	// 処理中左辺値のバッファ

	for(;;)
	{
		TokenArray tokarray;		// トークンを格納
		
		cout << boost::format(">>> ");

		// 空白も含めて入力ストリームから読み込む
		getline(cin, str);

		// exitコマンド
		if(str=="exit") break;

		// トークン分割
		// 文字列strをトークンに分割してトークン配列tokarrayに格納
		tokenize(str, tokarray);

		// テスト用関数:分割したトークンをすべて表示
		token_show(tokarray);

		// トークンを式に変換してキューにつめる
		int index = 0;
		Expression expr;
		for(	TokenArray::iterator it = tokarray.begin();
				it != tokarray.end();
				++it, ++index)
		{
			// 演算子トークンなら
			if(it->type() == TOK_OPERATOR)
			{
				// 新しい式を生成してキューにプッシュする
				expr = Expression(tokarray, index);
				exprq.push(expr);
			}
		}
		
		// 左辺値スタックが空になるまで処理を続ける
		while(!exprq.empty())
		{
			Expression e = exprq.front(); exprq.pop();
			lvs.push(evaluate(lvs, exprq, e, e.sub_type()));
		}

		if(!lvs.empty()) cout << "RESULT: " << lvs.top().value() << endl;
		else warning("main()", "lvs is empty");

		// キューとスタックを空にする
		while(!exprq.empty())	exprq.pop();
		while(!lvs.empty())		lvs.pop();
	}

	return 0;
}

// 左辺値スタックの値を使うときに、左辺値スタックを再帰走査する
void lvs_prev_recurse(LvalueStack& lvs, Expression& e_this)
{
	// 左辺値スタックから1つ式を取り出す
	Expression e_prev = lvs.top(); lvs.pop();
	// 前の式を使う場合は前の式の値が即値になるまで再帰
	if(e_prev.is_use_prev()) lvs_prev_recurse(lvs, e_prev);
	// 前の式が即値になったら計算する
	e_this = e_this.result(e_prev);
}

// 左辺値スタックの式が現在処理中の式の値を使うとき左辺値スタックを再帰走査
// ⇔ 第2オペランドがNEXTの式
void lvs_next_recurse(LvalueStack& lvs, Expression& e_this)
{
	// 左辺値スタックから1つ式を取り出す
	if(lvs.empty()) return;
	Expression e_prev = lvs.top();
	// 第2オペランドがNEXTでなくなったら再帰終了
	if(!e_prev.is_use_next()) return;
	lvs.pop();
	// 第2オペランドがNEXTでなくなるまで再帰
	lvs_next_recurse(lvs, e_prev);
	// 1つ前の式を評価する
	if(!e_prev.is_use_prev())
	{
		e_this = e_prev.result(e_this);
	} else {
		Expression e_prev_p = lvs.top(); lvs.pop();
		e_this = e_prev.result(e_prev_p, e_this);
	}
}

// 第3引数の式よりも優先順位の高い式をすべて評価し、与えた式の評価結果を返す
// 第4引数は最初にこの関数を呼んだときに第3引数に与えた式の優先度
Expression evaluate(LvalueStack& lvs, ExpressionQueue& exprq, Expression& e, const int priority)
{
	// 前後の式両方の評価結果を使う場合
	if(e.is_use_next() && e.is_use_prev())
	{
		if(exprq.empty()) warning("evaluate()", "exprq is empty");
		if(lvs.empty()) warning("evaluate()", "lvs is empty");
		// 次の式を取り出す
		Expression e_next = exprq.front(); exprq.pop();
		// 前の式(即値)を取り出す
		Expression e_prev = lvs.top(); lvs.pop();
		
		return e.result(e_prev, evaluate(lvs, exprq, e_next, priority));
	}

	// 次の式の評価結果のみ使う場合
	if(e.is_use_next())
	{
		if(exprq.empty()) warning("evaluate()", "exprq is empty");
		// 次の式を取り出す
		Expression e_next = exprq.front(); exprq.pop();
		return e.result(evaluate(lvs, exprq, e_next, priority));
	}

	// 前の式の評価結果のみ使う場合
	if(e.is_use_prev())
	{
		if(lvs.empty()) warning("evaluate()", "lvs is empty");
		// 前の式(即値)を取り出す
		Expression e_prev = lvs.top(); lvs.pop();
		return e.result(e_prev);
	}

	// 式評価
	e = e.result();

	// 次の式を取り出す
	Expression e_next = exprq.front();
	// 最初に始めた式より優先度が低ければひとまず評価終了
	if(is_same_priority(priority, e_next.sub_type()) >= 0) return e;
	else
	{
		// 評価結果をスタックにつむ
		lvs.push(e); exprq.pop();
		// 次の式を続けて評価する
		return evaluate(lvs, exprq, e_next, e_next.sub_type());
	}
}
