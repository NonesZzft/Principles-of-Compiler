#include <bits/stdc++.h>
using namespace std;

#ifndef _TOKEN_
#define _TOKEN_

#endif

typedef enum {
	START, INNUM, INDOUBLE, INID, DONE,
	INCOMMENT1, INCOMMENT2, INCOMMENT3, INCOMMENT4,
	INCOMPARE1, INCOMPARE2, INCOMPARE3, INCOMPARE4
} StateType;
typedef enum {
	/* book-keeping tokens */
	ENDFILE, ERROR,
	/* reserved words */
	INT, DOUBLE, VOID,
	IF, ELSE, WHILE, FOR, RETURN,
	/* multicharacter tokens */
	ID, NUM,
	/* special symbols */
	ASSIGN,EQ,NEQ,LT,GT,LTEQ,GTEQ,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,COLON,COMMA,
	LBRACKET,RBRACKET,LBRACE,RBRACE //方括号花括号
} TokenType;

bool digit(char ch) {
	if(ch>='0' && ch<='9') return true;
	return false;
}
bool letter(char ch) {
	if(ch>='a' && ch<='z') return true;
	if(ch>='A' && ch<='Z') return true;
	if(ch=='_') return true;
	return false;
}

// 大小写转换
// char UP(char ch) {
// 	return (ch-'A')%32 + 'A';
// }
// char LOW(char ch) {
// 	if(ch<='Z') ch = ch - 'A' + 'a';
// 	return ch;
// }

bool back = false, reserve;
char ch;
string tokenString;
TokenType getToken() {
	tokenString.clear();
	StateType state = START;
	TokenType res;
	// reserve = false;
	while(state != DONE) {
		if(!back) ch = getchar();
		else back = false;
		bool save = true;
		switch(state) {
			case START:
				if(digit(ch)) state = INNUM;
				else if(letter(ch)) state = INID;
				else if(ch=='/') {
					state = INCOMMENT1;
					save = false;
				}
				else if(ch==' '||ch=='\t') save = false;
				else if(ch=='\n') { save = false; lineno++; }
				else if(ch=='<') state = INCOMPARE1;
				else if(ch=='=') state = INCOMPARE2;
				else if(ch=='>') state = INCOMPARE3;
				else if(ch=='!') state = INCOMPARE4;
				else {
					state = DONE;
					if(ch==EOF) {
						save = false;
						res = ENDFILE;
					}
					else if(ch=='+') res = PLUS;
					else if(ch=='-') res = MINUS;
					else if(ch=='*') res = TIMES;
					// '/'有特殊含义
					else if(ch=='(') res = LPAREN;
					else if(ch==')') res = RPAREN;
					else if(ch=='[') res = LBRACKET;
					else if(ch==']') res = RBRACKET;
					else if(ch=='{') res = LBRACE;
					else if(ch=='}') res = RBRACE;
					else if(ch==';') res = SEMI;
					else if(ch==':') res = COLON;
					else if(ch==',') res = COMMA;
					else res = ERROR;
				}
				break;
			case INCOMMENT1:
				save = false;
				if(ch=='/') state = INCOMMENT2;
				else if(ch=='*') state = INCOMMENT3;
				else {
					state = DONE;
					back = true;
					res = OVER;
				}
				break;
			case INCOMMENT2:
				save =false;
				if(ch=='\n') { state = START; lineno++; }
				else if(ch==EOF) {
					state = DONE;
					res = ENDFILE;
				}
				// else if(letter(ch)) ch = UP(ch);
				break;
			case INCOMMENT3:
				save = false;
				if(ch=='*') state = INCOMMENT4;
				else if(ch==EOF) {
					state = DONE;
					res = ENDFILE;
				}
				// else if(letter(ch)) ch = UP(ch);
				break;
			case INCOMMENT4:
				save = false;
				if(ch=='/') state = START;
				else if(ch==EOF) {
					state = DONE;
					res = ENDFILE;
				}
				else if(ch=='*') break;
				else {
					state = INCOMMENT4;
					// if(letter(ch)) ch = UP(ch);
				}
				break;
			case INCOMPARE1:
				state = DONE;
				if(ch=='=') res = LTEQ;
				else {
					save = false;
					back = true;
					res = LT;
				}
				break;
			case INCOMPARE2:
				state = DONE;
				if(ch=='=') res = EQ;
				else {
					save = false;
					back = true;
					res = ASSIGN;
				}
				break;
			case INCOMPARE3:
				state = DONE;
				if(ch=='=') res = GTEQ;
				else {
					save = false;
					back = true;
					res = GT;
				}
				break;
			case INCOMPARE4:
				state = DONE;
				if(ch=='=') res = NEQ;
				else {
					save = false;
					back = true;
					res = NEQ;
				}
				break;
			case INNUM:
				if(ch=='.') {
					state = INDOUBLE;
				}
				else if(!digit(ch)) {
					back = true;
					save = false;
					state = DONE;
					res = NUM;
				}
				break;
			case INDOUBLE:
				if(!digit(ch)) {
					back = true;
					save = false;
					state = DONE;
					res = NUM;
				}
				break;
			case INID:
				if(!letter(ch)&&!digit(ch)) {
					back = true;
					save = false;
					state = DONE;
					res = ID;
				}
				break;
			case DONE:
			default:
				state = DONE;
				res = ERROR;
				break;
		}
		if(save) tokenString += ch;
		if(state==DONE) {
			if(res==ID) {
				if(tokenString=="if") {res=IF;break;}
				if(tokenString=="else") {res=ELSE;break;}
				if(tokenString=="return") {res=RETURN;break;}
				if(tokenString=="int") {res=INT;break;}
				if(tokenString=="void") {res=VOID;break;}
				if(tokenString=="double") {res=DOUBLE;break;}
				if(tokenString=="while") {res=WHILE;break;}
				if(tokenString=="for") {res=FOR;break;}
			}
		}
	}
	return res;
}