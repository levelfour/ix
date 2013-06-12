#include "header/lex.h"
using namespace std;

// 構文解析関数
int lexical_analysis(ExpressionQueue exprq, const TokenArray tokarray)
{
	Token tok = Token("");	// トークンバッファ
	for(int i = 0; i < tokarray.size(); i++)
	{
		tok = tokarray[i];
		switch(tok.type())
		{
		// 演算子なら
		case TOK_OPERATOR:
			// 単項演算子なら
			if(is_sigop(tok))
			{
			}
			//　二項演算子なら
			if(is_binop(tok))
			{
			}
		}
	}
}

// 単項演算子かどうかを判定する
bool is_sigop(Token tok)
{
	return false;
}

// 二項演算子かどうかを判定する
bool is_binop(Token tok)
{
	return true;
}
