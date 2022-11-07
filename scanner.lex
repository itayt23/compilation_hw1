%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
%option yyleng
%option yytext
digit   		  ([1-9])
letter  		  ([a-zA-Z])
whitespace	      ([\t\r\n ])

%x STRINGS


%%
/* Rules section */

void                                                                return VOID;
int                                                                 return INT;
byte                                                                return BYTE;
b                                                                   return B;
bool                                                                return BOOL;
and                                                                 return AND;
or                                                                  return OR;
not                                                                 return NOT;
true                                                                return TRUE;
false                                                               return FALSE;
return                                                              return RETURN;
if                                                                  return IF;
else                                                                return ELSE;
while                                                               return WHILE;
break                                                               return BREAK;
continue                                                            return CONTINUE;
(\;)                                                                return SC;
(\,)                                                                return COMMA;
(\()                                                                return LPAREN;
(\))                                                                return RPAREN;
(\{)                                                                return LBRACE;
(\})                                                                return RBRACE;
(=)                                                                 return ASSIGN;
(((\=|\<|\>|\!)\=)|\>|\<)                                           return RELOP;
(\+|\-|\*|\/)                                                       return BINOP;
\/\/([^\r\n])*                                                      return COMMENT;
{letter}({letter}|{digit}|0)*                                       return ID;
({digit}({digit}|0)*)|0                                             return NUM;
{whitespace}				                                                  ;
\"(\\{validEscapeSequence}|\\x{hex1}{hex2}|[^"\\\n\r])*\"           return STRING;
\"(\\{validEscapeSequence}|\\x{hex1}{hex2}|[^"\\])*                 return ERROR_UNCLOSED_STRING;
\"(\\.|[^"\\\n\r])*\"                                               return ERROR_UNDEFINED_ESCAPE_SEQ;
.		                                                            return ERROR_UNKNOWN;

%%
