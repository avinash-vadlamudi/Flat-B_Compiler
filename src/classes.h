#include<bits/stdc++.h>
#ifndef __HEADER__
#define __HEADER__
using namespace std;

struct Var_node{
  int type;
  string var_type;
  string name;
  vector<int> list;
  int max_index;
};


union Node{
  int value;
  char *identifier;
  class Program* program;
  class Declaration_list *declaration_list;
  class Decl_block *decl_block;
  class Code_block *code_block;
  class Decl_stmt *decl_stmt;
  class Expr *expr;
  class Variables *variables;
  class Statement_list* statement_list;
  class Stmt *stmt;
  class Expression *expression;
  class BoolExpression *boolexpression;
  class Variables2 *variables2;
  class Condition *condition;
  class ForLoop *forloop;
  class WhileLoop *whileloop;
  class Print *print;
  class PrintStmt *printstmt;
  class Prt *prt;
  class Read *read;
  class ReadVars *readvars;
  class GoToLoop *gotoloop;

  Node(){
    value=0;
    identifier=NULL;
    program=NULL;
    declaration_list=NULL;
    decl_block=NULL;
    code_block=NULL;
    decl_stmt=NULL;
    expr=NULL;
    variables=NULL;
    statement_list=NULL;
    stmt = NULL;
    expression = NULL;
    boolexpression = NULL;
    variables2 = NULL;
    condition = NULL;
    forloop = NULL;
    whileloop = NULL;
    print = NULL;
    printstmt = NULL;
    prt = NULL;
    read = NULL;
    readvars = NULL;
    gotoloop = NULL;
  }
  ~Node(){};


};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1


class Astnode;
class Variables;
class Expr;
class Decl_stmt;
class Declaration_list;
class Decl_block;
class Expr2;
class Variables2;
class Expression;
class BoolExpression;
class Statements;
class Stmt;
class Statement_list;
class Condition;
class WhileLoop;
class ForLoop;
class Prt;
class PrintStmt;
class Print;
class ReadVars;
class Read;
class GoToLoop;
class Code_block;
class Program;

struct Ref_node{
  string name;
  class Statement_list* list_ptr;
};


class Visitor
{
public:
  //virtual void visit(class Astnode*)=0;
  virtual void visit(class Variables*,class Decl_stmt*)=0;
  virtual void visit(class Expr*)=0;
  virtual void visit(class Decl_stmt*)=0;
  virtual void visit(class Declaration_list*)=0;
  virtual void visit(class Decl_block*)=0;
  //virtual int visit(class Expr2*)=0;
  virtual int visit(class Variables2* )=0;
  virtual int visit(class Expression*)=0;
  virtual int visit(class BoolExpression*)=0;
  //void visit(class Statements*);
  virtual int visit(class Stmt*)=0;
  virtual int visit(class Statement_list*)=0;
  virtual int visit(class Condition*)=0;
  virtual int visit(class WhileLoop*)=0;
  virtual int visit(class ForLoop*)=0;
  virtual int visit(class Prt*)=0;
  virtual int visit(class PrintStmt*)=0;
  virtual int visit(class Print*)=0;
  virtual int visit(class ReadVars*)=0;
  virtual int visit(class Read*)=0;
  virtual int visit(class GoToLoop*)=0;
  virtual void visit(class Code_block*)=0;
  virtual void visit(class Program*)=0;
};

class Interpreter:public Visitor
{
public:
  Interpreter()
  {

  }
  //void visit(class Astnode*);
  void visit(class Variables*,class Decl_stmt*);
  void visit(class Expr*);
  void visit(class Decl_stmt*);
  void visit(class Declaration_list*);
  void visit(class Decl_block*);
  //virtual int visit(class Expr2*){};
  int visit(class Variables2* );
  int visit(class Expression*);
  int visit(class BoolExpression*);
  //void visit(class Statements*);
  int visit(class Stmt*);
  int visit(class Statement_list*);
  int visit(class Condition*);
  int visit(class WhileLoop*);
  int visit(class ForLoop*);
  int visit(class Prt*);
  int visit(class PrintStmt*);
  int visit(class Print*);
  int visit(class ReadVars*);
  int visit(class Read*);
  int visit(class GoToLoop*);
  void visit(class Code_block*);
  void visit(class Program*);

};

class Astnode
{
    //virtual void accept(class Visitor *V) = 0;
};

class Variables:public Astnode
{
public:
  string num_type;
  int node_type;
  int value;
  string name;
  int index;
public:
  Variables(string,int,int);
  void accept(Visitor *V,class Decl_stmt* var)
  {
    V->visit(this,var);
  }

};

class Expr:public Astnode
{
public:
  vector<class Variables*> list;
public:
  Expr(class Variables*,class Expr*);
  Expr(class Variables*);
  vector<class Variables*> getlist();
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};

class Decl_stmt:public Astnode
{
public:
  string type;
  vector<class Variables*> list;
public:
  Decl_stmt(string,class Expr*);
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};

class Declaration_list:public Astnode
{
public:
  vector<class Decl_stmt*> decl_stmts;
public:
  Declaration_list(class Declaration_list*,class Decl_stmt*);
  Declaration_list();
  vector<class Decl_stmt*> getlist();
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};

