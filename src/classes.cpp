#include<bits/stdc++.h>
#include "classes.h"

using namespace std;
using namespace llvm;

extern int line_num;
//Interpreter *Vis = new Interpreter();
extern Visitor *Vis;
int errors;

static LLVMContext &Context = getGlobalContext();
static Module *TheModule = new Module("FlatB Compiler",Context);
map<string,BasicBlock*> labels_list;
static IRBuilder<> Builder(Context);

Function* createFunc(IRBuilder<> &Builder,string name)
{
  FunctionType* functype = FunctionType::get(Builder.getInt32Ty(),false);
  Function *tempfunc = Function::Create(
    functype,Function::ExternalLinkage,name,TheModule);
  return tempfunc;

}

BasicBlock *CreateBB(Function *tempfunc,string name)
{
  return BasicBlock::Create(Context,name,tempfunc);
}

GlobalVariable* createGlob(IRBuilder<> &Builder,string name,int type,int max_index)
{
  GlobalVariable *gvar;
  if(type==0)
  {
    TheModule->getOrInsertGlobal(name,Builder.getInt32Ty());
    gvar = TheModule->getNamedGlobal(name);
    gvar->setLinkage(GlobalValue::CommonLinkage);
    gvar->setAlignment(4);
    ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,0));
    gvar->setInitializer(const_int_val);
  }
  else
  {
    Type * var = (Type*)ArrayType::get(Type::getInt32Ty(getGlobalContext()), max_index);
    TheModule->getOrInsertGlobal(name,var);
    gvar = TheModule->getNamedGlobal(name);
    gvar->setLinkage(GlobalValue::CommonLinkage);
    gvar->setAlignment(4);
    gvar->setInitializer(ConstantAggregateZero::get(var));
  }
  return gvar;

}

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
    exit(0);
  }
}

class Statement_list * SymbolTable2::getptr(string str)
{
  class Statement_list* temp_ptr=NULL;
  if(references_list.find(str)==references_list.end())
  {
    errors++;
    cout<<"Reference Not declared Ref is: "<<str<<endl;
    exit(0);
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
      exit(0);
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
    exit(0);
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
    exit(0);
    return -1;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Error:Accessing out of bound: Variable: "<<str<<" Index-No: "<<ind<<"\n";
      exit(0);
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
    exit(0);
    return ;
  }
  if(variables_list[str].max_index<ind+1 || ind<0)
    {
      errors++;
      cout<<"Error:Accessing out of bound: Variable: "<<str<<" Index-No: "<<ind<<"\n";
      exit(0);
      return ;
    }
    variables_list[str].list[ind] = val;
}

SymbolTable *symtable = new SymbolTable();



          /* Code-generation Starts */
Value* Program::codegen()
{
  //GlobalVariable* gvar= createGlob(Builder,"var");
  Value* V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  V = fields->codegen();
  Function* temp_func = createFunc(Builder,"main");
  BasicBlock *entry = CreateBB(temp_func,"entry");
  for (map<string,Ref_node>::iterator it=symtable2->references_list.begin(); it!=symtable2->references_list.end(); ++it)
  {
    BasicBlock *temp = CreateBB(temp_func,it->first);
    labels_list[it->first]=temp;
  }
  Builder.SetInsertPoint(entry);

  V = methods->codegen();
  Builder.CreateRet(Builder.getInt32(0));
  verifyFunction(*temp_func);

  return V;
}

void Program::generateCode()
{
  cout<<"Generating LLVM IR CODE"<<endl;
  TheModule->dump();
}

Value* Declaration_list::codegen()
{
  Value* V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  for(int i=0;i<decl_stmts.size();i++)
  {
    V = decl_stmts[i]->codegen();
  }
  return V;
}

Value* Decl_stmt::codegen()
{
  Value* V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  for(int i=0;i<list.size();i++)
  {
    V = list[i]->codegen();
  }
  return V;
}

Value* Variables::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  Var_node temp1 = symtable->variables_list[name];
  GlobalVariable* gvar= createGlob(Builder,name,temp1.type,temp1.max_index);

  return V;

}
Value* Expr::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  return V;
}

Value* Decl_block::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  V = decl_list->codegen();
  return V;
}

