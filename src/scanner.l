%{
#include<bits/stdc++.h>
#include "classes.h"
#include "parser.tab.h"
using namespace std;
int line_num;
extern union Node yylval;

%}

%%
"declblock"	{yylval.identifier = strdup(yytext);return declblock;}
"codeblock"	{yylval.identifier = strdup(yytext) ;return codeblock;}

"int"		{ yylval.identifier = strdup(yytext); return TYPE;}
","		  {yylval.identifier = strdup(yytext); return ',';}
";"		{yylval.identifier = strdup(yytext); return ';';}
":"	  {yylval.identifier = strdup(yytext);	return ':';}
\".*\"		{yylval.identifier = strdup(yytext);return TEXT;}

"if"		{yylval.identifier = strdup(yytext); return IF;}
"else"		{yylval.identifier = strdup(yytext);return ELSE;}

"while"		{yylval.identifier = strdup(yytext);return WHILE;}
"for"		{yylval.identifier = strdup(yytext);return FOR;}
"goto"		{yylval.identifier = strdup(yytext);return GOTO;}

"print"		{yylval.identifier = strdup(yytext);return PRINT;}
"println"	{yylval.identifier = strdup(yytext);return PRINTLN;}
"read"		{yylval.identifier = strdup(yytext);return READ;}

-?([0-9])		{yylval.value = atoi(yytext);return DIGIT;}
[1-9][0-9]*	{yylval.value = atoi(yytext);return NUMBER;}
[a-zA-Z][a-zA-Z0-9]* {yylval.identifier = strdup(yytext);return IDENTIFIER;}
"+"	{yylval.identifier = strdup(yytext);	return '+';}
"-"	{yylval.identifier = strdup(yytext);	return '-';}
"*"	{yylval.identifier = strdup(yytext);	return '*';}
"/"	{yylval.identifier = strdup(yytext);	return '/';}

"("	{yylval.identifier = strdup(yytext);	return '(';}
")"	{yylval.identifier = strdup(yytext);	return ')';}
"{"	{yylval.identifier = strdup(yytext);	return '{';}
"}"	{yylval.identifier = strdup(yytext);	return '}';}
"["	{yylval.identifier = strdup(yytext);	return '[';}
"]"	{yylval.identifier = strdup(yytext);	return ']';}

"=="	{yylval.identifier = strdup(yytext);	return LOGEQ;}
"||"	{yylval.identifier = strdup(yytext);	return LOGOR;}
"<="	{yylval.identifier = strdup(yytext);	return LEQ;}
"!="	{yylval.identifier = strdup(yytext);	return NOTEQ;}
">="	{yylval.identifier = strdup(yytext);	return GEQ;}
"&&"	{yylval.identifier = strdup(yytext);	return LOGAND;}

">"		{yylval.identifier = strdup(yytext);	return '>';}
"<"		{yylval.identifier = strdup(yytext);	return '<';}
"="		{yylval.identifier = strdup(yytext);	return '=';}
"&"		{yylval.identifier = strdup(yytext);	return '&';}
"|"		{yylval.identifier = strdup(yytext);	return '|';}
"^"		{yylval.identifier = strdup(yytext);	return '^';}
"!"		{yylval.identifier = strdup(yytext);	return '!';}
"%"		{yylval.identifier = strdup(yytext);	return '%';}
[ \t]		{ /* Do nothing */ }
"\n"		{line_num++;}
.		{
		  printf("Unexpected token encountered: %s\n", yytext);
		  return ETOK;
		}
