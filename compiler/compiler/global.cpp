#include <bits/stdc++.h>
using namespace std;

#include "token.cpp"

typedef enum {
	SelectionK, ExpressionK, CompoundK, IterationK, ForK, ReturnK,
	ExpK, DeclK, ConstK, IdK, OpK, FunK,
	IntK, VoidK, ArrayK, DoubleK,
	ParamK, EmptyK
} NodeKind;

class TreeNode {
public:
	TreeNode() {}
	vector<TreeNode*> child;
	TreeNode * sibling;
	NodeKind nodekind;
	TokenType op;
	double val;
	string name;
};

TreeNode * newNode(NodeKind kind) {
	TreeNode *t = new TreeNode();
	if(t == NULL) {
		printf("Out of memory error\n");
	}
	else {
		t->sibling = NULL;
		t->nodekind = kind;
	}
	return t;
}

void printToken(TokenType token, string tokenString) {
	switch (token) {
	case IF:
	case ELSE:
	case RETURN:
	case VOID:
	case INT:
	case DOUBLE:
	case WHILE:
	case FOR:
		printf("reserved word: ");
		cout << tokenString << endl;
		break;
	case ASSIGN:
		printf("=\n");
		break;
	case LT:
		printf("<\n");
		break;
	case EQ:
		printf("==\n");
		break;
	case GT:
		printf(">\n");
		break;
	case LTEQ:
		printf("<=\n");
		break;
	case GTEQ:
		printf(">=\n");
		break;
	case NEQ:
		printf("!=\n");
		break;
	case LPAREN:
		printf("(\n");
		break;
	case RPAREN:
		printf(")\n");
		break;
	case LBRACKET:
		printf("[\n");
		break;
	case RBRACKET:
		printf("]\n");
		break;
	case LBRACE:
		printf("{\n");
		break;
	case RBRACE:
		printf("}\n");
		break;
	case COMMA:
		printf(",\n");
		break;
	case COLON:
		printf(":\n");
		break;
	case SEMI:
		printf(";\n");
		break;
	case PLUS:
		printf("+\n");
		break;
	case MINUS:
		printf("-\n");
		break;
	case TIMES:
		printf("*\n");
		break;
	case OVER:
		printf("/\n");
		break;
	case ENDFILE:
		printf("EOF\n");
		break;
	case NUM:
		// printf("NUM, val= %s\n", tokenString);
		cout << "NUM, val = " << tokenString << endl;
		break;
	case ID:
		printf("ID, name = ");
		cout << tokenString << endl;
		break;
	case ERROR:
		printf("ERROR: ");
		cout << tokenString << endl;
		break;
	default: /* should never happen */
		printf("Unknown token: %d\n", token);
	}
}

void printTree(TreeNode * tree, int generation) {
	while(tree != NULL) {
		for(int i = 1; i <= generation; i++) {
			printf("\t");
		}
		switch(tree->nodekind) {
		case OpK:
			printf("Op: ");
			// cout << tree->op << endl;
			printToken(tree->op, "\0");
			break;
		case ConstK:
			printf("Const: ");
			cout << tree->val << endl;
			break;
		case IdK:
			printf("Id: ");
			cout << tree->name << endl;
			break;
		case FunK:
			printf("Fun: ");
			cout << tree->name << endl;
			break;
		case ArrayK:
			printf("Array:\n");
			break;
		case DeclK:
			printf("Declaration:\n");
			break;
		case IntK:
			printf("Type: int\n");
			break;
		case VoidK:
			printf("Type: void\n");
			break;
		case DoubleK:
			printf("Type: double\n");
			break;
		case ParamK:
			printf("Param:\n");
			break;
		case SelectionK:
			printf("Selection: if\n");
			break;
		case ExpressionK:
			printf("Expression:\n");
			break;
		case CompoundK:
			printf("Compound: {\n");
			break;
		case IterationK:
			printf("Iteration: while\n");
			break;
		case ForK:
			printf("For: for\n");
			break;
		case ReturnK:
			printf("Return:\n");
			break;
		case EmptyK:
			printf("Empty:\n");
			break;
		default:
			printf("Unknown node kind\n");
			break;
		}
		for(int i = 0; i < tree->child.size(); i++) {
			if(tree->child[i] != NULL) {
				if(tree->nodekind==SelectionK && i==2) {
					for(int j = 1; j <= generation; j++) {
						printf("\t");
					}
					printf("else:\n");
				}
				printTree(tree->child[i], generation+1);
			}
		}
		if(tree->nodekind==CompoundK) {
			for(int i = 1; i <= generation; i++) {
				printf("\t");
			}
			printf("}\n");
		}
		tree = tree->sibling;
	}
}

void syntaxError(string message) {
	cout << ">>> ";
	cout << "Syntax error at line " << lineno << ": ";
	cout << message;
	// Error = true;
}