%{
    #include <stdio.h>
%}
%%
[a-zA-Z][a-zA-Z0-9_]* printf("Identifier");
%%
int yywrap(){
    return 1; 
}
int main(){
    yyin = fopen("ip.txt", "r");
    yylex();
}