Value* Variables2::codegen(int flag)
{
  Value *V = TheModule->getNamedGlobal(name);
  Value* index = 0;
  if(reqd_expr != NULL)
  {
    Value* index = reqd_expr->codegen();
    vector<Value*> arr_ind;
    arr_ind.push_back(Builder.getInt32(0));
    arr_ind.push_back(index);
    V = Builder.CreateGEP(V,arr_ind,name);
    if(flag==1)
      V = Builder.CreateLoad(V);
  }
  else
  {
    if(flag==1)
      V = Builder.CreateLoad(V);
  }
  return V;
}

Value* Expression::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));

  if(e1==NULL)
  {
    if(variable == NULL)
    {
      V = Builder.getInt32(value);
    }
    else
    {
      V = variable->codegen(1);
    }
    return V;
  }

  Value *V1 = e1->codegen();
  Value *V2 = e2->codegen();
  if(V1==0||V2==0)
  {
    cout<<"Error in expression"<<endl;

  }
  if(oper == "+")
  {
    V = Builder.CreateAdd(V1,V2,"AddOp");
  }
  else if(oper == "-")
  {
    V = Builder.CreateSub(V1,V2,"SubOp");
  }
  else if(oper == "*")
  {
    V = Builder.CreateMul(V1,V2,"MulOp");
  }
  else if(oper == "/")
  {
    V = Builder.CreateUDiv(V1,V2,"DivOp");
  }
  else if(oper == "%")
  {
    V = Builder.CreateURem(V1,V2,"ModOp");
  }
  else if(oper == "&")
  {
    V = Builder.CreateAnd(V1,V2,"unaryandOp");
  }
  else if(oper == "^")
  {
    V = Builder.CreateXor(V1,V2,"unaryxorOp");
  }
  else if(oper == "|")
  {
    V = Builder.CreateOr(V1,V2,"unaryorOp");
  }
  return V;
}

Value* BoolExpression::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));

  Value *V1 = e1->codegen();
  Value *V2 = e2->codegen();
  if(oper == "||")
  {
    if(V1==Builder.getInt32(1)||V2==Builder.getInt32(1))
      V = Builder.getInt32(1);
    //V = Builder.CreateICmpOr(V1,V2,"COr");
  }
  else if(oper == "&&")
  {
    if(V1==Builder.getInt32(1) && V2==Builder.getInt32(1))
      V = Builder.getInt32(1);
    // V = Builder.CreateICmpAnd(V1,V2,"CAnd");
  }
  else if(oper == "==")
  {
    V = Builder.CreateICmpEQ(V1,V2,"CE");
  }
  else if(oper == "!=")
  {
    V = Builder.CreateICmpNE(V1,V2,"CNE");
  }
  else if(oper == ">=")
  {
    V = Builder.CreateICmpUGE(V1,V2,"CGE");
  }
  else if(oper == ">")
  {
    V = Builder.CreateICmpUGT(V1,V2,"CGT");
  }
  else if(oper == "<=")
  {
    V = Builder.CreateICmpULE(V1,V2,"CLE");
  }
  else if(oper == "<")
  {
    V = Builder.CreateICmpULT(V1,V2,"CLT");
  }
  return V;
}

Value* Stmt::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));

  Value* req_val = reqd_expr->codegen();
  for(int i=0;i<list.size();i++)
  {
    V = list[i]->codegen(0);
    V = Builder.CreateStore(req_val,V);
  }

  return V;
}

