%{
    #include <stdio.h>
    #include <string.h>
    int words = 0;
    int chars = 0;
    int blanks = 0; 
    int lines = 0;  
%}
%%
" " {blanks++;}
[a-zA-Z][a-zA-Z]* {words++; chars += strlen(yytext);}
\n {chars++; lines++;};
. {chars++;}
%%
int yywrap(){
    return 1; 
}
int main(){
    yyin = fopen("ip.txt", "r");
    yylex();
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    printf("Blanks: %d\n", blanks);
    printf("Lines: %d\n", lines);
}