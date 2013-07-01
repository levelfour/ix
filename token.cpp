#include "token.h"
#include "opr.h"

TokenArray::TokenArray(TokenArray *org, int begin, int end) {
	for(int i = 0; i < end - begin; i++) {
		_array.push_back(org->str(begin + i));
		_type.push_back(org->type(begin + i));
	}
}

// scanner
void TokenArray::scanner(string src) {
	int org = 0;
	for(int i = 0; i < src.length(); i++) {
		// recognize token using delimiter
		if(src[i] == ' ' || i == src.length() - 1){
			// extract token from origin to current offset
			_array.push_back(
				src.substr(org, i - org + ((src[i] == ' ') ? 0 : 1))
			);
			org = i + 1;
		}
	}
}

int TokenArray::tokenizer() {
	if(_array.size() == 0) throw string(__func__) + string(": token not found");
	if(toktype(0) == TOK_UNKNOWN)
		throw string(__func__) + string(": unknown token");
	_type.push_back(toktype(0));
    
	for(int i = 1 ; i < _array.size(); i++) {
		// get the current token type
		TOKTYPE cur_type = toktype(i);
        
		// rules for each token types
		switch(cur_type) {
        case TOK_NUMBER:
        case TOK_IDENTIFIER:
        case TOK_STRING:
            // throw exception when finding a series of same type tokens
            if(_type[i-1] == TOK_NUMBER || _type[i-1] == TOK_IDENTIFIER)
               throw string(__func__) + string(": expected ';'");
            else break;
        case TOK_OPERATOR:
            break;
        case TOK_UNKNOWN:
            throw string(__func__) + string(": unknown token");
		}
        
		_type.push_back(cur_type);
	}
        
	return EXIT_SUCCESS;
}

// extract sub TokenArray
TokenArray TokenArray::sub(int begin, int end) {
	return TokenArray(this, begin, end);
}

// clear token data
void TokenArray::clear() {
	_array.clear();
	_type.clear();
}

TOKTYPE TokenArray::toktype(int i) {
	switch(_array[i][0]) {
        case 'A'...'Z':
        case 'a'...'z':
        case '_':
            return TOK_IDENTIFIER;
        case '0'...'9':
            return TOK_NUMBER;
        case '"':
        {
			// find the endmark of string
			int endmark = _array[i].find_first_of("\"", 1);
			if(endmark == _array[i].size() - 1) {
				return TOK_STRING;
			} else return TOK_UNKNOWN;
		}
        default:
		{
			for(int j = 0; j < OPERATOR_N; j++) {
				// recognize token as operator
				if(_array[i] == op_tok[j]) return TOK_OPERATOR;
			}
			return TOK_UNKNOWN;
		}
	}
}