Value* Statement_list::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  if(list1 == NULL && list2 == NULL)
  {
  }
  else if(list1!=NULL && list2 !=NULL)
  {
    V = list1->codegen();
    V = list2->codegen();
  }
  else if(list1==NULL && list2!=NULL)
  {
    Builder.CreateBr(labels_list[name]);
    Builder.SetInsertPoint(labels_list[name]);
    V = list2->codegen();
  }
  return V;
}
Value* Condition::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  Value *req_val = reqd_expr->codegen();
  req_val = Builder.CreateICmpNE(req_val,Builder.getInt1(0),"ifCond");
  Function *req_func = Builder.GetInsertBlock()->getParent();
  BasicBlock *ifBlock = CreateBB(req_func,"ifBlock");
  BasicBlock *elseBlock = CreateBB(req_func,"elseBlock");
  BasicBlock *contBlock = CreateBB(req_func,"contBlock");
  Builder.CreateCondBr(req_val,ifBlock,elseBlock);

  Builder.SetInsertPoint(ifBlock);
  Value* if_val = list1->codegen();
  if(if_val==0)
  return 0;

  Builder.CreateBr(contBlock);
  // ifBlock = Builder.GetInsertBlock();
  //
  // req_func->getBasicBlockList().push_back(elseBlock);
  Builder.SetInsertPoint(elseBlock);
  Value *else_val = ConstantInt::get(getGlobalContext(),APInt(32,0));
  if(list2!=NULL)
  {
    else_val = list2->codegen();
    if(else_val==0)
    return 0;

  }
  Builder.CreateBr(contBlock);
  // elseBlock = Builder.GetInsertBlock();
  // req_func->getBasicBlockList().push_back(contBlock);
  Builder.SetInsertPoint(contBlock);

  // PHINode *phi = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()),2,"IfOp");
  // phi->addIncoming(if_val,ifBlock);
  // phi->addIncoming(else_val,elseBlock);

  return V;
}

Value* WhileLoop::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  Value *req_val = reqd_expr->codegen();
  Function *req_func = Builder.GetInsertBlock()->getParent();
  BasicBlock *loopBB = CreateBB(req_func,"loopBlock");
  BasicBlock *nextBB = CreateBB(req_func,"nextBlock");
  Builder.CreateCondBr(req_val,loopBB,nextBB);
  Builder.SetInsertPoint(loopBB);
  Value *loop_val = list1->codegen();
  if(loop_val==0)
    return 0;

  Builder.CreateCondBr(req_val,loopBB,nextBB);

  Builder.SetInsertPoint(nextBB);

  return V;
}

Value* ForLoop::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  Value *req_var_addr = var->codegen(0);

  Value *init_val = Builder.getInt32(val1);
  Value *Inc_val = Builder.getInt32(val2);
  Value *Fin_val = Builder.getInt32(val3);

  V = Builder.CreateStore(init_val,req_var_addr);
  Function *req_func = Builder.GetInsertBlock()->getParent();
  // BasicBlock *PreHeaderBB = Builder.GetInsertBlock();
  BasicBlock *loopBB = CreateBB(req_func,"loopBlock");
  BasicBlock *nextBB = CreateBB(req_func,"nextBlock");
  Value *req_var = Builder.CreateLoad(req_var_addr);
  Value *cond_val = Builder.CreateICmpULE(req_var,Fin_val,"cond_cont");

  Builder.CreateCondBr(cond_val,loopBB,nextBB);

  Builder.SetInsertPoint(loopBB);
  Value* loop_val = list1->codegen();
  if(loop_val == 0)
    return 0;

  req_var = Builder.CreateLoad(req_var_addr);
  Value* next_val = Builder.CreateAdd(req_var,Inc_val,"update");
  V = Builder.CreateStore(next_val,req_var_addr);
  cond_val = Builder.CreateICmpULE(next_val,Fin_val,"cond_cont");

  Builder.CreateCondBr(cond_val,loopBB,nextBB);

  // loopBB = Builder.GetInsertBlock();
  // req_func->getBasicBlockList().push_back(nextBB);

  Builder.SetInsertPoint(nextBB);

  // PHINode *phi = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()),2,"LoopOp");
  // phi->addIncoming(loop_val,loopBB);

  return V;
}

Value *Prt::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  if(var == NULL)
  {
    text = text.substr(1,text.length()-2);
    V = Builder.CreateGlobalStringPtr(text);
  }
  else
  {
    V = var->codegen(1);
  }
  return V;
}

