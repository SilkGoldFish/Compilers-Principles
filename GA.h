#pragma once
#include"LA.h"

void _prog(string& Sym);
void _block(string& Sym);
void _condecl(string& Sym);
void _const(string& Sym);
void _vardecl(string& Sym);
void _proc(string& Sym);
void _body(string& Sym);
void _statement(string& Sym);
void _lexp(string& Sym);
void _exp(string& Sym);
void _term(string& Sym);
void _factor(string& Sym);
bool IsLop(const string& Sym);
bool IsAop(const string& Sym);
bool IsMop(const string& Sym);
bool IsId(const string& Sym);
bool IsInteger(const string& Sym);
void GrammarError(int mode, string& Sym);

void _prog(string& Sym) {//<prog> -> program <id>;<block>
	cout << "prog analyzation begins" << endl;
	if (Sym == "program") {
		Advance(Sym);
		if (IsId(Sym)) {
			Advance(Sym);
			if (Sym == ";") {
				Advance(Sym);
				_block(Sym);
				cout << "prog analyzation ends successfully" << endl;
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError(1, Sym);
	}
}

void _block(string& Sym) {//<block> -> [<condecl>][<vardecl>][<proc>]<body>
	cout << "block analyzation begins" << endl;
	if (Sym == "const") {
		_condecl(Sym);
		Advance(Sym);
	}
	if (Sym == "var") {
		_vardecl(Sym);
		Advance(Sym);
	}
	if (Sym == "procedure") {
		_proc(Sym);
		Advance(Sym);
	}
	_body(Sym);
	cout << "block analyzation ends successfully" << endl;
}

void _condecl(string& Sym) {//<condecl> -> const <const>{,<const>};
	cout << "condecl analyzation begins" << endl;
	if (Sym == "const") {
		Advance(Sym);
		_const(Sym);
		Advance(Sym);
		while (Sym == ",") {
			Advance(Sym);
			_const(Sym);
			Advance(Sym);
		}
		if (Sym == ";") {
			cout << "condecl analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _const(string& Sym) {	//<const> -> <id>:=<integer>
	cout << "const analyzation begins" << endl;
	if (IsId(Sym)) {
		Advance(Sym);
		if (Sym == ":=") {
			Advance(Sym);
			if (IsInteger(Sym)) {
				cout << "const analyzation ends successfully" << endl;
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _vardecl(string& Sym) {	//<vardecl> -> var <id>{,<id>};
	cout << "vardecl analyzation begins" << endl;
	if (Sym == "var") {
		Advance(Sym);
		if (IsId(Sym)) {
			Advance(Sym);
			while (Sym == ",") {
				Advance(Sym);
				if (IsId(Sym)) {
					Advance(Sym);
				}
				else{
					//GrammarError();
				}
			}
			if (Sym == ";") {
				cout << "vardecl analyzation ends successfully" << endl;
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _proc(string& Sym) {	//<proc> -> procedure <id>（[<id>{,<id>}]）;<block>{;<proc>}
	cout << "proc analyzation begins" << endl;
	if (Sym == "procedure") {
		Advance(Sym);
		if (IsId(Sym)) {
			Advance(Sym);
			if (Sym == "(") {
				Advance(Sym);
				if (IsId(Sym)) {
					Advance(Sym);
					while (Sym == ",") {
						Advance(Sym);
						if (IsId(Sym)) {
							Advance(Sym);
						}
						else {
							//GrammarError();
						}
					}
				}
				if (Sym == ")") {
					Advance(Sym);
					if (Sym == ";") {
						Advance(Sym);
						_block(Sym);
						Advance(Sym);
						while (Sym == ";") {
							Advance(Sym);
							_proc(Sym);
							Advance(Sym);
						}
						Back(Sym);
						cout << "proc analyzation ends successfully" << endl;
					}
					else {
						//GrammarError();
					}
				}
				else {
					//GrammarError();
				}
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _body(string& Sym) {  //<body> -> begin <statement>{;<statement>}end
	cout << "body analyzation begins" << endl;
	if (Sym == "begin") {
		Advance(Sym);
		_statement(Sym);
		Advance(Sym);
		while (Sym == ";") {
			Advance(Sym);
			_statement(Sym);
			Advance(Sym);
		}
		if (Sym == "end") {
			cout << "body analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _statement(string& Sym) {
	cout << "statement analyzation begins" << endl;
	if (IsId(Sym)) {	//<statement> -> <id> := <exp>
		Advance(Sym);
		if (Sym == ":=") {
			Advance(Sym);
			_exp(Sym);
			cout << "statement analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else if (Sym == "if") {		//<statement> -> if <lexp> then <statement>[else <statement>]
		Advance(Sym);
		_lexp(Sym);
		Advance(Sym);
		if (Sym == "then") {
			Advance(Sym);
			_statement(Sym);
			Advance(Sym);
			if (Sym == "else") {
				Advance(Sym);
				_statement(Sym);
			}
			else {
				Back(Sym);
			}
			cout << "statement analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else if (Sym == "while") {		//<statement> -> while <lexp> do <statement>
		Advance(Sym);
		_lexp(Sym);
		Advance(Sym);
		if (Sym == "do") {
			Advance(Sym);
			_statement(Sym);
			cout << "statement analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else if (Sym == "call") {		//<statement> -> call <id>（[<exp>{,<exp>}]）
		Advance(Sym);
		if (IsId(Sym)) {
			Advance(Sym);
			if (Sym == "(") {
				Advance(Sym);
				if (IsAop(Sym) || IsId(Sym) || IsInteger(Sym) || Sym == "(") {
					_exp(Sym);
					Advance(Sym);
					while (Sym == ",") {
						Advance(Sym);
						_exp(Sym);
						Advance(Sym);
					}
				}
				if (Sym == ")") {
					cout << "statement analyzation ends successfully" << endl;
				}
				else {
					//GrammarError();
				}
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else if (Sym == "begin") {		//<statement> -> <body>
		_body(Sym);
		cout << "statement analyzation ends successfully" << endl;
	}
	else if (Sym == "read") {		//<statement> -> read (<id>{，<id>})
		Advance(Sym);
		if (Sym == "(") {
			Advance(Sym);
			if (IsId(Sym)) {
				Advance(Sym);
				while (Sym == ",") {
					Advance(Sym);
					if (IsId(Sym)) {
						Advance(Sym);
					}
					else {
						//GrammarError();
					}
				}
				if (Sym == ")") {
					cout << "statement analyzation ends successfully" << endl;
				}
				else {
					//GrammarError();
				}
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else if (Sym == "write") {		//<statement> -> write (<exp>{,<exp>})
		Advance(Sym);
		if (Sym == "(") {
			Advance(Sym);
			_exp(Sym);
			Advance(Sym);
			while (Sym == ",") {
				Advance(Sym);
				_exp(Sym);
				Advance(Sym);
			}
			if (Sym == ")") {
				cout << "statement analyzation ends successfully" << endl;
			}
			else {
				//GrammarError();
			}
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

void _lexp(string& Sym) {	//<lexp> -> <exp> <lop> <exp>|odd <exp>
	cout << "lexp analyzation begins" << endl;
	if (Sym == "odd") {
		Advance(Sym);
		_exp(Sym);
		cout << "lexp analyzation ends successfully" << endl;
	}
	else {
		_exp(Sym);
		Advance(Sym);
		if (IsLop(Sym)) {
			Advance(Sym);
			_exp(Sym);
			cout << "lexp analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
}

void _exp(string& Sym) {	//<exp> -> [+|-]<term>{<aop><term>}
	cout << "exp analyzation begins" << endl;
	if (IsAop(Sym)) {
		Advance(Sym);
	}
	_term(Sym);
	Advance(Sym);
	while (IsAop(Sym)) {
		Advance(Sym);
		_term(Sym);
		Advance(Sym);
	}
	Back(Sym);
	cout << "exp analyzation ends successfully" << endl;
}

void _term(string& Sym) {		//<term> -> <factor>{<mop><factor>}
	cout << "term analyzation begins" << endl;
	_factor(Sym);
	Advance(Sym);
	while (IsMop(Sym)) {
		Advance(Sym);
		_factor(Sym);
		Advance(Sym);
	}
	Back(Sym);
	cout << "term analyzation ends successfully" << endl;
}

void _factor(string& Sym) {
	cout << "factor analyzation begins" << endl;
	if (IsId(Sym) || IsInteger(Sym)) {     //<factor> -> <id>|<integer>
		cout << "factor analyzation ends successfully" << endl;
	}
	else if (Sym == "(") {   //<factor> -> (<exp>)
		Advance(Sym);
		_exp(Sym); 
		Advance(Sym);
		if (Sym == ")") {
			cout << "factor analyzation ends successfully" << endl;
		}
		else {
			//GrammarError();
		}
	}
	else {
		//GrammarError();
	}
}

bool IsLop(const string& Sym) {     //<lop> -> =|<>|<|<=|>|>=
	if (Sym == "=" || Sym == "<>" || Sym == "<" || Sym == "<=" || Sym == ">" || Sym == ">=") {
		return true;
	}
	else {
		return false;
	}
}

bool IsAop(const string& Sym) {     //<aop> -> +|-
	if (Sym == "+" || Sym == "-") {
		return true;
	}
	else {
		return false;
	}
}

bool IsMop(const string& Sym) {     //<mop> -> *|/
	if (Sym == "*" || Sym == "/") {
		return true;
	}
	else {
		return false;
	}
}

bool IsId(const string& Sym) {    //<id> -> l{l|d}
	if (Id.find(Sym) != Id.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool IsInteger(const string& Sym) {     //<integer> -> d{d}
	if (Const.find(Sym) != Const.end()) {
		return true;
	}
	else {
		return false;
	}
}

void GrammarError(int mode, string& Sym) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	switch (mode) {
	case 1:break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
