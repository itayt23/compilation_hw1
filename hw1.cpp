#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "tokens.hpp"

#define INVALID_CHAR -1

using namespace std;

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

char get_escape_sequence(char c){
	switch (c)
	{
		case 'n':
			return '\n';
		case '0':
			return '\0';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case '\\': 
			return '\\';
		case '"':
			return '"';
		case 'x':
			return 'x';
		default:
			return INVALID_CHAR;
	}
}

char hex_to_ascii(char c1,char c2){ 
		std::string hex = std::string(1,c1)+c2; 
 		return (char) (int)strtol(hex.c_str(), nullptr, 16);
}

int main()
{
	int token;
	std::string final_string;
	while ((token = yylex())){
	  // Your code here
		if(token == ERROR_UNKNOWN){
			std::cout<<"Error "<<yytext<<std::endl; 
			exit(0);
		}
		if(token == ERROR_UNCLOSED_STRING){
			std::cout<<"Error unclosed string"<<std::endl; 
			exit(0);
		}
		if(token == ERROR_UNDEFINED_ESCAPE_SEQ){
			int string_len = strlen(yytext);
			std::string escape_seq;
			for (size_t i = 0; i < string_len; i++){
				if(yytext[i] == '\\'){
					if(yytext[i+1] == 'x'){
						i++;
						while(yytext[i] != ' ' && yytext[i] != '\"' && i<string_len){
							escape_seq.push_back(yytext[i]);
							i++;
						}
					}
					else{
						escape_seq.push_back(yytext[i+1]);
					}
				}
			}
			std::cout<<"Error undefined escape sequence "<<escape_seq<<std::endl; 
			exit(0);
		}
		if (token == COMMENT) {
			std::cout << yylineno << " " << token_to_string(token) << " "
				<< "//" << std::endl;
			continue;
		}
		else if(token == STRING){
			std::string final_string;
			int string_len = strlen(yytext);
			for(int i = 0; i <string_len; i++){
				if((i == 0 && yytext[i] == '\"') || (i==string_len-1 && yytext[i] == '\"')){
					continue;
				}
				else if(yytext[i] != '\\'){
					final_string.push_back(yytext[i]);
				}
				else{
					char escape_sequence = get_escape_sequence(yytext[i+1]);
					if(escape_sequence == INVALID_CHAR){
						std::cout << "Error undefined escape sequence "<< escape_sequence<<std::endl;
						exit(0);
					}
					if(escape_sequence == '\0')break;
					if(escape_sequence != 'x'){
						final_string.push_back(escape_sequence);
						i++;
					}
					else{
						if(yytext[i+2] == '0' && yytext[i+3] == '0') break; //TODO: NEED TO CHECK WHAT THEY WANT
						char ascii_char = hex_to_ascii(yytext[i+2],yytext[i+3]);
						final_string.push_back(ascii_char);
						i+=3;
					}
				}
			}
			std::cout << yylineno << " " << token_to_string(token) << " "
					<< final_string << std::endl;
		}
		else{
			std::cout << yylineno << " " << token_to_string(token) << " "
				<< yytext << std::endl;
		}
	}
	return 0;
}


