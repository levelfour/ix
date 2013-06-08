#ifndef __VALUE_H__
#define __VALUE_H__

#include <climits>	// INT_MAXとSHRT_MAXを使うためのヘッダ
#include "enum.h"

// 次の式を示す定数
const int NEXT = INT_MAX;
// 前の式を示す定数
const int PREV = SHRT_MAX;

// Valueクラス:変数や即値のような「値」を保持するクラス
class Value
{
private:
	VALUE_TYPE _val_type;	// 値の種類
	int _value;		// 値の実体

public:
	Value(VALUE_TYPE type, int value);
	Value();
	virtual ~Value();
	// _val_typeのアクセサ
	VALUE_TYPE type() const;
	void type(VALUE_TYPE type);
	// _valueのアクセサ
	int value() const;
};

#endif // __VALUE_H__
