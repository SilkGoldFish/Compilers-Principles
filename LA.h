#pragma once
#include<unordered_map>
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

unordered_map<string, int> Id;

unordered_map<string, int> Const;

vector<string> RW = { " ","program","const","var","procedure","begin","end","if",
					  "then","else","while","do","call","read","write","odd" };       //15 identifier

fstream file("source.txt", ios::in);

int row = 0, col = 0;        //row index and col index

void GetChar(char& ch) {
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
			row += 7;
		}
		GetChar(ch);
	}
}

void Concat(string& Sym, const char& ch) {
	Sym += ch;
}

bool IsLetter(const char& ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}

bool IsDigit(const char& ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	else {
		return false;
	}
}

int Reserve(const string& Sym) {
	for (int i = 0; i < RW.size(); i++) {
		if (Sym == RW[i]) {
			return i;
		}
	}
	return 0;
}

void Retract(char& ch) {
	file.seekg(-1, ios::cur);
	ch = ' ';
	col--;
}

void InsertId(const string& Sym) {
	Id.insert(pair<string, int>(Sym, Id.size()));
}

void InsertConst(const string& Sym) {
	Const.insert(pair<string, int>(Sym, Const.size()));
}

void LexicalError(int mode, const string& Sym) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	switch (mode) {
	case 1:cout << "YOU'VE FORGOTTEN TO INPUT A '=' AFTER ':' AT ROW:" << row << " COL:" << col - 1 << endl; break;
	case 2:cout << "YOU'VE INPUT AN ILLEGAL WORD AT ROW:" << row << " COL:" << col - Sym.size() << endl; break;
	case 3:cout << "YOU'VE INPUT A WRONG WORD(STARTS WITH DIGITS) AT ROW:" << row << " COL:" << col - Sym.size() << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
			LexicalError(3, Sym);	//YOU'VE INPUT A WRONG WORD(STARTS WITH DIGITS)
		}
		Retract(ch);
		InsertConst(Sym);
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
		exit(0);
	}
	else {
		while (ch < 0) {
			Concat(Sym, ch);
			GetChar(ch);
		}
		Retract(ch);
		LexicalError(2, Sym);	//YOU'VE INPUT AN ILLEGAL WORD
	}
}

void Back(string& Sym) {
	file.clear();
	file.seekg(-(int)Sym.size(), ios::cur);
}
