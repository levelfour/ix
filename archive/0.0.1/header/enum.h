#ifndef __ENUM_H__
#define __ENUM_H__

/*     列挙体     */
// トークンの種類
enum TOKEN_TYPE {
	TOK_UNKNOWN,	// 種類不明
	TOK_SPECIFIER,	// 識別子(変数名など)
	TOK_NUMBER,		// 即値
	TOK_RESERVED,	// 予約語
	/*TOK_SINGLE_OPERATOR,
	TOK_BINARY_OPERATOR,*/
	TOK_OPERATOR,	// 演算子
	TOK_DELIMITER,	// デリミタ
	TOK_SPACE,		// スペース
};

// 値の種類
enum VALUE_TYPE {
	VAL_NUMBER,		// 即値
	VAL_LITERAL,	// 文字列リテラル
	VAL_VARIABLE,	// 変数
	VAL_EXPRESSION,	// 式(の評価結果)	
};

// 演算モード
enum MODE {
	WAIT,
	ADD,
	SUB,
	MUL,
	DIV
};


// 式の種類
enum EXPR_TYPE {
	EXPR_OPERATION,		// 演算式(一般的な二項演算子を用いた演算)
	EXPR_VALUE,			// 値(即値、変数値など)
};


// 演算子の識別値
// 値が大きいものほど優先度が高く、優先度が等しいときは10の位が等しい
enum {
	OP_ADD = 10,	// 加算
	OP_SUB,			// 減算
	OP_MUL = 20,	// 乗算
	OP_DIV,			// 除算
};


#endif // __ENUM_H__