Value *PrintStmt::codegen(int flag)
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  vector<Value*> args;
  vector<Type*> arg_type;

  string str;
  str ="";
  for(int i=0;i<list.size();i++)
  {
    if(list[i]->var !=NULL)
    {
      str = str + "%d ";
    }
    else
    {
      string temp = list[i]->text.substr(1,list[i]->text.length()-2);
      str = str + temp + " ";
    }
  }
  if(flag ==1 )
  str = str + "\n";

  V = Builder.CreateGlobalStringPtr(str);
  args.push_back(V);
  arg_type.push_back(V->getType());

  for(int i=0;i<list.size();i++)
  {
    V = list[i]->codegen();
    if(list[i]->var !=NULL)
    {
      args.push_back(V);
      arg_type.push_back(V->getType());
    }
  }
  //llvm::ArrayRef<Value*> typeargs(arg_type);
  llvm::ArrayRef<Value*> refargs(args);
  llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), arg_type, false);
  Constant* printfunc = TheModule->getOrInsertFunction("printf", FType);
  return Builder.CreateCall(printfunc,refargs);
}

Value *Print::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  V = reqd->codegen(type);
  return V;
}

Value* ReadVars::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  return V;
}

Value* Read::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  vector<Value*> args;
  vector<Type*> arg_type;
  string str;
  str = "";
  for(int i=0;i<list.size();i++)
  {
    str = str + "%d";
  }

  V = Builder.CreateGlobalStringPtr(str);
  args.push_back(V);
  arg_type.push_back(V->getType());

  for(int i=0;i<list.size();i++)
  {
    V = list[i]->codegen(0);
    args.push_back(V);
    arg_type.push_back(V->getType());
  }
  llvm::ArrayRef<Value*> refargs(args);
  llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), arg_type, false);
  Constant* readfunc = TheModule->getOrInsertFunction("scanf", FType);
  return Builder.CreateCall(readfunc,refargs);
}
Value* GoToLoop::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  Function *req_func = Builder.GetInsertBlock()->getParent();
  BasicBlock *tempBB = CreateBB(req_func,"nextBB");
  if(reqd_expr==NULL)
  {
    Builder.CreateBr(labels_list[name]);
  }
  else
  {
    Value *req_val = reqd_expr->codegen();
    BasicBlock *lab = labels_list[name];
    Builder.CreateCondBr(req_val,lab,tempBB);
  }
  Builder.SetInsertPoint(tempBB);
  return V;
}
Value* Code_block::codegen()
{
  Value *V = ConstantInt::get(getGlobalContext(),APInt(32,0));
  V = stmt_list->codegen();
  return V;
}

      /* Code-generation ends */


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

int Interpreter::visit(class Variables2* vis_var)
{
  if(errors>0)
    return -1;
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
  return 0;
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

int Interpreter::visit(class Stmt* vis_var)
{
  if(errors>0)
    return -1;

  int temp = vis_var->reqd_expr->accept(Vis);
  //int temp = vis_var->reqd_expr->value;

  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Vis);
    if(errors>0)
    return -1;
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }
  return 0;

}

int Interpreter::visit(class Statement_list* vis_var)
{
  if(errors>0)
    return -1;
  int temp_check;

  if(vis_var->type == "GOTO")
  {
    if(vis_var->list1->accept(Vis))
    {
        vis_var->list3 = vis_var->list1->getptr();
        if(vis_var->list3!=NULL)
          temp_check = vis_var->list3->accept(Vis);
        return -1;
    }
    else
    {
      if(temp_check==-1)
      return -1;
      if(vis_var->list2!=NULL)
      temp_check = vis_var->list2->accept(Vis);
      if(temp_check==-1)
      return -1;
    }
  }
  else
  {
    if(vis_var->list1!=NULL)
    {
      temp_check = vis_var->list1->accept(Vis);
      if(temp_check==-1)
      return -1;
    }

    if(vis_var->list2!=NULL)
    {
      if(temp_check==-1)
      return -1;
      temp_check = vis_var->list2->accept(Vis);
      if(temp_check==-1)
      return -1;
    }
  }
  return 0;

}

int Interpreter::visit(class Condition* vis_var)
{
  if(errors>0)
    return -1;
  int temp_check;
  vis_var->val = vis_var->reqd_expr->accept(Vis);
  //vis_var->val = vis_var->reqd_expr->value;
  if(vis_var->val==1)
  {
    temp_check = vis_var->list1->accept(Vis);
    return temp_check;
  }
  else
  {
    if(vis_var->list2 != NULL)
    {
      temp_check = vis_var->list2->accept(Vis);
      return temp_check;
    }
  }
  return 0;

}

