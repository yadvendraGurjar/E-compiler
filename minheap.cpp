/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    root = NULL;
}

void heapifyUp(HeapNode* node) {
    while (node->par && node->val < node->par->val) {
        swap(node->val, node->par->val);
        node = node->par;
    }
}

void heapifyDown(HeapNode* node) {
    while (true) {
        HeapNode* minNode = node;
        if (node->left && node->left->val < minNode->val) {
            minNode = node->left;
        }
        if (node->right && node->right->val < minNode->val) {
            minNode = node->right;
        }
        if (minNode == node) {
            break;
        }
        swap(node->val, minNode->val);
        node = minNode;
    }
}

int* decToBinary(int n){
    int* arr = new int[32];
    int i = 0;
    while( n > 0 ){
        arr[i+1] = n & 1;
        i++;
        n>>=1;
    }
    arr[0]=i;
    return arr;
}

void MinHeap::push_heap(int num){
    HeapNode* newNode = new HeapNode(num);
    if (!root) {
        root = newNode;
    }
    else{
        HeapNode* lastNode = root;
        int* arr = decToBinary(size + 1);
        for(int i = arr[0]-1 ; i > 1 ; i--){
            if(arr[i] == 1){
                lastNode = lastNode->right;
            }
            else{
                lastNode = lastNode->left;
            }
        }
        if (arr[1] == 1) {
            lastNode->right = newNode;
        }
        else {
            lastNode->left = newNode;
        }
        newNode->par = lastNode;
        heapifyUp(newNode);
    }
    size++;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if (size == 1) {
        delete root;
        root = NULL;
        size = 0;
        return;
    }
    HeapNode* lastNode = root;
    int* arr = decToBinary(size);
    for(int i = arr[0]-1 ; i > 1 ; i--){
        if(arr[i] == 1){
            lastNode = lastNode->right;
        }
        else{
            lastNode = lastNode->left;
        }
    }
    if (arr[1] == 1) {
        root->val = lastNode->right->val;
        delete lastNode->right;
        lastNode->right = NULL;
    }
    else {
        root->val = lastNode->left->val;
        delete lastNode->left;
        lastNode->left = NULL;
    }
    heapifyDown(root);
    size--;
}

void helperdelete(HeapNode* node) {
    if (node) {
        helperdelete(node->left);
        helperdelete(node->right);
        delete node;
    }
}

MinHeap::~MinHeap(){
    helperdelete(root);
    root = NULL;
}