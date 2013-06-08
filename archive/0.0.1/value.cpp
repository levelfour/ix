#include "header/value.h"
using namespace std;

// 値クラス
Value::Value(VALUE_TYPE type, int value)
	: _val_type(type), _value(value) {}
	
Value::Value() {}
Value::~Value() {}

// _val_typeのアクセサ
VALUE_TYPE Value::type() const { return _val_type; }

void Value::type(VALUE_TYPE type) { _val_type = type; }

// _valueのアクセサ
int Value::value() const { return _value; }
