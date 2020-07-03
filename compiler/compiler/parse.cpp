#include <bits/stdc++.h>
using namespace std;

#ifndef _PARSE_
#define _PARSE_

#include "global.cpp"

#endif

// 函数声明

void match(TokenType expected);

TreeNode * program();
TreeNode * declaration_list();
TreeNode * declaration();
TreeNode * local_declarations();
TreeNode * params();
TreeNode * param();
TreeNode * statement_list();
TreeNode * statement();
TreeNode * expression_stmt();
TreeNode * compound_stmt();
TreeNode * selection_stmt();
TreeNode * iteration_stmt();
TreeNode * for_stmt();
TreeNode * return_stmt();
TreeNode * expression();
TreeNode * simple_expression();
TreeNode * additive_expression();
TreeNode * term();
TreeNode * factor();
TreeNode * arg_list();

TokenType token;

void match(TokenType expected) {
	if(token == expected) {
		token = getToken();
		// printToken(token, tokenString);
	}
	else {
		syntaxError("unexpected token -> ");
		printToken(token, tokenString);
	}
}

TreeNode * program() {
	token = getToken();
	TreeNode * t = declaration_list();
	if(token != ENDFILE) {
		syntaxError("Code ends before file\n");
	}
	return t;
}

TreeNode * declaration_list() {
	TreeNode * t = declaration();
	TreeNode * p = t;
	while(token == INT || token == VOID || token == DOUBLE) {
		TreeNode * q;
		q = declaration();
		if(q!=NULL) {
			if(t==NULL) t = p = q;
			else {
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

TreeNode * declaration() {
	TreeNode * t = NULL;
	TreeNode * pType = NULL;
	switch(token) {
		case INT:
			pType = newNode(IntK);
			match(INT);
			break;
		case VOID:
			pType = newNode(VoidK);
			match(VOID);
			break;
		case DOUBLE:
			pType = newNode(DoubleK);
			match(DOUBLE);
			break;
		default:
			return NULL;
	}
	TreeNode * pID = new TreeNode();
	if(token==ID) {
		pID = newNode(IdK);
		pID->name = tokenString;
		match(ID);
	}
	TreeNode * pVar=NULL, *pArr=NULL, *pConst=NULL, *pFun=NULL;
	switch(token) {
		case SEMI:
			match(SEMI);
			pVar = newNode(DeclK);
			pVar->child.push_back(pType);
			pVar->child.push_back(pID);
			t = pVar;
			break;
		case LBRACKET:
			match(LBRACKET);
			pVar = newNode(DeclK);
			pArr = newNode(ArrayK);
			pConst = newNode(ConstK);
			pConst->val = atoi(tokenString.c_str());
			pVar->child.push_back(pType);
			pVar->child.push_back(pArr);
			pArr->child.push_back(pID);
			pArr->child.push_back(pConst);
			t = pVar;
			match(NUM);
			match(RBRACKET);
			match(SEMI);
			break;
		case LPAREN:
			match(LPAREN);
			pFun = newNode(FunK);
			pFun->child.push_back(pType);
			pFun->name = pID->name;
			pFun->child.push_back(params());
			match(RPAREN);
			pFun->child.push_back(compound_stmt());
			t = pFun;
			break;
		default:
			syntaxError("unexpected token -> ");
			printToken(token, tokenString);
			token = getToken();
			break;
	}
	return t;
}

TreeNode * local_declarations() {
	TreeNode * t = declaration();
	TreeNode * p = t;
	while(token==INT || token==VOID || token==DOUBLE) {
		TreeNode * q = declaration();
		if(t!=NULL) {
			if(t==NULL) t = p = q;
			else {
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

TreeNode * params() {
	TreeNode * t = param();
	TreeNode * p = t;
	while(token == COMMA) {
		match(COMMA);
		TreeNode * q = param();
		if(q!=NULL) {
			if(t==NULL) t = p = q;
			else {
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

TreeNode * param() {
	TreeNode * t = NULL;
	TreeNode * type = NULL;
	switch(token) {
		case INT:
			type = newNode(IntK);
			match(INT);
			break;
		case VOID:
			type = newNode(VoidK);
			match(VOID);
			break;
		case DOUBLE:
			type = newNode(DoubleK);
			match(DOUBLE);
			break;
		default:
			syntaxError("unexpected token -> ");
			printToken(token, tokenString);
			token = getToken();
	}
	TreeNode * pid = NULL;
	if(token == ID) {
		pid = newNode(IdK);
		pid->name = tokenString;
		match(ID);
	}
	else {
		t = newNode(ParamK);
		t->child.push_back(type);
		return t;
	}
	TreeNode * pArr = NULL;
	switch(token) {
		case RPAREN:
		case COMMA:
			t = newNode(ParamK);
			t->child.push_back(type);
			t->child.push_back(pid);
			break;
		case LBRACKET:
			match(LBRACKET);
			match(RBRACKET);
			pArr = newNode(ArrayK);
			t->child.push_back(type);
			t->child.push_back(pArr);
			pArr->child.push_back(pid);
			break;
		default:
			syntaxError("unexpected token -> ");
			printToken(token, tokenString);
			token = getToken();
	}
	return t;
}

TreeNode * statement_list() {
	TreeNode * t = statement();
	TreeNode * p = t;
	while(token!=ENDFILE && token!=RBRACE) {
		TreeNode * q = statement();
		if(q!=NULL) {
			if(t==NULL) t = p = q;
			else {
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}

// 更改：可以是空语句
TreeNode * statement() {
	TreeNode * t = NULL;
	switch(token) {
		case IF: t = selection_stmt(); break;
		case WHILE: t = iteration_stmt(); break;
		case FOR: t = for_stmt(); break;
		case RETURN: t = return_stmt(); break;
		case LBRACE: t = compound_stmt(); break;
		case ID:
		case LPAREN:
		case NUM:
		case SEMI:
			t = expression_stmt(); break;
		case RBRACE:
			break;
		default:
			syntaxError("unexpected token -> ");
			printToken(token, tokenString);
			token = getToken();
	}
	return t;
}

TreeNode * expression_stmt() {
	TreeNode * t = newNode(ExpressionK);
	if(token == SEMI) {
		match(SEMI);
	}
	else {
		if(t!=NULL) t->child.push_back(expression());
		match(SEMI);
	}
	return t;
}

TreeNode * compound_stmt() {
	TreeNode * t = newNode(CompoundK);
	match(LBRACE);
	t->child.push_back(local_declarations());
	t->child.push_back(statement_list());
	match(RBRACE);
	return t;
}

TreeNode * selection_stmt() {
	TreeNode * t = newNode(SelectionK);
	match(IF);
	match(LPAREN);
	if(t != NULL) t->child.push_back(expression());
	match(RPAREN);
	if(t != NULL) t->child.push_back(statement());
	if(token == ELSE) {
		match(ELSE);
		if(t!=NULL) t->child.push_back(statement());
	}
	return t;
}

TreeNode * iteration_stmt() {
	TreeNode * t = newNode(IterationK);
	match(WHILE);
	match(LPAREN);
	if(t!=NULL) t->child.push_back(expression());
	match(RPAREN);
	if(t!=NULL) t->child.push_back(statement());
	return t;
}

TreeNode * for_stmt() {
	TreeNode * t = newNode(ForK);
	match(FOR);
	match(LPAREN);
	if(token==SEMI) {
		match(SEMI);
		t->child.push_back(newNode(EmptyK));
	}
	else {
		t->child.push_back(expression());
		match(SEMI);
	}
	if(token==SEMI) {
		match(SEMI);
		t->child.push_back(newNode(EmptyK));
	}
	else {
		t->child.push_back(expression());
		match(SEMI);
	}
	if(token==RPAREN) {
		match(RPAREN);
		t->child.push_back(newNode(EmptyK));
	}
	else {
		t->child.push_back(expression());
		match(RPAREN);
	}
	t->child.push_back(statement());
	return t;
}

TreeNode * return_stmt() {
	TreeNode * t = newNode(ReturnK);
	match(RETURN);
	if(token == SEMI) {
		match(SEMI);
	}
	else {
		if(t!=NULL) t->child.push_back(expression());
		match(SEMI);
	}
	return t;
}

TreeNode * expression() {
	TreeNode * t = NULL;
	if(token != ID) {
		t = simple_expression();
	}
	else {
		t = newNode(IdK);
		if(t!=NULL) t->name = tokenString;
		match(ID);
		if(token == LBRACKET) {
			match(LBRACKET);
			TreeNode * pArr = newNode(ArrayK);
			pArr->child.push_back(t);
			pArr->child.push_back(expression());
			match(RBRACKET);
			t = pArr;
		}
		if(token == ASSIGN) {
			TreeNode * p = newNode(OpK);
			if(p!=NULL) {
				p->child.push_back(t);
				p->op = token;
				match(token);
				p->child.push_back(expression());
				t = p;
			}
		}
		else if(token==EQ || token==NEQ || token==LT || token==GT || token==LTEQ || token==GTEQ) {
			TreeNode * p = newNode(OpK);
			if(p!=NULL) {
				p->child.push_back(t);
				p->op = token;
				t = p;
				match(token);
				t->child.push_back(additive_expression());
			}
		}
		else if(token==LPAREN) {
			match(LPAREN);
			TreeNode * p = newNode(FunK);
			p->name = t->name;
			// p->child.push_back(t);
			p->child.push_back(arg_list());
			t = p;
			match(RPAREN);
		}
		else if(token==PLUS || token==MINUS) {
			TreeNode * p = newNode(OpK);
			if(p!=NULL) {
				p->child.push_back(t);
				p->op = token;
				t = p;
				match(token);
				t->child.push_back(additive_expression());
			}
		}
		else if(token==TIMES || token==OVER) {
			TreeNode * p = newNode(OpK);
			if(p!=NULL) {
				p->child.push_back(t);
				p->op = token;
				t = p;
				match(token);
				t->child.push_back(term());
			}
		}
	}
	return t;
}

TreeNode * var() {
	TreeNode * t = NULL;
	match(ID);
	if(token == LBRACKET) {
		match(LBRACKET);
		t->child.push_back(expression());
		match(RBRACKET);
	}
	else {
		t->child.push_back(expression());
	}
	return t;
}

TreeNode * simple_expression() {
	TreeNode * t = additive_expression();
	if (token==LT || token==EQ || token==NEQ || token==GT || token==LTEQ || token==GTEQ) {
		TreeNode * p = newNode(OpK);
		if (p!=NULL) {
			p->child.push_back(t);
			p->op = token;
			t = p;
		}
		match(token);
		if (t!=NULL)
		t->child.push_back(additive_expression());
	}
	return t;
}

TreeNode * additive_expression() {
	TreeNode *t = term();
	while ((token == PLUS) || (token == MINUS)) {
		TreeNode *p = newNode(OpK);
		if (p != NULL) {
			p->child.push_back(t);
			p->op = token;
			t = p;
			match(token);
			t->child.push_back(term());
		}
	}
	return t;
}

TreeNode * term() {
	TreeNode *t = factor();
	while ((token == TIMES) || (token == OVER)) {
		TreeNode *p = newNode(OpK);
		if (p != NULL) {
			p->child.push_back(t);
			p->op = token;
			t = p;
			match(token);
			p->child.push_back(factor());
		}
	}
	return t;
}

TreeNode * factor() {
	TreeNode *t = NULL;
	switch (token) {
	case NUM:
		t = newNode(ConstK);
		if ((t != NULL) && (token == NUM))
			t->val = stod(tokenString);
		match(NUM);
		break;
	case ID:
		t = newNode(IdK);
		if(t != NULL) {
			t->name = tokenString;
		}
		match(ID);
		if(token == LPAREN) {
			match(LPAREN);
			TreeNode * p = newNode(FunK);
			p->name = t->name;
			// p->child.push_back(t);
			t = p;
			t->child.push_back(arg_list());
			match(RPAREN);
		}
		break;
	case LPAREN:
		match(LPAREN);
		t = expression();
		match(RPAREN);
		break;
	default:
		// syntaxError("unexpected token -> ");
		// printf("unexpected token -> ");
		// printToken(token, tokenString);
		// token = getToken();
		break;
	}
	return t;
}

TreeNode * arg_list() {
	if(token == RPAREN) {
		return NULL;
	}
	TreeNode * t = expression();
	TreeNode * p = t;
	while(token==COMMA) {
		TreeNode * q;
		match(COMMA);
		q = expression();
		if(q!=NULL) {
			if(t==NULL) t = p = q;
			else {
				p->sibling = q;
				p = q;
			}
		}
	}
	return t;
}