int Interpreter::visit(class WhileLoop* vis_var)
{
  if(errors>0)
    return -1;
  int temp_check;
  vis_var->val = vis_var->reqd_expr->accept(Vis);
  //vis_var->val = vis_var->reqd_expr->value;
  while(vis_var->val==1)
  {
    temp_check = vis_var->list1->accept(Vis);
    if(temp_check==-1)
    return -1;
    vis_var->val = vis_var->reqd_expr->accept(Vis);
    //vis_var->val = vis_var->reqd_expr->value;
  }
  return 0;

}

int Interpreter::visit(class ForLoop* vis_var)
{
  if(errors>0)
    return -1;
  int temp_check;
  int temp=vis_var->val1;
  vis_var->var->accept(Vis);
  symtable->update(vis_var->var->name,vis_var->var->ind,temp);

  while(temp<=vis_var->val3)
  {
    temp_check = vis_var->list1->accept(Vis);
    if(temp_check == -1)
    return temp_check;
    temp = temp + vis_var->val2;
    vis_var->var->accept(Vis);
    symtable->update(vis_var->var->name,vis_var->var->ind,temp);
  }
  return 0;

}

int Interpreter::visit(class Prt* vis_var)
{
  if(errors>0)
    return -1;

  if(vis_var->text!="")
    cout<<vis_var->text.substr(1,vis_var->text.length()-2)<<" ";
  if(vis_var->var!=NULL)
  {
    vis_var->var->accept(Vis);
    int temp = vis_var->var->val;
    cout<<temp<<" ";
  }
  return 0;

}

int Interpreter::visit(class PrintStmt* vis_var)
{
  if(errors>0)
    return -1;

  for(int i=0;i<vis_var->list.size();i++)
  {
    vis_var->list[i]->accept(Vis);
  }
  return 0;

}

int Interpreter::visit(class Print* vis_var)
{
  if(errors>0)
    return -1;

  vis_var->reqd->accept(Vis);
  if(vis_var->type == 1)
  cout<<"\n";
  return 0;

}

int Interpreter::visit(class ReadVars* vis_var)
{
  if(errors>0)
    return -1;

  for(int i=0;i<vis_var->list.size();i++)
  {
    int temp;
    cin>>temp;
    vis_var->list[i]->accept(Vis);
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }
  return 0;

}

int Interpreter::visit(class Read* vis_var)
{
  if(errors>0)
    return -1;

  for(int i=0;i<vis_var->list.size();i++)
  {
    int temp;
    cin>>temp;
    vis_var->list[i]->accept(Vis);
    symtable->update(vis_var->list[i]->name,vis_var->list[i]->ind,temp);
  }
  return 0;

}

int Interpreter::visit(class GoToLoop* vis_var)
{
  if(errors>0)
    return -1;
  vis_var->list1 = symtable2->getptr(vis_var->name);
  if(errors>0)
  return -1;
  if(vis_var->reqd_expr!=NULL)
  {
    int temp = vis_var->reqd_expr->accept(Vis);
    //int temp = vis_var->reqd_expr->value;
    vis_var->val = temp;
    if(vis_var->val)
    {
      //vis_var->list1->accept(Vis);
      //temp = vis_var->reqd_expr->accept(Vis);
      //int temp = vis_var->reqd_expr->value;
    }
  }
  else
  {
    vis_var->val = 1;
    // if(vis_var->val)
    //   vis_var->list1->accept(Vis);
  }
  return vis_var->val;

}

void Interpreter::visit(class Code_block* vis_var)
{
  if(errors>0)
    return ;

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
  e1 = NULL;
  e2 = NULL;
  variable = NULL;
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

Statement_list::Statement_list(class Statements* var1,class Statement_list *var2,string txt)
{
  count = 0;
  type = txt;
  name = "";
  list1 = var1;
  list2 = var2;
}
Statement_list::Statement_list(string str,class Statement_list *var2)
{
  type = "NOT_GOTO";
  count = 0;
  name = str;
  symtable2->addnode(str,var2);
  list2 = var2;
  list1 = NULL;
}
Statement_list::Statement_list()
{
  count = 0;
  type = "NOT_GOTO";
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
