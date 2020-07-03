This is a C- Lexical and Syntax Analyzer which is the curriculum project of Projects in Principles of Complier.

Implemented C- Syntax Analyzer by using C++. Removed the left recursion of grammar first, made analysis through top-down and built an Abstract Syntax Tree coded from C-.

For lexical analyzer, here is the DFA.
![relation](https://github.com/NonesZzft/Principles-of-Compiler/blob/master/DFA.png)

For syntax analyzer, here is the BCNF grammar, 29 productions.

1. program → declaration-list  
2. declaration-list → declaration-list declaration | declaration  
3. declaration → var-declaration | fun-declaration  
4. var-declaration → type-specifierID ; | type-specifierID [NUM];  
5. type-specifier→ int | void  
6. fun-declaration → type-specifierID (params)compound-stmt  
7. params→ param-list | void  
8. param-list→ param-list , param| param  
9. param→ type-specifierID | type-specifierID [ ]  
10. compound-stmt → { local-declarations statement-list }  
11. local-declarations → local-declarations var-declaration | empty  
12. statement-list → statement-list statement | empty  
13. statement → expression-stmt | compound-stmt| selection-stmt | iteration-stmt | return-stmt  
14. expression-stmt → expression ;| ;  
15. selection-stmt → if( expression ) statement | if ( expression ) statement else statement  
16. iteration-stmt → while( expression ) statement  
17. return-stmt → return ; | return expression ;  
18. expression → var = expression | simple-expression  
19. var → ID| ID[ expression ]  
20. simple-expression → additive-expression relop additive- expression | additive-expression  
21. relop → <= | < | > | >= | == | !=  
22. additive-expression → additive-expression addop term | term  
23. addop → + | -  
24. term → term mulop factor | factor 25. mulop → * | /  
26. factor → ( expression ) | var | call | NUM  
27. call → ID( args )  
28. args → arg-list | empty  
29. arg-list → arg-list , expression | expression  
