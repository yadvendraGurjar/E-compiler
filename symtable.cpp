/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

int height1(SymNode *N){ 
    if (N == NULL) return -1; 
    return N->height; 
}

int getBalance(SymNode* N){  
    if (N == NULL){
        return 0;
    }
    return height1(N->left) - height1(N->right);
}

SymNode* helperinsert(SymNode* Node,  string k){
    if (Node == NULL) return new SymNode(k);
    if (k < Node->key){
        Node->left = helperinsert(Node->left, k);
    }
    else if(k > Node->key){
        Node->right = helperinsert(Node->right, k);
    }
    else return Node;
    Node->height = 1 + max(height1(Node->left), height1(Node->right));
    int bal = getBalance(Node);
    // Left Left Case  
    if (bal > 1 && k < Node->left->key) return Node->LeftLeftRotation();
    // Right Right Case  
    if (bal < -1 && k > Node->right->key) return Node->RightRightRotation();
    // Left Right Case  
    if (bal > 1 && k > Node->left->key) return Node->LeftRightRotation();
    // Right Left Case  
    if (bal < -1 && k < Node->right->key) return Node->RightLeftRotation();
    return Node;
}

void SymbolTable::insert(string k){
    root = helperinsert(root, k);
    size++;
}

SymNode* minValueNode(SymNode* node){ 
    SymNode* curr = node; 
    while (curr->left != NULL) curr = curr->left;
    return curr; 
}

SymNode* helperdelete(SymNode* root, string k){
    if (root == NULL) return root;
    if ( k < root->key ) root->left = helperdelete(root->left, k);
    else if( k > root->key ) root->right = helperdelete(root->right, k);
    else{
        if(root->left == NULL || root->right == NULL) { 
            SymNode *temp = root->left ? root->left : root->right;
            if (temp == NULL){ 
                temp = root;
                root = NULL;
            } 
            else{
                root->key = temp->key;
                root->address = temp->address;
                root->height = 0;
                delete temp;
                root->right = NULL;
                root->left = NULL;
            }
        } 
        else{
            SymNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->address = temp->address;
            root->right = helperdelete(root->right, temp->key); 
        }
    }
    if (root == NULL) 
    return root;
    root->height = 1 + max(height1(root->left), height1(root->right));
    int balance = getBalance(root);
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) return root->LeftLeftRotation();
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) return root->LeftRightRotation();
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) return root->RightRightRotation();
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) return root->RightLeftRotation();
    return root;
}

void SymbolTable::remove(string k){
    if(search(k) == -2) return;
    root = helperdelete(root, k);
    size--;
}

int SymbolTable::search(string k){
    if (root->key == k){
        return root->address;
    }
    SymNode* temp =  root;
    while(temp != NULL ){
        if(k < temp->key){
            temp = temp->left;
        }
        else if (k > temp->key){
            temp = temp->right;
        }
        else{
            return temp->address;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    if (root->key == k){
        root->address = idx;
        return;
    }
    SymNode* temp =  root;
    while(temp != NULL ){
        if(k < temp->key){
            temp = temp->left;
        }
        else if (k > temp->key){
            temp = temp->right;
        }
        else{
            temp->address = idx;
            return;
        }
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void Delete(SymNode* root){
    if(root == NULL){
        return;
    }
    else if(root->left == NULL && root->right==NULL){
        delete root;
        return;
    }
    else{
        Delete(root->left);
        Delete(root->right);
        delete root;
        return;
    }
}

SymbolTable::~SymbolTable(){
    Delete(root);
}