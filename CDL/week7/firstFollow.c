#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.c"

void Program();
void Declarations();
void Data_Type();
void Id_List();
void Assign_Stat();
void Id_List_Prime();
void Assign_Stat_Prime();

char* firstProgram = "main";
char* followProgram = "$";

char firstDeclaration[2][10] = {"int", "char"};
char* followDeclaration = "id";
int findfirstDeclaration(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstDeclaration[i], str)==0) return i;
	return -1;
}

char firstDataType[2][10] = {"int", "char"};
char* followDataType = "id";

char* firstIDList = "id";
char* followIDList = ";";

char* firstIDListPrime = ",";
char* followIDListPrime = ";";

char* firstAss = "id";
char* followAss = "}";

char firstAssPrime[2][10] = {"id", "NUM"};
char* followAssPrime = "}";
int findAssPrime(char *str) {
	for(int i=0; i<2; i++)
		if(strcmp(firstAssPrime[i], str)==0) return i;
	return -1;
}

void invalid() {
	printf("FALIED");
	exit(0);
}

void printToken() {
	printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
}

void Program(){
    t = getToken(fptr);
    printToken();
    if(!strcmp(t->tokenName, firstProgram)){
        t = getToken(fptr);
        printToken();
        if(!strcmp(t->tokenName, "(")){
            t = getToken(fptr);
            printToken();
            if(!strcmp(t->tokenName, ")")){
                t = getToken(fptr);
                printToken();
                if(!strcmp(t->tokenName, "{")){
                    t = getToken(fptr);
                    printToken();
                    if(findfirstDeclaration(t->tokenName)!= -1){
                        Declarations();
                        Assign_Stat();
                    }
                    else if(!strcmp(t->tokenName, followDeclaration)){
                        Assign_Stat();
                    }
                    // t = getToken(fptr);
                    // printToken();
                    if(!strcmp(t->tokenName, "}"))
                        return; 
                    else{
                        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "}");    
                        exit(0);
                    }      
                }
                else{
                    printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "{");
                    exit(0);
                }
            }
            else{
                printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ")");
                exit(0);
            }
        }
        else{
            printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "(");
            exit(0);
        }
    }
    else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, firstProgram);
		exit(0);
	}
}

void Declarations(){
    if(findfirstDeclaration(t->tokenName) != -1){
        Id_List();
        if(!strcmp(t->tokenName, ";"))
            Declarations();
        else {
			printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ";");
			exit(0);
		}
    }
	else if(strcmp(followDeclaration, t->tokenName)==0) return;
    else{
        printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\" or \"%s\".\n", t->row, t->col, "int", "char", "id");
		exit(0);
    }
}

void Id_List(){
    t = getToken(fptr);
    printToken();
    if(!strcmp(t->tokenName, firstIDList)){
        Id_List_Prime();
    }
    else{
        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "id");
		exit(0);
    }
}

void Id_List_Prime(){
    t = getToken(fptr);
    printToken();
    if(!strcmp(t->tokenName, ",")){
        Id_List();
    }
    else if(!strcmp(t->tokenName, followIDListPrime))
        return; 
    else{
        printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, ",", ";");
		exit(0);
    }
}

void Assign_Stat(){
    if(!strcmp(t->tokenName, firstAss)){
        t = getToken(fptr);
        printToken();
        if(!strcmp(t->tokenName, "=")){
            Assign_Stat_Prime();
        }
        else {
			printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "=");
			exit(0);
		}
    }
    else {
		printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, firstAss);
		exit(0);
	}
}

void Assign_Stat_Prime(){
    t = getToken(fptr);
    printToken();
    if(findAssPrime(t->tokenName) != -1){
        t = getToken(fptr);
        printToken();
        if(!strcmp(t->tokenName, ";"))
            return; 
        else {
			printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ";");
			exit(0);
		}
    }
    else {
		printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "NUM");
		exit(0);
	}
}

int main() {
	for(int i=0; i<MAX_HASH_SIZE; i++)
		hashSymbol[i] == NULL;
	// printf("Enter the first file to be opened: ");
	// scanf("%s", filename);
	fptr = fopen("ip.txt", "r");
	if(!fptr) {
		printf("The file does not exist.\n");
		exit(0);
	}
	Program();
	t = getToken(fptr);
	printToken();
	if(strcmp(t->tokenName, "$")==0) printf("SUCCESS");
	else invalid();
	displaySymbolTable();
	fclose(fptr);
	return 0;
}
