#include<bits/stdc++.h>
using namespace std;
#include "classes.h"
extern int line_num;
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
      cout<<"Improper limit of array"<<" Name: "<<str<<"\n";
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
    cout<<"Redeclaration of variable "<<str<<"\n";
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
    cout<<"Variable Not Declared Name: "<<str<<endl;
    return -1;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Accessing out of bound"<<str<<" Index-No: "<<ind<<"\n";
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
    cout<<"Variable Not Declared Name: "<<str<<endl;
    return ;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Accessing out of bound: Variable: "<<str<<" Index-No: "<<ind<<"\n";
      return ;
    }
    variables_list[str].list[ind] = val;
}

SymbolTable *symtable = new SymbolTable();


      /* Visitor Implementation

void Visitor::visit(class Program* vis_prog)
{
  if(errors>0)
    return;
  vis_prog->fields->accept(Visitor V);
  vis_prog->methods->accept(Visitor V);
}

void Visitor::visit(class Declaration_list* vis_var)
{
  if(errors>0)
    return;
  for(int i = 0;i<vis_var->decl_stmts.size();i++)
  {
    vis_var->decl_stmts[i]->accept(Visitor V);
  }
}

void Visitor::visit(class Decl_stmt* vis_var)
{
  if(errors>0)
    return;
  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Visitor V,vis_var);
  }
}

void Visitor::visit(class Variables* vis_var,class Decl_stmt* vis_var2)
{
  if(errors>0)
    return;
  if(errors>0)
  return;

  vis_var->num_type = vis_var2->type;
  //cout<<name<<" "<<index<<" "<<node_type<<"\n";
  symtable->addnode(vis_var->name,vis_var->index,vis_var->node_type,vis_var->num_type);


}


void Visitor::visit(class Decl_block* vis_var)
{
  if(errors>0)
    return;

    vis_var->decl_list->accept(Visitor V);

}

void Visitor::visit(class Expr2* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Variables2* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Expression* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class BoolExpression* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Statements* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Stmt* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Statement_list* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Condition* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class WhileLoop* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class ForLoop* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Prt* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class PrintStmt* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Print* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class ReadVars* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Read* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class GoToLoop* var)
{
  if(errors>0)
    return;

}

void Visitor::visit(class Code_block* var)
{
  if(errors>0)
    return;

}
       Visitor Ends */

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

void Variables::traverse(string vartype)
{
  if(errors>0)
  return;

  num_type = vartype;
  //cout<<name<<" "<<index<<" "<<node_type<<"\n";
  symtable->addnode(name,index,node_type,vartype);
}
void Expr::traverse()
{
  if(errors>0)
  return;

  string str="int";
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse(str);
  }
}
void Decl_stmt::traverse()
{
  if(errors>0)
  return;

  //cout<<type<<"\n";
  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse(type);
  }
}
void Declaration_list::traverse()
{
  if(errors>0)
  return;

  for(int i=0;i<decl_stmts.size();i++)
  {
    decl_stmts[i]->traverse();
  }
}
void Decl_block::traverse()
{
  if(errors>0)
  return;

  //cout<<"Decl_block\n";
  decl_list->traverse();
}



int Variables2::traverse()
{
  if(errors>0)
  return -1;


  if(reqd_expr == NULL)
  {
    ind = 0;
  }
  else
  {
    ind = reqd_expr->traverse();
  }
  val = symtable->getvalue(name,ind);
  //cout<<name<<" "<<type<<" "<<val<<"\n";
  return val;
}

void Variables2::updateval(int ans)
{
  if(errors>0)
  return ;

  if(reqd_expr == NULL)
  {
    ind = 0;
    symtable->update(name,0,ans);
    return;
  }
  else
  {
    ind = reqd_expr->traverse();
    symtable->update(name,ind,ans);
    return ;
  }
}


