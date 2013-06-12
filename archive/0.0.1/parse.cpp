#include "header/parse.h"
#include "header/data.h"
using namespace std;

// トークンクラス
Token::Token(string arg, TOKEN_TYPE type)
	: _str(arg), _tok_type(type) {}

Token::~Token() {}

// _strのアクセサ
string Token::str() const { return _str; }

// _tok_typeのアクセサ
TOKEN_TYPE Token::type() const { return _tok_type; }

void Token::type(TOKEN_TYPE a_type) { _tok_type = a_type; }

// 代入演算子(トークンの文字列を代入)
void Token::operator=(const string rvalue)
{
	_str = rvalue;
}

// 代入演算子(トークンをコピーする)
void Token::operator=(const Token tok)
{
	this->_str = tok.str();
	this->_tok_type = tok.type();
}


// トークンをすべて表示するテスト関数
void token_show(TokenArray tokarray)
{
	for(TokenArray::iterator it = tokarray.begin(); it != tokarray.end(); it++)
	{
		cout << it->str() << "(" << it->type() << ")" << "/";
	}
	cout << endl;
}


// 入力をトークンに分割してvectorに格納
void tokenize(string& str, TokenArray& tokarray)
{
	// トークン分割
	Token tmp = string("");

	// 次のトークンの種類の候補
	TOKEN_TYPE type_buf;
	
	// はじめのトークンの種類を判別
	for(int k = 0; k < strlen(specifier_str); k++)
		if(str[0] == specifier_str[k])
			type_buf = TOK_SPECIFIER;
	if('0' <= str[0] && str[0] <= '9') type_buf = TOK_NUMBER;
	for(int k = 0; k < operator_num; k++)
		if(!str.compare(0, strlen(operator_str[k]), operator_str[k]))
			type_buf = TOK_OPERATOR;
	for(int k = 0; k < reserved_num; k++)
		if(!str.compare(0, strlen(reserved_str[k]), reserved_str[k]))
			type_buf = TOK_RESERVED;
	for(int k = 0; k < delimiter_num; k++)
		if(!str.compare(0, strlen(delimiter_str[k]), delimiter_str[k]))
			type_buf = TOK_DELIMITER;
	for(int k = 0; k < space_num; k++)
		if(!str.compare(0, strlen(space_str[k]), space_str[k]))
			type_buf = TOK_SPACE;

	for(int i = 0; i < str.size(); )
	{
		// 次のトークンの切り出し位置
		int j = str.size();
		// 次のトークン切り出し位置(簡略用)
		int offset;

		// トークンの種類を確定
		tmp.type(type_buf);
		type_buf = TOK_UNKNOWN;	// バッファの初期化

		// トークンの区切りを検索(次のトークンの種類を判別)
		// 予約語を検索
		if(tmp.type() != TOK_RESERVED)
		for(int k = 0; k < reserved_num; k++)
		{
			offset = str.find(reserved_str[k], i);
			if(offset != string::npos && offset < j)
			{
				j = offset;
				type_buf = TOK_RESERVED;
			}
		}

		// アルファベットを検索
		if(tmp.type() != TOK_SPECIFIER && tmp.type() != TOK_RESERVED)
		for(int k = 0; k < strlen(specifier_str); k++)
		{
			offset = str.find(specifier_str[k], i);
			if(offset != string::npos && offset < j)
			{
				// トークン切り出し位置を新しく設定
				j = offset;
				// 暫定的にトークンの種類を決定
				type_buf = TOK_SPECIFIER;
			}
		}
		
		// 数字を検索
		if(tmp.type() != TOK_NUMBER)
		for(int k = 0; k < 10; k++)
		{
			offset = str.find(boost::lexical_cast<string>(k), i);
			if(offset != string::npos && offset < j)
			{
				j = offset;
				type_buf = TOK_NUMBER;
			}
		}
		
		// 演算子を検索
		if(tmp.type() != TOK_OPERATOR)
		for(int k = 0; k < operator_num; k++)
		{
			offset = str.find(operator_str[k], i);
			if(offset != string::npos && offset < j)
			{
				j = offset;
				type_buf = TOK_OPERATOR;
			}
		}

		// デリミタを検索
		if(tmp.type() != TOK_DELIMITER)
		for(int k = 0; k < delimiter_num; k++)
		{
			offset = str.find(delimiter_str[k], i);
			if(offset != string::npos && offset < j) 
			{
				j = offset;
				type_buf = TOK_DELIMITER;
			}
		}

		// スペース(読み飛ばし文字)を検索
		if(tmp.type() != TOK_SPACE)
		for(int k = 0; k < space_num; k++)
		{
			offset = str.find(space_str[k], i);
			if(offset != string::npos && offset < j) 
			{
				j = offset;
				type_buf = TOK_SPACE;
			}
		}

		// トークンの区切りが見つからなかったら
		if(j == string::npos) j = str.size();
		// 次の空白までをトークンとして切り出す
		tmp = str.substr(i, j-i);
		if(tmp.type() != TOK_SPACE) tokarray.push_back(tmp);
		// 終端まで達していたらブレイク
		if(str[j] == '\0') break;
		// 空白の次の文字から走査開始
		i = j;
	}
}
