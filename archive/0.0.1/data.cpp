#include "header/data.h"

// 識別子
// アルファベット及びアンダースコア
const char specifier_str[] =
	"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

// 演算子
// 第2次元の[2]は文字列の長さの最大値
const int operator_num = 29;
const char operator_str[operator_num][3] = {
 "+","-","*","/","%","=","++","--","&&","||","!",/*"?",":",*/"<","<=",">",
 ">=","==","!=","&","|","^","<<",">>","~","[","]","(",")",".","->"
};

// 予約語
const int reserved_num = 32;
const char reserved_str[reserved_num][9] = {
 "void","char","short","int","long","float","double","auto","static",
 "const","signed","unsigned","extern","volatile","register","return",
 "goto","if","else","switch","case","default","break","for","while",
 "do","continue","typedef","struct","enum","union","sizeof"
};

// デリミタ
const int delimiter_num = 4;
const char delimiter_str[delimiter_num][2] = {
 "\"","\'",",",";",
};

// スペース(読み飛ばし文字)
const int space_num = 3;
const char space_str[space_num][2] = {
 " ","\t","\n"
};

