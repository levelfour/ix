#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

#include "token.h"
#include "syntax.h"

using namespace std;

const char prompt[] = ">>> ";

// get stream function
bool getSrc(string& str) {
	str.clear();
	cout << prompt;
	getline(cin, str);
	if(str != "") return true;
	return false;
}

int main() {
	string src;				// user input source
	TokenArray token;		// lexical analyzer
	SyntaxTree syntax;		// syntax tree

	while(getSrc(src)) {
		// exit command
		if(src == "exit" || src == "quit" || src == "q") break;
		
		try {
			token.scanner(src);
			token.tokenizer();
			//token.show();

			syntax.parser(&token);
			cout << syntax.exec() << endl;
		} catch(const string err) {
			cerr << err << endl;	
		}

		// finalizer
		token.clear();
		syntax.clear();
	}

	return 0;
}
