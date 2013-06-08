#ifndef __PARSE_H__
#define __PARSE_H__

#include <cstring>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include "enum.h"

class Token;
typedef std::vector<Token> TokenArray;

// parse(字句解析)を行う関数群
// Tokenクラス:トークンを文字列として保持するクラス
class Token
{
private:
	std::string _str;	// トークンそのものの文字列
	TOKEN_TYPE _tok_type;	// トークンの種類

public:
	Token(std::string arg, TOKEN_TYPE type = TOK_UNKNOWN);
	virtual ~Token();
	// _strのアクセサ
	std::string str() const;
	// _tok_typeのアクセサ
	TOKEN_TYPE type() const;
	void type(TOKEN_TYPE a_type);
	// 代入演算子(文字列を代入する)
	void operator=(const std::string rvalue);
	// 代入演算子(トークンをコピーする)
	void operator=(const Token tok);
};

// トークンをすべて表示するテスト用関数
void token_show(TokenArray tokarray);
// トークンへ分割する字句解析関数
void tokenize(std::string& str, TokenArray& tokarray);

#endif	// __PARSE_H__
