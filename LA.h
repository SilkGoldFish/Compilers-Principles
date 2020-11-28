#pragma once
#include<unordered_map>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#define RW_NUM 16
using namespace std;

unordered_map<string, int> Id;

unordered_map<string, int> Const;

const string RW[16] = { " ","program","const","var","procedure","begin","end","if",
					  "then","else","while","do","call","read","write","odd" };       //15 identifier

fstream file("source.txt", ios::in);

int row = 0, col = 0;        //row index and col index

inline void GetChar(char& ch);
void GetBC(char& ch);
inline void Concat(string& Sym, const char& ch);
inline bool IsLetter(const char& ch);
inline bool IsDigit(const char& ch);
int Reserve(const string& Sym);
inline void Retract(char& ch);
inline void InsertId(const string& Sym);
inline void InsertConst(const string& Sym);
void LexicalError(int mode, const string& Sym);
void Advance(string& Sym);
inline void Back(string& Sym);
inline void SetPrintColorWhite();
inline void SetPrintColorRed();
inline bool IsLop(const string& Sym);
inline bool IsAop(const string& Sym);
inline bool IsMop(const string& Sym);
inline bool IsId(const string& Sym);
inline bool IsInteger(const string& Sym);
inline bool IsContained(const string& Goal, const string& Sym);
bool IsString(const string& Goal, const string& Sym);

inline void GetChar(char& ch) {
	ch = file.get();
	col++;
}

void GetBC(char& ch) {
	while (ch == ' ' || ch == '\n' || ch == '\t') {
		if (ch == ' ') {
			//
		}
		else if (ch == '\n') {
			col = 0;
			++row;
		}
		else if (ch == '\t') {
			col += 7;
		}
		GetChar(ch);
	}
}

inline void Concat(string& Sym, const char& ch) {
	Sym += ch;
}

inline bool IsLetter(const char& ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}

inline bool IsDigit(const char& ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	else {
		return false;
	}
}

int Reserve(const string& Sym) {
	for (int i = 0; i < RW_NUM; i++) {
		if (Sym == RW[i]) {
			return i;
		}
	}
	return 0;
}

inline void Retract(char& ch) {
	file.seekg(-1, ios::cur);
	ch = ' ';
	col--;
}

inline void InsertId(const string& Sym) {
	Id.insert(pair<string, int>(Sym, Id.size()));
}

inline void InsertConst(const string& Sym) {
	Const.insert(pair<string, int>(Sym, Const.size()));
}

void LexicalError(int mode, const string& Sym) {
	SetPrintColorRed();
	switch (mode) {
	case 1:cout << "[LEXICAL ERROR]  YOU'VE FORGOTTEN TO INPUT A '=' AFTER ':' AT ROW:" << row << " COL:" << col << endl; break;
	case 2:cout << "[LEXICAL ERROR]  YOU'VE INPUT AN ILLEGAL WORD AT ROW:" << row << " COL:" << col - Sym.size() << endl; break;
	case 3:cout << "[LEXICAL ERROR]  YOU'VE INPUT A WRONG WORD(STARTS WITH DIGITS) AT ROW:" << row << " COL:" << col - Sym.size() << endl;
	}
	SetPrintColorWhite();
}

