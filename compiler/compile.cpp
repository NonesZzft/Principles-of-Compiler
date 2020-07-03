#include <bits/stdc++.h>
using namespace std;

typedef enum {
	START, INCOMMENT, INNUM, INID, INASSIGN, DONE
} StateType;
typedef enum {
	/* book-keeping tokens */
	ENDFILE,ERROR,
	/* reserved words */
	IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
	/* multicharacter tokens */
	ID,NUM,
	/* special symbols */
	ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
} TokenType;

bool digit(char ch) {
	if(ch>='0' && ch<='9') return true;
	return false;
}
bool letter(char ch) {
	if(ch>='a' && ch<='z') return true;
	if(ch>='A' && ch<='Z') return true;
	return false;
}

bool back = false, biaoji;
char ch;
TokenType getToken(string &s) {
	StateType state = START;
	TokenType res;
	biaoji = false;
	while(state != DONE) {
		if(!back) ch = getchar();
		else back = false;
		bool save = true;
		switch(state) {
			case START:
				if(digit(ch)) state = INNUM;
				else if(letter(ch)) state = INID;
				else if(ch==':') state = INASSIGN;
				else if(ch=='{') {
					state = INCOMMENT;
					save = false;
				}
				else if(ch==' '||ch=='\t'||ch=='\n') save = false;
				else {
					state = DONE;
					if(ch==EOF) {
						save = false;
						res = ENDFILE;
					}
					else if(ch=='+') res = PLUS;
					else if(ch=='-') res = MINUS;
					else if(ch=='*') res = TIMES;
					else if(ch=='/') res = OVER;
					else if(ch=='=') res = EQ;
					else if(ch=='<') res = LT;
					else if(ch=='(') res = LPAREN;
					else if(ch==')') res = RPAREN;
					else if(ch==';') res = SEMI;
					else res = ERROR;
				}
				break;
			case INCOMMENT:
				save = false;
				if(ch==EOF) {
					state = DONE;
					res = ENDFILE;
				}
				else if(ch=='}') {
					state = START;
				}
				else if(letter(ch)) {
					ch = (ch-'A')%32 + 'A';
				}
				break;
			case INASSIGN:
				state = DONE;
				if(ch=='=') res = ASSIGN;
				else {
					back = true;
					save = false;
					res = ERROR;
				}
				break;
			case INNUM:
				if(!digit(ch)) {
					back = true;
					save = false;
					state = DONE;
					res = NUM;
				}
				break;
			case INID:
				if(!letter(ch)) {
					back = true;
					save = false;
					state = DONE;
					res = ID;
				}
				break;
			case DONE:
			default:
				puts("出错了！");
				state = DONE;
				res = ERROR;
				break;
		}
		if(save) s += ch;
		else if(!back&&ch!=EOF) cout << ch;
		if(state==DONE) {
			if(res==ID) {
				biaoji = true;
				if(s=="if") {res=IF;break;}
				if(s=="then") {res=THEN;break;}
				if(s=="else") {res=ELSE;break;}
				if(s=="end") {res=END;break;}
				if(s=="repeat") {res=REPEAT;break;}
				if(s=="until") {res=UNTIL;break;}
				if(s=="read") {res=READ;break;}
				if(s=="write") {res=WRITE;break;}
			}
		}
	}
	return res;
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	while(1) {
		string s;
		TokenType res = getToken(s);
		if(res==ENDFILE) break;
		if(res==ERROR) {
			puts("输入出错了！");
			break;
		}
		if(biaoji) {
			if(res==ID) transform(s.begin(), s.end(), s.begin(), ::tolower);
			else transform(s.begin(), s.end(), s.begin(), ::toupper);
		}
		cout << s;
	}

	return 0;
}