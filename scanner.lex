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

void                                  return VOID;
int                                   return INT;
byte                                  return BYTE;
b                                     return B;
bool                                  return BOOL;
and                                   return AND;
or                                    return OR;
not                                   return NOT;
true                                  return TRUE;
false                                 return FALSE;
return                                return RETURN;
if                                    return IF;
else                                  return ELSE;
while                                 return WHILE;
break                                 return BREAK;
continue                              return CONTINUE;
(\;)                                  return SC;
(\,)                                  return COMMA;
(\()                                  return LPAREN;
(\))                                  return RPAREN;
(\{)                                  return LBRACE;
(\})                                  return RBRACE;
(=)                                   return ASSIGN;
(((\=|\<|\>|\!)\=)|\>|\<)             return RELOP;
(\+|\-|\*|\/)                         return BINOP;
\/\/([^\r\n])*                        return COMMENT;
{letter}({letter}|{digit}|0)*         return ID;
({digit}({digit}|0)*)|0               return NUM;
{whitespace}				                    ;
(\")                                  BEGIN(STRINGS);
<STRINGS><<EOF>>                      return WRONGSTRING;
<STRINGS>([\x00-\x09\x0b-\x0c\x0e-\x21\x23-\x5b\x5d-\x7f]|((\\)(\\))|((\\)(\"))|((\\)(n))|((\\)(r))|((\\)(t))|((\\)(0))|((\\)x))*(\") {BEGIN(INITIAL);return STRING;}
<STRINGS>([^(\")])*((\")?)            return WRONGSTRING;
.		                                  return UNKNOWN;


%%
