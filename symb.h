#ifndef __SYMB_H__
#define __SYMB_H__

#include <string>
#include <vector>
#include "expr.h"
#include "types.h"

class Symbol {
public:
	Symbol();
	virtual ~Symbol();
	virtual SYMBTYPE type() = 0;
	std::string id() { return _id; }

private:
	std::string _id;
};

class SymbVariable : public Symbol {
public:
	SymbVariable();
	virtual ~SymbVariable();
	SYMBTYPE type() { return SYMB_VARIABLE; }

private:
	int _value;
};

class SymbFunction: public Symbol {
public:
	SymbFunction();
	virtual ~SymbFunction();
	int exec();
	SYMBTYPE type() { return SYMB_FUNCTION; }

private:
	std::vector<SymbVariable> _args;
	std::vector<Expr*> _process;
};

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();

	void add_variable(std::string id, int value = INT_MAX);
	void add_function(std::string id, Expr *process);

	int searchById(std::string id) {
		for(int i = 0; i < _symbols.size(); i++) {
			if(_symbols[i].id() == id) return i;
		}
		return -1; // not found
	}

	SYMBTYPE type(int id) {
		if(id < 0 || _symbols.size() <= id)
			throw string(__func__) + string(": out of range");
		return _symbols[id].type();
	}

private:
	std::vector<Symbol> _symbols;
};

#endif // __SYMB_H__
