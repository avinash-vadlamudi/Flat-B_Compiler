#include<bits/stdc++.h>
using namespace std;
#include "classes.h"

Program::Program(class Decl_block* b1,class Code_block* b2)
{
    fields = b1;
    methods = b2;
}
Decl_block::Decl_block(class Declaration_list* b1)
{
    decl_list = b1;
}
Code_block::Code_block(class Statement_list* b1)
{
    stmt_list = b1;
}
Declaration_list::Declaration_list(class Declaration_list* b2,class Decl_stmt* b1)
{
    decl_stmts = b2->getlist();
    decl_stmts.push_back(b1);
    delete(b2);
}

Declaration_list::Declaration_list(class Decl_stmt* b1)
{
    decl_stmts.push_back(b1);
}

vector<class Decl_stmt*> Declaration_list::getlist()
{
  vector<class Decl_stmt*> list2;
  list2 = decl_stmts;
  return list2;
}

Decl_stmt::Decl_stmt(string type,class Expr *b1)
{
    this->type = type;
    list = b1->getlist();

}

Expr::Expr(class Variables *b1)
{
    list.push_back(b1);
}
Expr::Expr(class Variables *b1,class Expr *b2)
{
    list = b2->getlist();
    list.push_back(b1);
    delete(b2);
}
vector<class Variables*> Expr::getlist()
{
  vector<class Variables*> list2;
  list2 = list;
  return list2;
}
Variables::Variables(string str,int ind,int type)
{
    name = str;
    node_type = type;
    index = ind;
    value = 0;
}

Expression::Expression(class Expr2* var1,string op,class Expr2* var2)
{
  e1 = var1;
  e2 = var2;
  oper = op;
  variable = NULL;
}
Expression::Expression(class Variables2* var)
{
  e1 = NULL;
  e2 = NULL;
  variable = var;
}
Expression::Expression(int val)
{
  value = val;
}

BoolExpression::BoolExpression(class Expr2* var1,string op, class Expr2* var2)
{
  e1 = var1;
  e2 = var2;
  oper = op;
  variable = NULL;
}

Stmt::Stmt(class Variables2 *var1,class Stmt *var2)
{
  list = var2->getlist();
  list.push_back(var1);
  reqd_expr = var2->getexpr();
  delete(var2);
}
Stmt::Stmt(class Expression* var1)
{
  reqd_expr = var1;
}
vector<class Variables2*> Stmt::getlist()
{
  vector<class Variables2*> list2;
  list2 = list;
  return list2;
}
Expression * Stmt::getexpr()
{
  class Expression* expr_temp;
  expr_temp = reqd_expr;
  return expr_temp;
}

Statement_list::Statement_list(class Statements* var1,class Statement_list *var2)
{
  name = "";
  list1 = var1;
  list2 = var2;
}
Statement_list::Statement_list(string str,class Statement_list *var2)
{
  name = str;
  list2 = var2;
  list1 = NULL;
}
Statement_list::Statement_list()
{
  name = "";
  list1 = NULL;
  list2 = NULL;
}

Variables2::Variables2(string str)
{
  name = str;
  reqd_expr = NULL;
  ind = 0;
  type = 0;
}
Variables2::Variables2(string str,class Expression* expr)
{
  reqd_expr = expr;
  name = str;
  type = 1;
}

Condition::Condition(class BoolExpression* var1,class Statement_list* var2,class Statement_list* var3)
{
  reqd_expr = var1;
  list1 = var2;
  list2 = var3;
}
Condition::Condition(class BoolExpression* var1,class Statement_list* var2)
{
  reqd_expr = var1;
  list1 = var2;
  list2 = NULL;
}

WhileLoop::WhileLoop(class BoolExpression *var1,class Statement_list *var2)
{
  reqd_expr = var1;
  list1 = var2;
}

ForLoop::ForLoop(class Variables2* var1,int var2,int var3,int var4,class Statement_list* var5)
{
  var = var1;
  val1 = var2;
  val2 = var3;
  val3 = var4;
  list1 = var5;
}
ForLoop::ForLoop(class Variables2* var1,int var2,int var3,class Statement_list *var4)
{
  var = var1;
  val1 = var2;
  val2 = 1;
  val3 = var3;
  list1 = var4;
}

Read::Read(class ReadVars* var)
{
  list = var->getlist();
  delete(var);
}
ReadVars::ReadVars(class Variables2* var1,class ReadVars* var2)
{
  list = var2->getlist();
  list.push_back(var1);
  delete(var2);
}
ReadVars::ReadVars(class Variables2* var1)
{
  list.push_back(var1);
}
vector<class Variables2*> ReadVars::getlist()
{
  vector<class Variables2*> list2;
  list2 = list;
  return list2;
}

