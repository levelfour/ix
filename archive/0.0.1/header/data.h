#ifndef __DATA_H__
#define __DATA_H__

// 識別子
// アルファベット及びアンダースコア
extern const char specifier_str[];

// 演算子
// 第2次元の[2]は文字列の長さの最大値
extern const int operator_num;
extern const char operator_str[/*operator_num*/][3];

// 予約語
extern const int reserved_num;
extern const char reserved_str[/*reserved_num*/][9];

// デリミタ
extern const int delimiter_num;
extern const char delimiter_str[/*delimiter_num*/][2];

// スペース(読み飛ばし文字)
extern const int space_num;
extern const char space_str[/*space_num*/][2];

#endif // __DATA_H__
