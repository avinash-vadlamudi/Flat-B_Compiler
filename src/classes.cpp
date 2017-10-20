#include<bits/stdc++.h>
using namespace std;
#include "classes.h"
extern int line_num;
//Interpreter *Vis = new Interpreter();
extern Visitor *Vis;
int errors;

SymbolTable2::SymbolTable2()
{

}

void SymbolTable2::addnode(string str,class Statement_list* var)
{
  Ref_node temp;
  if(references_list.find(str)==references_list.end())
  {
    temp.name = str;
    temp.list_ptr = var;
    references_list[str] = (temp);
  }
  else
  {
    errors++;
    cout<<"Reference already used Ref is: "<<str<<endl;
  }
}

class Statement_list * SymbolTable2::getptr(string str)
{
  class Statement_list* temp_ptr=NULL;
  if(references_list.find(str)==references_list.end())
  {
    errors++;
    cout<<"Reference Not declared Ref is: "<<str<<endl;
    return temp_ptr;
  }
  else
  {
    temp_ptr = references_list[str].list_ptr;
    return temp_ptr;
  }

}

SymbolTable2 *symtable2 = new SymbolTable2();



SymbolTable::SymbolTable()
{

}
void SymbolTable::addnode(string str,int ind,int type,string vartype)
{
  Var_node temp;
  int flag = check(str);
  if(flag==0)
  {
    if(ind<=0 && type==1)
    {
      errors++;
      cout<<"Error:Improper limit of array"<<" Name: "<<str<<"\n";
      return;
    }
    temp.name = str;
    temp.var_type = vartype;
    temp.max_index = max(ind,1);
    temp.type = type;
    int temp2;

    for(int i=0;i<temp.max_index;i++)
    {
      temp2 = 0;
      temp.list.push_back(temp2);
    }
    //variables_list.push_back(temp);
    variables_list[str] = temp;
  }
  else
  {
    errors++;
    cout<<"Error:Redeclaration of variable "<<str<<"\n";
    //cout<<errors<<endl;
  }

}

int SymbolTable::check(string str)
{
  int flag=0;
/*  for(int i=0;i<variables_list.size();i++)
  {
    if(str==variables_list[i].name)
    {
      flag=1;
      break;
    }
  } */
  if(variables_list.find(str) == variables_list.end())
    flag = 0;
  else
    flag = 1;
  return flag;
}

int SymbolTable::getvalue(string str,int ind)
{
  int flag = check(str);
  if(flag==0)
  {
    errors++;
    cout<<"Error:Variable Not Declared Name: "<<str<<endl;
    return -1;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Error:Accessing out of bound: Variable: "<<str<<" Index-No: "<<ind<<"\n";
      return 0;
    }
    return variables_list[str].list[ind];

}

void SymbolTable::update(string str,int ind,int val)
{
  int flag = check(str);
  if(flag==0)
  {
    errors++;
    cout<<"Error:Variable Not Declared Name: "<<str<<endl;
    return ;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Error:Accessing out of bound: Variable: "<<str<<" Index-No: "<<ind<<"\n";
      return ;
    }
    variables_list[str].list[ind] = val;
}

SymbolTable *symtable = new SymbolTable();


      /* Visitor Implementation */


void Interpreter::visit(class Program* vis_prog)
{
  if(errors>0)
    return;
  vis_prog->fields->accept(Vis);
  vis_prog->methods->accept(Vis);
}

void Interpreter::visit(class Declaration_list* vis_var)
{
  if(errors>0)
    return;
  for(int i = 0;i<vis_var->decl_stmts.size();i++)
  {
    vis_var->decl_stmts[i]->accept(Vis);
  }
}

void Interpreter::visit(class Decl_stmt* vis_var)
{
  if(errors>0)
    return;
  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Vis,vis_var);
  }
}

void Interpreter::visit(class Expr* vis_var)
{

}

void Interpreter::visit(class Variables* vis_var,class Decl_stmt* vis_var2)
{
  if(errors>0)
    return;
  if(errors>0)
  return;

  vis_var->num_type = vis_var2->type;
  //cout<<name<<" "<<index<<" "<<node_type<<"\n";
  symtable->addnode(vis_var->name,vis_var->index,vis_var->node_type,vis_var->num_type);
}

