#include <iostream>
#include <stdio.h>
#include <string>
#include "tokens.hpp"



std::string token_to_string(int token){
    switch(token) {
        case VOID : return "VOID";
        case INT : return "INT";
        case BYTE : return "BYTE";
        case B : return "B";
        case BOOL : return "BOOL";
        case AND : return "AND";
        case OR : return "OR";
        case NOT : return "NOT";
        case TRUE : return "TRUE";
        case FALSE : return "FALSE";
        case RETURN : return "RETURN";
        case IF : return "IF";
        case ELSE : return "ELSE";
        case WHILE : return "WHILE";
        case BREAK : return "BREAK";
        case CONTINUE : return "CONTINUE";
        case SC : return "SC";
        case COMMA : return "COMMA";
        case LPAREN : return "LPAREN";
        case RPAREN : return "RPAREN";
        case LBRACE : return "LBRACE";
        case RBRACE : return "RBRACE";
        case ASSIGN : return "ASSIGN";
        case RELOP : return "RELOP";
        case BINOP : return "BINOP";
        case COMMENT : return "COMMENT";
        case ID : return "ID";
        case NUM : return "NUM";
        case STRING : return "STRING";
    }
	return "NULL";
}
int main()
{
	int token;
	while ((token = yylex())) {
	  // Your code here
		if(token == ERROR_UNKNOWN){
			std::cout<<"Error "<<token<<std::endl; //TODO: chnge tokeen to char 
			exit(0);
		}
		if(token == ERROR_UNCLOSED_STRING){
			std::cout<<"Error unclosed string"<<std::endl; 
			exit(0);
		}
		if(token == ERROR_UNDEFINED_ESCAPE_SEQ){

		}
		if (token == COMMENT) {
			printf("%d %s %s\n", yylineno, yytext, "//");
		}
		else if(token == STRING){
			printf("%d %s %s\n", yylineno, token_to_string(token),yytext);
		}
	return 0;
}