void Advance(string& Sym) {
	char ch;
	Sym = "";
	GetChar(ch);
	GetBC(ch);
	if (IsLetter(ch)) {
		while (IsLetter(ch) || IsDigit(ch)) {
			Concat(Sym, ch);
			GetChar(ch);
		}
		Retract(ch);
		const int code = Reserve(Sym);
		if (!code) {
			InsertId(Sym);
		}
	}
	else if (IsDigit(ch)) {
		while (IsDigit(ch)) {
			Concat(Sym, ch);
			GetChar(ch);
		}
		if (IsLetter(ch)) {
			while (IsLetter(ch)) {
				Concat(Sym, ch);
				GetChar(ch);
			}
			Retract(ch);
			InsertId(Sym);
			LexicalError(3, Sym);	//YOU'VE INPUT A WRONG WORD(STARTS WITH DIGITS)
		}
		else {
			Retract(ch);
			InsertConst(Sym);
		}
	}
	else if (ch == ':') {
		GetChar(ch);
		if (ch != '=') {
			Retract(ch);
			LexicalError(1, Sym);	//YOU'VE FORGOTTEN TO INPUT A '=' AFTER ':'
		}
		Sym = ":=";
	}
	else if (ch == '=') {
		Sym = "=";
	}
	else if (ch == '+') {
		Sym = "+";
	}
	else if (ch == '-') {
		Sym = "-";
	}
	else if (ch == '*') {
		Sym = "*";
	}
	else if (ch == '/') {
		Sym = "/";
	}
	else if (ch == ';') {
		Sym = ";";
	}
	else if (ch == '(') {
		Sym = "(";
	}
	else if (ch == ')') {
		Sym = ")";
	}
	else if (ch == '<') {
		GetChar(ch);
		if (ch == '=') {
			Sym = "<=";
		}
		else if (ch == '>') {
			Sym = "<>";
		}
		else {
			Retract(ch);
			Sym = "<";
		}
	}
	else if (ch == '>') {
		GetChar(ch);
		if (ch == '=') {
			Sym = ">=";
		}
		else {
			Retract(ch);
			Sym = ">";
		}
	}
	else if (ch == ',') {
		Sym = ",";
	}
	else if (ch == -1) {
		exit(0);	//(only used in LA test)
	}
	else {
		while (ch < 0) {
			Concat(Sym, ch);
			GetChar(ch);
		}
		Retract(ch);
		LexicalError(2, Sym);	//YOU'VE INPUT AN ILLEGAL WORD
		Advance(Sym);
	}
}

inline void Back(string& Sym) {
	file.clear();
	file.seekg(-(int)Sym.size(), ios::cur);
	col -= Sym.size();
}

inline void SetPrintColorWhite() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

inline void SetPrintColorRed() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
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

inline bool IsContained(const string& Goal, const string& Sym) {
	if (Goal.find(Sym) != string::npos) {
		return true;
	}
	else {
		return false;
	}
}

bool IsString(const string& Goal, const string& Sym) {	//only can detect three cases
	if (Goal == Sym) {	//completely the same or Sym is part of the Goal
		return true;
	}
	else if (IsContained(Goal, Sym)) {
		SetPrintColorRed();
		cout << "[SPELL ERROR]  YOU'VE INPUT THE WRONG SPELLING OF '" << Goal << "' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
		SetPrintColorWhite();
		return true;
	}
	else {	//Sym loses some letters from Goal or differs a letter
		int i = 0, j = 0, k = 0, equal = 0;
		while (i < Sym.size()) {
			if (Sym[i] == Goal[j] || Sym[i] == Goal[j] + 32 || Sym[i] == Goal[j] - 32) {
				++equal; ++i; ++j;
			}
			else {
				for (k = j; k < Goal.size(); k++) {
					if (Goal[k] == Sym[i]) {
						break;
					}
				}
				if (k < Goal.size()) {
					j = k;
				}
				else {
					if (i < Sym.size() - 1) {
						++i;
					}
					else {
						break;
					}
				}
			}
		}
		if (equal >= Sym.size() - 1) {
			SetPrintColorRed();
			cout << "[SPELL ERROR]  YOU'VE INPUT THE WRONG SPELLING OF '" << Goal << "' AT ROW:" << row << " COL:" << col - Sym.size() << endl;
			SetPrintColorWhite();
			return true;
		}
		else {
			return false;
		}
	}
}

void TestLA() {	//function for testing LA
	string Sym;
	while (true) {
		Advance(Sym);
		string print = "<";
		print += Sym + ",";
		if (Id.find(Sym) != Id.end()) {
			print += to_string(Id[Sym]) + ">";
		}
		else if (Const.find(Sym) != Const.end()) {
			print += to_string(Const[Sym]) + ">";
		}
		else {
			print += "->";
		}
		cout << print << endl;
	}
}
