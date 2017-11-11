%{
  //#include <stdio.h>
  //#include <stdlib.h>
  #include "classes.h"
  #include <bits/stdc++.h>
  extern FILE *yyin;
  extern int line_num;
  int yylex (void);
  class Program* start = NULL;
  Visitor *Vis = new Interpreter();
  void yyerror (char const *s);
  void variables_redeclaration();
  void variables_checking();
  extern union Node yylval;
  extern int errors;

%}
%start program

%token<identifier> declblock
%token<identifier> codeblock

%token<value> DIGIT
%token<value> NUMBER
%token<identifier> IDENTIFIER
%token ETOK
%token<identifier> TYPE
%token<identifier> TEXT

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

%type<program> program;
%type<decl_block> decl_block;
%type<code_block> code_block;
%type<declaration_list> declaration_list;
%type<decl_stmt> decl_stmt;
%type<expr> expr;
%type<variables> variables;
%type<value> VALUE;
%type<statement_list> statement_list;
%type<expression> expression;
%type<boolexpression> boolexpression;
%type<stmt> stmt;
%type<variables2> VARIABLE;
%type<condition> condition;
%type<whileloop> whileloop;
%type<forloop> forloop;
%type<print> print;
%type<read> read;
%type<readvars> readvars;
%type<printstmt> printstmt;
%type<prt> prt;
%type<gotoloop> gotoloop;
%%

program:  decl_block code_block {$$ = new Program($1,$2);start = $$;errors =0;}

decl_block:  declblock '{' declaration_list '}' {$$ = new Decl_block($3);}

code_block:  codeblock '{' statement_list '}'  {$$ = new Code_block($3);}


declaration_list : decl_stmt ';' declaration_list  {$$ = new Declaration_list($3,$1);}
                 |  {$$ = new Declaration_list();}
		             ;



decl_stmt : TYPE expr {$$ = new Decl_stmt(string($1),$2);}
	  ;

expr : variables ',' expr {$$ = new Expr($1,$3);}
     | variables {$$ = new Expr($1);}
     ;

variables : IDENTIFIER '[' VALUE ']' {$$ = new Variables(string($1),$3,1);}
	  | IDENTIFIER { $$ = new Variables(string($1),1,0);}
	  ;


statement_list : forloop statement_list {$$ = new Statement_list($1,$2,string("NOT_GOTO"));}
	       | whileloop statement_list {$$ = new Statement_list($1,$2,string("NOT_GOTO"));}
	       | gotoloop ';' statement_list {$$ = new Statement_list($1,$3,string("GOTO"));}
	       | condition statement_list {$$ = new Statement_list($1,$2,string("NOT_GOTO"));}
         | IDENTIFIER ':' statement_list {$$ = new Statement_list(string($1),$3);}
	       | print ';' statement_list {$$ = new Statement_list($1,$3,string("NOT_GOTO"));}
	       | read ';' statement_list {$$ = new Statement_list($1,$3,string("NOT_GOTO"));}
	       | stmt ';' statement_list {$$ = new Statement_list($1,$3,string("NOT_GOTO"));}
	       | {$$ = new Statement_list();}
	       ;


stmt : VARIABLE '=' stmt {$$ = new Stmt($1,$3);}
     | expression {$$ = new Stmt($1);}
     ;

VARIABLE : IDENTIFIER {$$ = new Variables2(string($1));}
	 | IDENTIFIER '[' expression ']' {$$ = new Variables2(string($1),$3);}
	 ;


/*
temp : VALUE
     | IDENTIFIER
     | IDENTIFIER '[' temp ']'
     ;
*/

VALUE : DIGIT {$$=$1;}
      | NUMBER {$$=$1;}
      ;

condition : IF boolexpression '{' statement_list '}' ELSE '{' statement_list '}'  {$$ = new Condition($2,$4,$8);}
	  | IF boolexpression '{' statement_list '}'  {$$ = new Condition($2,$4);}
	  ;

whileloop : WHILE boolexpression '{' statement_list '}'  {$$ = new WhileLoop($2,$4);}
	  ;

forloop : FOR VARIABLE '=' expression ',' expression ',' expression '{' statement_list '}'  {$$ = new ForLoop($2,$4,$6,$8,$10);}
	| FOR VARIABLE '=' expression ',' expression '{' statement_list '}'  {$$ = new ForLoop($2,$4,$6,$8);}
	;

gotoloop :GOTO IDENTIFIER {$$ = new GoToLoop(string($2));}
	       |GOTO IDENTIFIER IF boolexpression  {$$ = new GoToLoop(string($2),$4);}
	       ;

read : READ readvars {$$ = new Read($2);}
     ;
readvars : VARIABLE ',' readvars {$$ = new ReadVars($1,$3);}
	 | VARIABLE  {$$ = new ReadVars($1);}

print : PRINT printstmt {$$ = new Print($2,0);}
      | PRINTLN printstmt  {$$ = new Print($2,1);}
      ;

printstmt : printstmt ',' prt {$$ = new PrintStmt($3,$1);}
	  | prt {$$ = new PrintStmt($1);}
	  ;

prt : TEXT {$$ = new Prt(string($1));}
    | VARIABLE {$$ = new Prt($1);}
    ;

boolexpression : expression LOGOR expression {$$ = new BoolExpression($1,string("||"),$3);}
	       | expression LOGAND expression {$$ = new BoolExpression($1,string("&&"),$3);}
	       | expression LOGEQ expression {$$ = new BoolExpression($1,string("=="),$3);}
	       | expression NOTEQ expression {$$ = new BoolExpression($1,string("!="),$3);}
	       | expression GEQ expression  {$$ = new BoolExpression($1,string(">="),$3);}
	       | expression '>' expression  {$$ = new BoolExpression($1,string(">"),$3);}
	       | expression LEQ expression  {$$ = new BoolExpression($1,string("<="),$3);}
	       | expression '<' expression  {$$ = new BoolExpression($1,string("<"),$3);}
	       | '(' boolexpression ')'  {$$ = $2;}
	       ;

expression : expression '|' expression  {$$ = new Expression($1,string("|"),$3);}
	   | expression '^' expression  {$$ = new Expression($1,string("^"),$3);}
	   | expression '&' expression  {$$ = new Expression($1,string("&"),$3);}
	   | expression '-' expression  {$$ = new Expression($1,string("-"),$3);}
	   | expression '+' expression  {$$ = new Expression($1,string("+"),$3);}
	   | expression '%' expression  {$$ = new Expression($1,string("%"),$3);}
	   | expression '/' expression  {$$ = new Expression($1,string("/"),$3);}
	   | expression '*' expression  {$$ = new Expression($1,string("*"),$3);}
	   | '(' expression ')'  {$$ = $2;}
	   | VARIABLE {$$ = new Expression($1);}
	   | VALUE  {$$ = new Expression($1);}
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
	fprintf(stderr,"Error:%s At: %s Line-No:%d\n",s,yylval.identifier,line_num);
       //fprintf (stderr, "%s\n", s);
  exit(-1);
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
  if(start)
  {
    start->accept(Vis);
  }
  if(errors==0)
  {
    start->codegen();
    start->generateCode();
  }
}
