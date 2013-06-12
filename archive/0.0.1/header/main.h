#ifndef __MAIN_H__
#define __MAIN_H__

// ヘッダファイル
#include <iostream>
#include <cstring>
#include <string>
#include <boost/format.hpp>

#include "expression.h"

// メイン関数
int main();
// 左辺値スタックを再帰走査する
// 左辺値スタックの値を使う場合
void lvs_prev_recurse(LvalueStack& lvs, Expression& e_this);
// 左辺値スタックの式が現在処理中の式の値を使う場合
void lvs_next_recurse(LvalueStack& lvs, Expression& e_this);
// 第3引数の式よりも優先順位の高い式をすべて評価し、与えた式の評価結果を返す
Expression evaluate(LvalueStack& lvs, ExpressionQueue& exprq, Expression& e, const int priority);

#endif	// __MAIN_H__