void Interpreter::visit(Decl_block* vis_var)
{
  if(errors>0)
    return;
    vis_var->decl_list->accept(Vis);
}


/*void Visitor::visit(class Expr2* vis_var)
{
  if(errors>0)
    return;
} */

void Interpreter::visit(class Variables2* vis_var)
{
  if(errors>0)
    return;
  if(vis_var->reqd_expr == NULL)
  {
    vis_var->ind = 0;
  }
  else
  {
    vis_var->ind = vis_var->reqd_expr->accept(Vis);
    //vis_var->ind = vis_var->reqd_expr->value;
  }
  vis_var->val = symtable->getvalue(vis_var->name,vis_var->ind);
  //cout<<name<<" "<<type<<" "<<val<<"\n";
}

int Interpreter::visit(class Expression* vis_var)
{
  if(errors>0)
    return -1;
  int temp1;
  int temp2;

  if(vis_var->e1!=NULL)
  {
    temp1 = vis_var->e1->accept(Vis);
    //temp1 = vis_var->e1->value;
    temp2 = vis_var->e2->accept(Vis);
    //temp2 = vis_var->e2->value;
    int temp3 = vis_var->perform_op(temp1,temp2,vis_var->oper);
    vis_var->value = temp3;
    //cout<<"\n";
  }
  if(vis_var->variable !=NULL)
  {
    vis_var->variable->accept(Vis);
    temp1 = vis_var->variable->val;
    vis_var->value = temp1;
  }
  return vis_var->value;

}

int Interpreter::visit(class BoolExpression* vis_var)
{
  if(errors>0)
    return -1;

  int temp1,temp2;
  if(vis_var->e1!=NULL)
  {
    temp1 = vis_var->e1->accept(Vis);
    //temp1 = vis_var->e1->value;
    temp2 = vis_var->e2->accept(Vis);
    //temp2 = vis_var->e2->value;
    vis_var->value = vis_var->perform_op(temp1,temp2,vis_var->oper);
    //cout<<"\n";
  }

  if(vis_var->variable !=NULL)
  {
    vis_var->variable->accept(Vis);
    temp1 = vis_var->variable->val;
    vis_var->value = temp1;
  }
  return vis_var->value;
}

/*void Visitor::visit(class Statements* var)
{
  if(errors>0)
    return;

} */

void Interpreter::visit(class Stmt* vis_var)
{
  if(errors>0)
    return;

  int temp = vis_var->reqd_expr->accept(Vis);
  //int temp = vis_var->reqd_expr->value;

  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Vis);
    if(errors>0)
    return;
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }

}

void Interpreter::visit(class Statement_list* vis_var)
{
  if(errors>0)
    return;

  if(vis_var->list1!=NULL)
  {
    vis_var->list1->accept(Vis);
  }
  if(vis_var->list2!=NULL)
  {
    vis_var->list2->accept(Vis);
  }

}

void Interpreter::visit(class Condition* vis_var)
{
  if(errors>0)
    return;

  vis_var->val = vis_var->reqd_expr->accept(Vis);
  //vis_var->val = vis_var->reqd_expr->value;
  if(vis_var->val==1)
  {
    vis_var->list1->accept(Vis);
  }
  else
  {
    if(vis_var->list2 != NULL)
    {
      vis_var->list2->accept(Vis);
    }
  }

}

void Interpreter::visit(class WhileLoop* vis_var)
{
  if(errors>0)
    return;

  vis_var->val = vis_var->reqd_expr->accept(Vis);
  //vis_var->val = vis_var->reqd_expr->value;
  while(vis_var->val==1)
  {
    vis_var->list1->accept(Vis);
    vis_var->val = vis_var->reqd_expr->accept(Vis);
    //vis_var->val = vis_var->reqd_expr->value;
  }

}

void Interpreter::visit(class ForLoop* vis_var)
{
  if(errors>0)
    return;

  int temp=vis_var->val1;
  vis_var->var->accept(Vis);
  symtable->update(vis_var->var->name,vis_var->var->ind,temp);

  while(temp<=vis_var->val3)
  {
    vis_var->list1->accept(Vis);
    temp = temp + vis_var->val2;
    vis_var->var->accept(Vis);
    symtable->update(vis_var->var->name,vis_var->var->ind,temp);
  }

}

