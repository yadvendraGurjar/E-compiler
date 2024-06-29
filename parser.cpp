/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

bool isOperator(string s){
    if(s=="+" || s =="-"|| s=="*" || s =="/") return true;
    return false;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode *root = new ExprTreeNode(expression[1], 0);
    root->left = new ExprTreeNode(expression[0], 0);
    ExprTreeNode *rightNode = NULL;
    vector<ExprTreeNode *> stk;
    int s = 0;
    int i = 2;
    while(i < expression.size()){
        if (expression[i] == "("){
            i++;
            string next = expression[i];
            if (next == "("){
                continue;
            }
            ExprTreeNode *node = new ExprTreeNode(next, 0);
            stk.push_back(node);
            s++;
            i++;
        }
        else if(expression[i] == ")"){
            ExprTreeNode *temp = stk[s - 1];
            stk.pop_back();
            s--;
            ExprTreeNode *node = stk[s - 1];
            stk.pop_back();
            s--;
            node->right = temp;
            stk.push_back(node);
            s++;
            i++;
        }
        else if(isOperator(expression[i])){
            ExprTreeNode *node;
            node = new ExprTreeNode(expression[i], 0);
            node->left = stk[s - 1];
            stk.pop_back();
            stk.push_back(node);
            i++;
        }
        else{
            ExprTreeNode *node = new ExprTreeNode(expression[i], 0);
            if (s == 0){
                rightNode = node;
                break;
            }
            stk.push_back(node);
            s++;
            i++;
        }
    }
    if(rightNode == NULL){
        rightNode = stk[0];
        stk.pop_back();
    }
    root->right = rightNode;
    if(root->left->type == "VAR"){
        symtable->insert(root->left->id);
    }
    expr_trees.push_back(root);
}

Parser::~Parser(){
    for (long unsigned i = 0; i < expr_trees.size(); i++)
    {
        expr_trees[i] = NULL;
        delete expr_trees[i];
    }
    expr_trees.clear();
    delete symtable;
}