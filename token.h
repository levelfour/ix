#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <cstdio>
#include <string>
#include <vector>
using namespace std;
	
enum TOKTYPE {
	TOK_UNKNOWN = 0,
	TOK_NUMBER,
	TOK_IDENTIFIER,
	TOK_OPERATOR,
	TOK_STRING,
};
 
const int OPERATION_N = 4;
const char op_tok[OPERATION_N][2] = {
	"+","-","*","/"
};

class TokenArray {
public:
	TokenArray() {
        
	}
    
	~TokenArray() {
        
	}
    
	void scanner(string src);
	int tokenizer();
    
	// clear token data
	void clear() {
		_array.clear();
		_type.clear();
	}
    
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
