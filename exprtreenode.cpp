/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    left=nullptr;
    right=nullptr;
}

bool is_digits1(string& str){
    if(str[0] == '-'){
        for (int i = 1 ; i< str.size() ; i++) {
            char ch = str[i];
            if (!(ch >= 48 && ch <= 57)) {
                return false;
            }
        }
    }
    else{
    for (int i = 0 ; i< str.size() ; i++) {
        char ch = str[i];
            if (!(ch >= 48 && ch <= 57)) {
                return false;
            }
        }
    }
    return true;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    left=NULL;
    right=NULL;
    if (t == "+"){
        type = "ADD";
        num = v;
    }
    else if (t == "-"){
        type = "SUB";
        num = v;
    }
    else if (t == "*"){
        type = "MUL";
        num = v;
    }
    else if (t == "/"){
        type = "DIV";
        num = v;
    }
    else if (t == "del"){
        type = "DEL";
        num = v;
    }
    else if (t == "ret"){
        type = "RET";
        num = v;
    }
    else if (is_digits1(t)){
        type = "VAL";
        num = stoi(t);
    }
    else{
        type = "VAR";
        id = t;
        num = v;
    }
}

ExprTreeNode::~ExprTreeNode(){
    left=nullptr;
    right=nullptr;
    delete left;
    delete right;
}
