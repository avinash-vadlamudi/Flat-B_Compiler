%{
#include "parser.tab.h"
%}

%%
"declblock"	{printf("Token: %s\n",yytext) ;return declblock;}
"codeblock"	{printf("Token: %s\n",yytext) ;return codeblock;}

"int"		{printf("Token: %s\n",yytext) ;return TYPE;}
","		return ',';
";"		return ';';
":"		return ':';
\".*\"		{printf("Token: %s\n",yytext) ;return TEXT;}

"if"		{printf("Token: %s\n",yytext) ;return IF;}
"else"		{printf("Token: %s\n",yytext) ;return ELSE;}

"while"		{printf("Token: %s\n",yytext) ;return WHILE;}
"for"		{printf("Token: %s\n",yytext) ;return FOR;}
"goto"		{printf("Token: %s\n",yytext) ;return GOTO;}

"print"		{printf("Token: %s\n",yytext) ;return PRINT;}
"println"	{printf("Token: %s\n",yytext) ;return PRINTLN;}
"read"		{printf("Token: %s\n",yytext) ;return READ;}

[0-9]		{printf("Token type: Number, Lexeme/Token Value: %s\n",yytext) ;return DIGIT;}
[1-9][0-9]*	{  
			printf("Token type: Number, Lexeme/Token Value: %s\n", yytext);  
			return NUMBER; 
                }
[a-zA-Z][a-zA-Z0-9]* {  
			printf("Token type: Identifier, Lexeme/Token Value: %s\n", yytext);  
			yylval.identifier = strdup(yytext);
			return IDENTIFIER; 
		     } 
"+"		return '+';
"-"		return '-';
"*"		return '*';
"/"		return '/';

"("		return '(';
")"		return ')';
"{"		return '{';
"}"		return '}';
"["		return '[';
"]"		return ']';

"=="		return LOGEQ;
"||"		return LOGOR;
"<="		return LEQ;
"!="		return NOTEQ;
">="		return GEQ;
"&&"		return LOGAND;

">"		return '>';
"<"		return '<';
"="		return '=';
"&"		return '&';
"|"		return '|';
"^"		return '^';
"!"		return '!';
"%"		return '%';
[ \t]		{ /* Do nothing */ }
.		{ 
		  printf("Unexpected token encountered: %s\n", yytext); 
		  return ETOK;
		}
