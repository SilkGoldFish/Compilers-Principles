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
inline bool IsLop(const string& Sym);
inline bool IsAop(const string& Sym);
inline bool IsMop(const string& Sym);
inline bool IsId(const string& Sym);
inline bool IsInteger(const string& Sym);
void GrammarError(int mode, string& Sym);

void _prog(string& Sym) {	//<prog> -> program <id>;<block>
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
				GrammarError(3, Sym);	//lacks of ';'
			}
		}
		else {
			GrammarError(2, Sym);	//lacks of 'id'
		}
	}
	else {
		GrammarError(1, Sym);	//lacks of 'program'
	}
}

void _block(string& Sym) {	//<block> -> [<condecl>][<vardecl>][<proc>]<body>
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

void _condecl(string& Sym) {	//<condecl> -> const <const>{,<const>};
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
			GrammarError(5, Sym);	//lacks of ';'
		}
	}
	else {
		GrammarError(4, Sym);	//unknown error
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
				GrammarError(8, Sym);	//lacks of 'integer'
			}
		}
		else {
			GrammarError(7, Sym);	//lacks of ':='
		}
	}
	else {
		GrammarError(6, Sym);	//lacks of 'id'
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
				else {
					GrammarError(9, Sym);	//lacks of 'id'
				}
			}
			if (Sym == ";") {
				cout << "vardecl analyzation ends successfully" << endl;
			}
			else {
				GrammarError(10, Sym);	//lacks of ';'
			}
		}
		else {
			GrammarError(9, Sym);	//lacks of 'id'
		}
	}
	else {
		GrammarError(4, Sym);	//unknown error
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
							GrammarError(14, Sym);	//lacks of 'id'
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
						GrammarError(15, Sym);	//lacks of ';'
					}
				}
				else {
					GrammarError(13, Sym);	//lacks of ')'
				}
			}
			else {
				GrammarError(12, Sym);	//lacks of '('
			}
		}
		else {
			GrammarError(11, Sym);	//lacks of 'id'
		}
	}
	else {
		GrammarError(4, Sym);	//unknown error
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
			GrammarError(17, Sym);	//lacks of ';' || lacks of 'end'
		}
	}
	else {
		GrammarError(16, Sym);	//lacks of 'begin' (only feasible in <body> included in <block>)
	}
}

void _statement(string& Sym) {	//the first word missing of each branch can't be detected
	cout << "statement analyzation begins" << endl;
	if (IsId(Sym)) {	//<statement> -> <id> := <exp>
		Advance(Sym);
		if (Sym == ":=") {
			Advance(Sym);
			_exp(Sym);
			cout << "statement analyzation ends successfully" << endl;
		}
		else {
			GrammarError(18, Sym);	//lacks of ':='
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
			GrammarError(19, Sym);	//lacks of 'then' 
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
			GrammarError(20, Sym);	//lacks of 'do'	
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
					GrammarError(23, Sym);	//lacks of ')'
				}
			}
			else {
				GrammarError(22, Sym);	//lacks of '('
			}
		}
		else {
			GrammarError(21, Sym);	//lacks of 'id'
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
						GrammarError(25, Sym);	//lacks of 'id'
					}
				}
				if (Sym == ")") {
					cout << "statement analyzation ends successfully" << endl;
				}
				else {
					GrammarError(26, Sym);	//lacks of ')'
				}
			}
			else {
				GrammarError(25, Sym);	//lacks of 'id'
			}
		}
		else {
			GrammarError(24, Sym);	//lacks of '('
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
				GrammarError(28, Sym);	//lacks of ')'
			}
		}
		else {
			GrammarError(27, Sym);	//lacks of '('
		}
	}
	else {
		GrammarError(4, Sym);	//unknown error
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
			GrammarError(29, Sym);	//lacks of a 'lop'
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
			GrammarError(30, Sym);	//lacks of ')'
		}
	}
	else {
		GrammarError(4, Sym);	//unknown error
	}
}

inline bool IsLop(const string& Sym) {     //<lop> -> =|<>|<|<=|>|>=
	if (Sym == "=" || Sym == "<>" || Sym == "<" || Sym == "<=" || Sym == ">" || Sym == ">=") {
		return true;
	}
	else {
		return false;
	}
}

inline bool IsAop(const string& Sym) {     //<aop> -> +|-
	if (Sym == "+" || Sym == "-") {
		return true;
	}
	else {
		return false;
	}
}

inline bool IsMop(const string& Sym) {     //<mop> -> *|/
	if (Sym == "*" || Sym == "/") {
		return true;
	}
	else {
		return false;
	}
}

inline bool IsId(const string& Sym) {    //<id> -> l{l|d}
	if (Id.find(Sym) != Id.end()) {
		return true;
	}
	else {
		return false;
	}
}

inline bool IsInteger(const string& Sym) {     //<integer> -> d{d}
	if (Const.find(Sym) != Const.end()) {
		return true;
	}
	else {
		return false;
	}
}

