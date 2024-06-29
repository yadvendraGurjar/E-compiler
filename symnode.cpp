/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

int height(SymNode *N){ 
    if (N == NULL) return -1; 
    return N->height; 
}

SymNode* Rightrot(SymNode* y){
    // cout<<"right roteted";
    SymNode *x = y->left; 
    SymNode *T2 = x->right; 
    x->right = y; 
    y->left = T2;  
    y->height = max(height(y->left), height(y->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

SymNode* Leftrot(SymNode* x){
    // cout<<"left roteted";
    SymNode *y = x->right;
    SymNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

SymNode* SymNode::LeftLeftRotation(){
    return Rightrot(this);
}

SymNode* SymNode::RightRightRotation(){
    return Leftrot(this);
}

SymNode* SymNode::LeftRightRotation(){
    this->left = Leftrot(this->left);
    return Rightrot(this);
}

SymNode* SymNode::RightLeftRotation(){
    this->right = Rightrot(this->right);
    return Leftrot(this);
}

SymNode::~SymNode(){
    par=NULL;
    left=NULL;
    right=NULL;
    delete par;
    delete left;
    delete right;
}