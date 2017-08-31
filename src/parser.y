%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
  void variables_redeclaration();
  void variables_checking();
%}

%token declblock
%token codeblock

%token DIGIT
%token NUMBER
%token IDENTIFIER
%token ETOK
%token TYPE
%token TEXT

%token IF
%token ELSE
%token WHILE
%token FOR
%token GOTO

%token PRINT
%token PRINTLN
%token READ

%token LOGEQ
%token LOGOR
%token LEQ
%token NOTEQ
%token GEQ
%token LOGAND

%right '='

%left LOGOR
%left LOGAND
%left '|'
%left '^'
%left '&'
%left NOTEQ
%left LOGEQ
%left GEQ
%left '>'
%left LEQ
%left '<'
%left '-'
%left '+'
%left '%'
%left '/'
%left '*'
%left ')'
%left '('

%union {char *identifier;}

%%

program:	decl_block code_block

decl_block:  declblock '{' declaration_list '}'

code_block:  codeblock '{' statement_list '}' 


declaration_list : decl_stmt ';' declaration_list 
		 |
		 ;

decl_stmt : TYPE expr 
	  |
	  ;

expr : variables ',' expr 
     | variables
     ;

variables : IDENTIFIER{variables_redeclaration();} '[' VALUE ']' 
	  | IDENTIFIER{variables_redeclaration();}
	  ;

statement_list : forloop statement_list
	       | whileloop statement_list
	       | gotoloop ';' statement_list
	       | condition statement_list
	       | print ';' statement_list
	       | read ';' statement_list
	       | stmt ';' statement_list 
	       | 
	       ;

stmt : VARIABLE '=' stmt
     | expression
     ;

VARIABLE : IDENTIFIER{variables_checking();}
	 | IDENTIFIER{variables_checking();} '[' temp ']'
	 ;

temp : VALUE
     | IDENTIFIER{variables_checking();}
     ;

VALUE : DIGIT
      | NUMBER
      ;

condition : IF boolexpression '{' statement_list '}' ELSE '{' statement_list '}'
	  | IF boolexpression '{' statement_list '}'
	  ;

whileloop : WHILE boolexpression '{' statement_list '}'
	  ;

forloop : FOR VARIABLE '=' VALUE ',' VALUE ',' VALUE '{' statement_list '}'
	| FOR VARIABLE '=' VALUE ',' VALUE '{' statement_list '}'
	;

gotoloop : IDENTIFIER ':' statement_list GOTO IDENTIFIER 
	 | IDENTIFIER ':' statement_list GOTO IDENTIFIER IF boolexpression
	 ;

read : READ VARIABLE
     ;

print : PRINT printstmt
      | PRINTLN printstmt
      ;

printstmt : TEXT ',' printstmt
	  | VARIABLE ',' printstmt
	  | TEXT
	  | VARIABLE
	  ;

boolexpression : expression LOGOR expression
	       | expression LOGAND expression
	       | expression '|' expression
	       | expression '^' expression
	       | expression '&' expression
	       | expression LOGEQ expression
	       | expression NOTEQ expression
	       | expression GEQ expression
	       | expression '>' expression
	       | expression LEQ expression
	       | expression '<' expression
	       | expression ')' expression
	       | expression '(' expression
	       | VARIABLE
	       | VALUE
	       ;

expression : expression LOGOR expression
	   | expression LOGAND expression
	   | expression '|' expression
	   | expression '^' expression
	   | expression '&' expression
	   | expression LOGEQ expression
	   | expression NOTEQ expression
	   | expression GEQ expression
	   | expression '>' expression
	   | expression LEQ expression
	   | expression '<' expression
	   | expression '-' expression
	   | expression '+' expression
	   | expression '%' expression
	   | expression '/' expression
	   | expression '*' expression
	   | expression ')' expression
	   | expression '(' expression
	   | VARIABLE
	   | VALUE
	   ;


%%

#include "lex.yy.c"
typedef struct names{
	char identifier[100];
}Names;

Names varnames[1000];
int poi=0,i;

void variables_redeclaration()
{
	int flag=0;
	char *temp = yylval.identifier;
	for(i=0;i<poi;i++)
	{
		if(strcmp(temp,varnames[i].identifier)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		fprintf(stderr,"Redeclaration of %s as variable\n",temp);
		exit(0);

	}
	else
	{
		strcpy(varnames[poi].identifier,temp);
		poi++;
	}
}

void variables_checking()
{
	int flag=0;
	char *temp = yylval.identifier;
	for(i=0;i<poi;i++)
	{
		if(strcmp(temp,varnames[i].identifier)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		fprintf(stderr,"This variable is undeclared: %s\n",temp);
		exit(0);
	}
}

void yyerror (char const *s)
{
	fprintf(stderr,"Error before: %s\n",yytext);
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");

	yyparse();
}