void GrammarError(int mode, string& Sym) {
	SetPrintColorRed();
	switch (mode) {
	case 1:	//from <prog>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF RW 'PROGRAM' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (IsId(Sym)) {
			Advance(Sym);
			if (Sym == ";") {
				Advance(Sym);
				_block(Sym);
				cout << "prog analyzation ends successfully" << endl;
			}
			else {
				GrammarError(3, Sym);
			}
		}
		else {
			GrammarError(2, Sym);
		}
		break;
	case 2:	//from <prog>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (Sym == ";") {
			Advance(Sym);
			_block(Sym);
			cout << "prog analyzation ends successfully" << endl;
		}
		else {
			GrammarError(3, Sym);
		}
		break;
	case 3:	//from <prog>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ';' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		_block(Sym);
		cout << "prog analyzation ends successfully" << endl;
		break;
	case 4:	//unknown error
		cout << "[GRAMMAR ERROR]  UNKNOWN ERROR AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		exit(0);
		break;
	case 5:	//from <condecl>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ';' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 6:	///from <const>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (Sym == ":=") {
			Advance(Sym);
			if (IsInteger(Sym)) {
				cout << "const analyzation ends successfully" << endl;
			}
			else {
				GrammarError(8, Sym);	//lacks of 'integer'
			}
		}
		else {
			GrammarError(7, Sym);	//lacks of ':='
		}
		break;
	case 7:	//from <const>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ':=' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (IsInteger(Sym)) {
			cout << "const analyzation ends successfully" << endl;
		}
		else {
			GrammarError(8, Sym);	//lacks of 'integer'
		}
		break;
	case 8:	//from <const>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN INTEGER AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 9:	//from <vardecl>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		while (Sym == ",") {
			Advance(Sym);
			if (IsId(Sym)) {
				Advance(Sym);
			}
			else {
				GrammarError(9, Sym);
			}
		}
		if (Sym == ";") {
			cout << "vardecl analyzation ends successfully" << endl;
		}
		else {
			GrammarError(10, Sym);
		}
		break;
	case 10:	//from <vardecl>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ';' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 11:	//from <proc>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
						GrammarError(14, Sym);	//lacks of 'id'
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
					GrammarError(15, Sym);	//lacks of ';'
				}
			}
			else {
				GrammarError(13, Sym);	//lacks of ')'
			}
		}
		else {
			GrammarError(12, Sym);	//lacks of '('
		}
		break;
	case 12:	//from <proc>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A '(' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (IsId(Sym)) {
			Advance(Sym);
			while (Sym == ",") {
				Advance(Sym);
				if (IsId(Sym)) {
					Advance(Sym);
				}
				else {
					GrammarError(14, Sym);	//lacks of 'id'
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
				GrammarError(15, Sym);	//lacks of ';'
			}
		}
		else {
			GrammarError(13, Sym);	//lacks of ')'
		}
		break;
	case 13:	//from <proc>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ')' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
			GrammarError(15, Sym);	//lacks of ';'
		}
		break;
	case 14:	//from <proc>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		while (Sym == ",") {
			Advance(Sym);
			if (IsId(Sym)) {
				Advance(Sym);
			}
			else {
				GrammarError(14, Sym);	//lacks of 'id'
			}
		}
		break;
	case 15:	//from <proc>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ';' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		_block(Sym);
		Advance(Sym);
		while (Sym == ";") {
			Advance(Sym);
			_proc(Sym);
			Advance(Sym);
		}
		Back(Sym);
		cout << "proc analyzation ends successfully" << endl;
		break;
	case 16:	//from <body>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF RW 'BEGIN' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
			GrammarError(17, Sym);
		}
		break;
	case 17:	//from <body>	can not solve the case of two continuous begin-end in one <body> 
		if (Sym == "begin") {
			cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF RW 'END' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
			SetPrintColorWhite();
			Back(Sym);
		}
		else if (IsId(Sym) || Sym == "if" || Sym == "while" || Sym == "call" || Sym == "read" || Sym == "write") {
			cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ';' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
			SetPrintColorWhite();
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
				GrammarError(17, Sym);	//lacks of ';' || lacks of 'end'
			}
		}
		break;
	case 18:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ':=' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		_exp(Sym);
		cout << "statement analyzation ends successfully" << endl;
		break;
	case 19:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF RW 'THEN' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
		break;
	case 20:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF RW 'DO' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		_statement(Sym);
		cout << "statement analyzation ends successfully" << endl;
		break;
	case 21:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
				GrammarError(23, Sym);	//lacks of ')'
			}
		}
		else {
			GrammarError(22, Sym);	//lacks of '('
		}
		break;
	case 22:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A '(' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
			GrammarError(23, Sym);	//lacks of ')'
		}
		break;
	case 23:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ')' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 24:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A '(' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		if (IsId(Sym)) {
			Advance(Sym);
			while (Sym == ",") {
				Advance(Sym);
				if (IsId(Sym)) {
					Advance(Sym);
				}
				else {
					GrammarError(25, Sym);	//lacks of 'id'
				}
			}
			if (Sym == ")") {
				cout << "statement analyzation ends successfully" << endl;
			}
			else {
				GrammarError(26, Sym);	//lacks of ')'
			}
		}
		else {
			GrammarError(25, Sym);	//lacks of 'id'
		}
		break;
	case 25:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF AN ID AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		while (Sym == ",") {
			Advance(Sym);
			if (IsId(Sym)) {
				Advance(Sym);
			}
			else {
				GrammarError(25, Sym);	//lacks of 'id'
			}
		}
		if (Sym == ")") {
			cout << "statement analyzation ends successfully" << endl;
		}
		else {
			GrammarError(26, Sym);	//lacks of ')'
		}
		break;
	case 26:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ')' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 27:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A '(' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
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
			GrammarError(28, Sym);	//lacks of ')'
		}
		break;
	case 28:	//from <statement>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ')' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	case 29:	//from <lexp>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A 'LOP' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		_exp(Sym);
		cout << "lexp analyzation ends successfully" << endl;
		break;
	case 30:	//from <factor>
		cout << "[GRAMMAR ERROR]  PROGRAM LACKS OF A ')' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		Back(Sym);
		break;
	}
}
