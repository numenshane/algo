#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

typedef struct btreeNode{
    btreeNode* left;
    btreeNode* right;
    int val;
} BtreeNode;

void preOrder(BtreeNode* root){

    if (root == NULL) return;
    cout << root->val << endl;
    preOrder(root->left);
    preOrder(root->right);
}
void postOrder(BtreeNode* root){

    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << endl;
}
void midOrder(BtreeNode* root){

    if (root == NULL) return;
    midOrder(root->left);
    cout << root->val << endl;
    midOrder(root->right);
}

void insertNode(BtreeNode* &root, BtreeNode* node)
{
    assert(node != NULL);
    if (root==NULL) { 
        root = node; 
        return;
    }
    if (root->val < node->val)
        return insertNode(root->right, node);
    else if (root->val == node->val){
        cout << "existed node, will free this node with value:" << node->val << endl;
        free(node);
        return;
    }
    else
        return insertNode(root->left, node);
}

BtreeNode* mallocNode(int val)
{
    BtreeNode* node = (BtreeNode*)malloc(sizeof(BtreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeBtree(BtreeNode* root)
{
    if (root == NULL) return;
    freeBtree(root->left);
    freeBtree(root->right);
    //freeBtree(root);
    free(root);
}

int main() {
    unsigned int len;
    int val;
    BtreeNode* root = NULL;
    cout << "please input tree len" << endl;
    cin >> len;
    for (int i =0; i < len; i++){
        cout << "please input tree node index:" << i << "'s value:" << endl;
        cin >> val;
        BtreeNode* node = mallocNode(val);
        if (i == 0) 
            root = node;
        else
            insertNode(root, node);
    }
    
    cout << "preOrder:" << endl;
    preOrder(root);
    
    cout << "postOrder" << endl;
    postOrder(root);
    
    cout << "midOrder" << endl;
    midOrder(root);
    
    freeBtree(root);
    
}
