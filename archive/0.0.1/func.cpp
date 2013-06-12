#include "header/func.h"
using namespace std;

// 文字列をint型にキャスト(boost::lexical_castのラッパー)
int icast(Token tok)
{
	string tmp = tok.str();
	try {
		// 文字列が数字なら数値にキャストして返却
		return boost::lexical_cast<int>(tmp);
	} catch(...) {
		// 文字列が数字でなければキャスト失敗
		return -1;
	}
}

// エラーメッセージを表示して例外を投げる
void warning(const char *err_msg)
{
	cerr << err_msg << endl;
	throw;
}

void warning(const char *func, const char *msg)
{
	cerr << "ERROR!: in function '" << func << "'\n" << msg << endl;
	throw;
}