class Decl_block:public Astnode
{
public:
  class Declaration_list* decl_list;

public:
  Decl_block(class Declaration_list*);
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};




class SymbolTable
{
public:
  map<string,Var_node> variables_list;
public:
  SymbolTable();
  void addnode(string,int ,int,string);
  int getvalue(string,int);
  void update(string,int,int);
  int check(string);
};

class SymbolTable2
{
public:
  map<string,Ref_node> references_list;
public:
  SymbolTable2();
  void addnode(string,class Statement_list*);
  class Statement_list* getptr(string);
};






class Expr2
{
public:
    virtual int accept(class Visitor *V) = 0;
};


class Variables2:public Astnode
{
public:
  string name;
  int val;
  int type;
  int ind;
  class Expression *reqd_expr;
public:
  Variables2(string);
  Variables2(string,class Expression*);
  int accept(Visitor *V)
  {
    V->visit(this);
    return 0;
  }
};

class Expression:public Expr2
{
public:
  class Expr2* e1;
  class Expr2* e2;
  string oper;
  class Variables2* variable;
  int value;
public:
  Expression(class Expr2*,string ,class Expr2*);
  Expression(class Variables2* var);
  Expression(int);
  int perform_op(int,int,string);
  int accept(Visitor *V)
  {
    int temp = V->visit(this);
    return temp;
  }
};

class BoolExpression:public Expr2
{
public:
  class Expr2* e1;
  class Expr2* e2;
  string oper;
  class Variables2* variable;
  int value;
public:
  BoolExpression(class Expr2*,string,class Expr2*);
  int perform_op(int,int,string);
  int accept(Visitor *V)
  {
    int temp = V->visit(this);
    return temp;
  }
};


class Statements:public Astnode
{
public:
    virtual int accept(class Visitor *V) = 0;
    virtual class Statement_list* getptr()
    {
      
    }

};

class Stmt:public Statements
{
public:
  vector<class Variables2*> list;
  class Expression *reqd_expr;
public:
  Stmt(class Variables2* , class Stmt* );
  Stmt(class Expression*);
  vector<class Variables2*> getlist();
  class Expression * getexpr();
  int accept(Visitor *V)
  {
    V->visit(this);
    return 0;
  }
};

class Statement_list:public Astnode
{
public:
  class Statements* list1;
  string name;
  int count;
  string type;
  class Statement_list* list2;
  class Statement_list* list3;
public:
  Statement_list(class Statements*,class Statement_list*,string);
  Statement_list(string,class Statement_list*);
  Statement_list();
  int accept(Visitor *V)
  {
    int temp = V->visit(this);
    return temp;
  }
};

class Condition:public Statements
{
public:
  int val;
  class Statement_list *list1;
  class Statement_list *list2;
  class BoolExpression* reqd_expr;
public:
  Condition(class BoolExpression*,class Statement_list*,class Statement_list*);
  Condition(class BoolExpression*,class Statement_list*);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class WhileLoop:public Statements
{
public:
  int val;
  class Statement_list *list1;
  class BoolExpression *reqd_expr;
public:
  WhileLoop(class BoolExpression*,class Statement_list*);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class ForLoop:public Statements
{
public:
  int val1;
  int val2;
  int val3;
  class Variables2 *var;
  class Statement_list *list1;
public:
  ForLoop(class Variables2*,int,int,int,class Statement_list*);
  ForLoop(class Variables2*, int ,int ,class Statement_list*);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class Prt:public Astnode
{
public:
  string text;
  class Variables2* var;
public:
  Prt(string);
  Prt(class Variables2*);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class PrintStmt:public Astnode
{
public:
  vector<class Prt*> list;
public:
  PrintStmt(class Prt*,class PrintStmt*);
  PrintStmt(class Prt*);
  vector<class Prt*> getlist();
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class Print:public Statements
{
public:
  int type;
  class PrintStmt *reqd;
public:
  Print(class PrintStmt *,int);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class ReadVars:public Astnode
{
public:
  vector<class Variables2*> list;
public:
  ReadVars(class Variables2*,class ReadVars*);
  ReadVars(class Variables2*);
  vector<class Variables2*> getlist();
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class Read:public Statements
{
public:
  vector<class Variables2 *> list;
public:
  Read(class ReadVars*);
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};

class GoToLoop:public Statements
{
public:
  string name;
  class BoolExpression *reqd_expr;
  class Statement_list* list1;
  int val;
public:
  GoToLoop(string);
  GoToLoop(string,class BoolExpression*);
  class Statement_list* getptr()
  {
    class Statement_list* list_temp;
    list_temp = list1;
    return list1;
  }
  int accept(Visitor *V)
  {
    return V->visit(this);
  }
};



class Code_block:public Astnode
{
public:
  class Statement_list* stmt_list;
public:
  Code_block(class Statement_list*);
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};

class Program:public Astnode
{
public:
  class Decl_block* fields;
  class Code_block* methods;

public:
  Program(class Decl_block*,class Code_block*);
  void accept(Visitor *V)
  {
    V->visit(this);
  }
};

#endif
