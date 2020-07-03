#include <bits/stdc++.h>
using namespace std;

int lineno = 0;

#include "parse.cpp"

int main() {
	// test parse
	freopen("compiler/in.txt", "r", stdin);
	freopen("compiler/out.txt", "w", stdout);

	int lineno = 0;
	TreeNode * tree = program();
	printTree(tree, 0);

	// test getToken
	// freopen("compiler/in_token.txt", "r", stdin);
	// freopen("compiler/out_token.txt", "w", stdout);
	// while(1) {
	// 	TokenType token = getToken();
	// 	if(token==ENDFILE) break;
	// 	if(token==ERROR) {
	// 		puts("输入出错了！");
	// 		break;
	// 	}
	// 	printToken(token, tokenString);
	// }

	return 0;
}