void Interpreter::visit(class Prt* vis_var)
{
  if(errors>0)
    return;

  if(vis_var->text!="")
    cout<<(vis_var->text)<<" ";
  if(vis_var->var!=NULL)
  {
    vis_var->var->accept(Vis);
    int temp = vis_var->var->val;
    cout<<temp<<" ";
  }

}

void Interpreter::visit(class PrintStmt* vis_var)
{
  if(errors>0)
    return;

  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Vis);
  }

}

void Interpreter::visit(class Print* vis_var)
{
  if(errors>0)
    return;

  vis_var->reqd->accept(Vis);
  if(vis_var->type == 1)
  cout<<"\n";

}

void Interpreter::visit(class ReadVars* vis_var)
{
  if(errors>0)
    return;

  for(int i=0;i<vis_var->list.size();i++)
  {
    int temp;
    cin>>temp;
    vis_var->list[i]->accept(Vis);
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }

}

void Interpreter::visit(class Read* vis_var)
{
  if(errors>0)
    return;

  for(int i=0;i<vis_var->list.size();i++)
  {
    int temp;
    cin>>temp;
    vis_var->list[i]->accept(Vis);
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }

}

void Interpreter::visit(class GoToLoop* vis_var)
{
  if(errors>0)
    return;

  if(vis_var->name1!=vis_var->name2)
  {
    errors++;
    cout<<"Identifiers doesn't match: "<<vis_var->name1<<" "<<vis_var->name2<<endl;
    return;
  }
  if(vis_var->reqd_expr!=NULL)
  {
    int temp = vis_var->reqd_expr->accept(Vis);
    //int temp = vis_var->reqd_expr->value;
    while(temp==1)
    {
      vis_var->list1->accept(Vis);
      temp = vis_var->reqd_expr->accept(Vis);
      //int temp = vis_var->reqd_expr->value;
    }
  }
  else
  {
    while(1)
      vis_var->list1->accept(Vis);
  }


}

void Interpreter::visit(class Code_block* vis_var)
{
  if(errors>0)
    return;

  vis_var->stmt_list->accept(Vis);

}
    /*   Visitor Ends */

    /* Constructors */

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

Declaration_list::Declaration_list()
{
    //decl_stmts.push_back(b1);
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
  symtable2->addnode(str,var2);
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
  val2 = var4;
  val3 = var3;
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

Print::Print(class PrintStmt *var,int val)
{
  type = val;
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

GoToLoop::GoToLoop(string str,class Statement_list* var,string str2)
{
  name1 = str;
  name2 = str2;
  list1 = var;
  val = 1;
  reqd_expr = NULL;
}
GoToLoop::GoToLoop(string str,class Statement_list* var,string str2,class BoolExpression *var1)
{
  name1 = str;
  name2 = str2;
  list1 = var;
  reqd_expr = var1;
}

    /* traversal */
    
int Expression::perform_op(int temp1,int temp2,string oper)
{
  if(oper == "+")
  {
    return (temp1 + temp2);
  }
  else if(oper == "-")
  {
    return (temp1 - temp2);
  }
  else if(oper == "*")
  {
    return (temp1*temp2);
  }
  else if(oper == "/")
  {
    if(temp2==0)
    {
      errors++;
      cout<<"Division operation failed \n";
      return -1;
    }
    return (temp1/temp2);
  }
  else if(oper == "%")
  {
    return (temp1%temp2);
  }
  else if(oper == "&")
  {
    return (temp1&temp2);
  }
  else if(oper == "^")
  {
    return (temp1^temp2);
  }
  else if(oper == "|")
  {
    return (temp1|temp2);
  }
}



int BoolExpression::perform_op(int temp1,int temp2,string op)
{
  if(op=="||")
  {
    return temp1||temp2;
  }
  else if(op=="&&")
  {
    return (temp1&&temp2);
  }
  else if(op=="==")
  {
    return (temp1==temp2);
  }
  else if(op == "!=")
  {
    return (temp1!=temp2);
  }
  else if(op== ">=")
  {
    return (temp1>=temp2);
  }
  else if(op == ">")
  {
    return (temp1>temp2);
  }
  else if(op == "<=")
  {
    return (temp1<=temp2);
  }
  else if(op == "<")
  {
    return (temp1<temp2);
  }
}
