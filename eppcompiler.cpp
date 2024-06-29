/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
  Parser* targ = new Parser();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
  memory_size = mem_limit;
  output_file = out_file;
  mem_loc = vector<int>(mem_limit);
}

void EPPCompiler::compile(vector<vector<string>> code){
  for(int i = 0 ; i < memory_size ; i++){
    least_mem_loc.push_heap(i);
  }
  for(int i = 0 ; i<code.size() ; i++){
    targ.parse(code[i]);
    vector<string> cmds = generate_targ_commands();
    // for(int i = 0 ; i < cmds.size() ; i++){
    //   cout<<cmds[i];
    // }
    write_to_file(cmds);
  }
}

void postOrderTraversal(ExprTreeNode* node , vector<ExprTreeNode*>& stk) {
  if (node == NULL) {
    return;
  }
  postOrderTraversal(node->right , stk);
  postOrderTraversal(node->left , stk);
  stk.push_back(node);
}

vector<string> EPPCompiler::generate_targ_commands(){
  int sz = targ.expr_trees.size();
  ExprTreeNode* root = targ.expr_trees[sz-1];
  vector<string> res;
  vector<ExprTreeNode*> vec;
  postOrderTraversal(root , vec);
  for(int i = 0 ; i < vec.size()-2 ; i++){
    if(vec[1]->type != "DEL"){
    if(vec[i]->type == "VAR"){
      int ads = targ.symtable->search(vec[i]->id);
      string s = "PUSH mem[";
      string u = to_string(ads);
      s += u ;
      s.push_back(']');
      res.push_back(s);
    }
    else if(vec[i]->type == "VAL"){
      int ads = vec[i]->num;
      string s = "PUSH ";
      string u = to_string(ads);
      s += u;
      res.push_back(s);
    }
    else if(vec[i]->type == "ADD"){
      res.push_back("ADD");
    }
    else if(vec[i]->type == "SUB"){
      res.push_back("SUB");
    }
    else if(vec[i]->type == "MUL"){
      res.push_back("MUL");
    }
    else{
      res.push_back("DIV");
    }
    }
  }
  ExprTreeNode* temp = vec[vec.size()-2];
  if(temp->type == "VAR"){
    int ars = least_mem_loc.get_min();
    targ.symtable->assign_address(temp->id , ars);
    string s = "mem[";
    string u = to_string(ars);
    string t = "] = POP";
    s = s + u + t;
    res.push_back(s);
    least_mem_loc.pop();
  }
  else if(temp->type == "DEL"){
    int ads = targ.symtable->search(vec[0]->id);
    string s = "DEL = mem[";
    string u = to_string(ads);
    s += u;
    s.push_back(']');
    targ.symtable->remove(vec[0]->id);
    least_mem_loc.push_heap(ads);
    res.push_back(s);
  }
  else{
    string s = "RET = POP";
    res.push_back(s);
  }
  return res;
}

void EPPCompiler::write_to_file(vector<string> commands){
  ofstream MyWriteFile(output_file,ios::app);
  int i ;
  for (i=0;i<commands.size();i++) {
    MyWriteFile <<commands[i];
    MyWriteFile << std::endl;
  }
  MyWriteFile.close();
}

EPPCompiler::~EPPCompiler(){
}
