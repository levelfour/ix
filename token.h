#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <cstdio>
#include <string>
#include <vector>
#include "types.h"
using namespace std;

class TokenArray {
public:
	TokenArray() {}
	TokenArray(TokenArray *org, int begin, int end);
	~TokenArray() {}
    
	void scanner(string src);
	int tokenizer();
	TokenArray sub(int begin, int end);
	void clear();

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
