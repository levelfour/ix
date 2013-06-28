#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <cstdio>
#include <string>
#include <vector>
#include "types.h"
using namespace std;
	
const int OPERATOR_N = 4;
const char op_tok[OPERATOR_N][2] = {
	"*","/","+","-"
};


class TokenArray {
public:
	TokenArray() {}
	TokenArray(TokenArray *org, int begin, int end) {
		for(int i = 0; i < end - begin; i++) {
			_array.push_back(org->str(begin + i));
			_type.push_back(org->type(begin + i));
		}
	}
    
	~TokenArray() {}
    
	void scanner(string src);
	int tokenizer();

	TokenArray sub(int begin, int end) {
		return TokenArray(this, begin, end);
	}
    
	// clear token data
	void clear() {
		_array.clear();
		_type.clear();
	}
	int size() 			{ return _array.size(); }
	string str(int i)	{ return _array[i]; }
	TOKTYPE type(int i)	{ return _type[i]; }
    
#ifdef DEBUG
	// show all tokens
	void show() {
		for(int i = 0; i < _array.size(); i++) {
			printf("%s(%d)\n", _array[i].c_str(), _type[i]);
		}
	}
#endif
    
private:
	TOKTYPE toktype(int i);
   
	vector<string> _array;
	vector<TOKTYPE> _type;
    
};


#endif // __TOKEN_H__
