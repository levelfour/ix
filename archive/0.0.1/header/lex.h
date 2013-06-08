#ifndef __LEX_H__
#define __LEX_H__

#include "parse.h"
#include "expression.h"
#include "enum.h"

// lexical analysis(構文解析)を行う関数群
// 構文解析関数
int lexical_analysis(ExpressionQueue exprq, const TokenArray tokarray);
// 単項演算子かどうかを判定
bool is_sigop(Token tok);
// 二項演算子かどうかを判定
bool is_binop(Token tok);

#endif // __LEX_H__
