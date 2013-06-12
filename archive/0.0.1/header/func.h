#ifndef __FUNC_H__
#define __FUNC_H__

#include <boost/lexical_cast.hpp>

#include "parse.h"

// boost::lexical_castのラッパー
int icast(Token tok);

// エラーメッセージを表示して例外を投げる
void warning(const char *err_msg);
void warning(const char *func, const char *msg);

#endif // __FUNC_H__