Print::Print(class PrintStmt *var)
{
  reqd = var;
}
PrintStmt::PrintStmt(class Prt* var1,class PrintStmt *var2)
{
  list = var2->getlist();
  list.push_back(var1);
  delete(var2);
}
PrintStmt::PrintStmt(class Prt* var1)
{
  list.push_back(var1);
}
vector<class Prt*> PrintStmt::getlist()
{
  vector<class Prt*> list2;
  list2 = list;
  return list2;
}
Prt::Prt(string var1)
{
  text = var1;
  var = NULL;
}
Prt::Prt(class Variables2* var1)
{
  text = "";
  var = var1;
}

GoToLoop::GoToLoop(string str)
{
  name = str;
  val = 1;
  reqd_expr = NULL;
}
GoToLoop::GoToLoop(string str,class BoolExpression *var1)
{
  name = str;
  reqd_expr = var1;
}


void Variables::traverse()
{
  cout<<name<<" "<<index<<" "<<node_type<<"\n";
}
void Expr::traverse()
{
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
}
void Decl_stmt::traverse()
{
  cout<<type<<"\n";
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
}
void Declaration_list::traverse()
{
  for(int i=0;i<decl_stmts.size();i++)
  {
    decl_stmts[i]->traverse();
  }
}
void Decl_block::traverse()
{
  cout<<"Decl_block\n";
  decl_list->traverse();
}

void Variables2::traverse()
{
  cout<<name<<" "<<type<<"\n";
  if(reqd_expr != NULL)
  {
    reqd_expr->traverse();
  }
  cout<<"\n\n";

}
void Expression::traverse()
{
  if(e1!=NULL)
  {
    e1->traverse();
    cout<<"\n";
  }
  if(e2!=NULL)
  {
    e2->traverse();
    cout<<"\n";
  }
  if(oper!="")
  {
    cout<<oper<<"\n";
  }
  if(variable !=NULL)
  {
    variable->traverse();
  }
  cout<<value<<"\n";

  cout<<"\n\n";
}
void BoolExpression::traverse()
{
  if(e1!=NULL)
  {
    e1->traverse();
    cout<<"\n";
  }
  if(e2!=NULL)
  {
    e2->traverse();
    cout<<"\n";
  }
  if(oper!="")
  {
    cout<<oper<<"\n";
  }
  if(variable !=NULL)
  {
    variable->traverse();
  }
  cout<<value<<"\n";

  cout<<"\n\n";
}
void Stmt::traverse()
{
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
  reqd_expr->traverse();
  cout<<"\n\n";
}
void Statement_list::traverse()
{
  if(name!="")
  {
    cout<<name<<"\n";
  }
  if(list1!=NULL)
  {
    list1->traverse();
  }
  if(list2!=NULL)
  {
    list2->traverse();
  }
}
void Condition::traverse()
{
  cout<<"IFELSE\n";
  reqd_expr->traverse();
  if(list1!=NULL)
  {
    list1->traverse();
  }
  if(list2!=NULL)
  {
    list2->traverse();
  }
  cout<<"\n";
}
void WhileLoop::traverse()
{
  cout<<"WHILE\n";
  reqd_expr->traverse();
  if(list1!=NULL)
  {
    list1->traverse();
  }
  cout<<"\n";
}
void ForLoop::traverse()
{
  cout<<"FOR\n";
  var->traverse();
  cout<<val1<<" "<<val2<<" "<<val3<<"\n";
  if(list1!=NULL)
  {
    list1->traverse();
  }
  cout<<"\n";
}
void Prt::traverse()
{
  cout<<text<<"\n";
  if(var!=NULL)
    var->traverse();
  cout<<"\n";
}
void PrintStmt::traverse()
{
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
  cout<<"\n";
}
void Print::traverse()
{
  reqd->traverse();
}
void ReadVars::traverse()
{
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
  cout<<"\n";
}
void Read::traverse()
{
  cout<<"Read\n";
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
  cout<<"\n";
}
void GoToLoop::traverse()
{
  cout<<"GOTO\n";
  cout<<name<<"\n";
  if(reqd_expr!=NULL)
  {
    reqd_expr->traverse();
  }
  cout<<"\n";
}
void Code_block::traverse()
{
  stmt_list->traverse();
}
void Program::traverse()
{
  fields->traverse();
  methods->traverse();
}