int Expression::traverse()
{
  if(errors>0)
  return -1;
  int temp1;
  int temp2;

  if(e1!=NULL)
  {
    temp1 = e1->traverse();
    temp2 = e2->traverse();
    int temp3 = perform_op(temp1,temp2,oper);
    value = temp3;
    //cout<<"\n";
  }
  if(variable !=NULL)
  {
    temp1 = variable->traverse();
    value = temp1;
  }
  //cout<<value<<"\n";
  //cout<<"\n\n";

  return value;

}

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


int BoolExpression::traverse()
{
  if(errors>0)
  return -1;

  int temp1,temp2;
  if(e1!=NULL)
  {
    temp1 = e1->traverse();
    temp2 = e2->traverse();
    value = perform_op(temp1,temp2,oper);
    //cout<<"\n";
  }

  if(variable !=NULL)
  {
    temp1 = variable->traverse();
    value = temp1;
  }
  //cout<<value<<"\n";


  return value;
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

void Stmt::traverse()
{
  if(errors>0)
  return;
  int temp = reqd_expr->traverse();

  for(int i=0;i<list.size();i++)
  {
    list[i]->updateval(temp);
  }
  //cout<<"\n\n";
}

void Statement_list::traverse()
{
  if(errors>0)
  return;

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
  if(errors>0)
  return;

  //cout<<"IFELSE\n";
  val = reqd_expr->traverse();
  if(val==1)
  {
    list1->traverse();
  }
  else
  {
    if(list2 != NULL)
    {
      list2->traverse();
    }
  }
  //cout<<"\n";
}
void WhileLoop::traverse()
{
  if(errors>0)
  return;

  //cout<<"WHILE\n";

  val = reqd_expr->traverse();
  while(val==1)
  {
    list1->traverse();
    val = reqd_expr->traverse();
  }
  //cout<<"\n";
}
void ForLoop::traverse()
{
  if(errors>0)
  return;

  //cout<<"FOR\n";
  //cout<<val1<<" "<<val2<<" "<<val3<<"\n";
  int temp=val1;
  var->updateval(val1);

  while(temp<=val3)
  {
    list1->traverse();
    temp = temp + val2;
    var->updateval(temp);
  }
  //cout<<"\n";
}
void Prt::traverse()
{
  if(errors>0)
  return;

  if(text!="")
    cout<<text<<" ";
  if(var!=NULL)
  {
    int temp = var->traverse();
    cout<<temp<<" ";
  }
}
void PrintStmt::traverse()
{
  if(errors>0)
  return;

  for(int i=0;i<list.size();i++)
  {
    list[i]->traverse();
  }
}
void Print::traverse()
{
  if(errors>0)
  return;

  reqd->traverse();
  if(type == 1)
  cout<<"\n";

}
void ReadVars::traverse()
{
  if(errors>0)
  return;

  for(int i=0;i<list.size();i++)
  {
    int temp;
    cin>>temp;
    list[i]->updateval(temp);
  }
}
void Read::traverse()
{
  if(errors>0)
  return;

  //cout<<"Read\n";
  for(int i=0;i<list.size();i++)
  {
    int temp;
    cin>>temp;
    list[i]->updateval(temp);
  }
}
void GoToLoop::traverse()
{
  if(errors>0)
  return;
  if(name1!=name2)
  {
    errors++;
    cout<<"Identifiers doesn't match: "<<name1<<" "<<name2<<endl;
    return;
  }
  if(reqd_expr!=NULL)
  {
    int temp = reqd_expr->traverse();
    while(temp==1)
    {
      list1->traverse();
      temp = reqd_expr->traverse();
    }
  }
  else
  {
    while(1)
      list1->traverse();
  }
}
void Code_block::traverse()
{
  if(errors>0)
  return;

  stmt_list->traverse();
}
void Program::traverse()
{
  if(errors>0)
  return;

  fields->traverse();
  methods->traverse();

/*  if(errors>0)
  {
    cout<<"No.of errors: "<<errors<<endl;
  } */
}
