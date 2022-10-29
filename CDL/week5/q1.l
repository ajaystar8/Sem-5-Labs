%{
    #include <stdio.h>
    int vowels = 0;
    int consonants = 0; 
%}
%%
[a,e,i,o,u,A,E,I,O,U] {vowels++;}
[a-zA-Z] {consonants++;}
%%
int yywrap(){
    return 1; 
}
int main(){
    yyin = fopen("ip.txt", "r");
    yylex();
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
}