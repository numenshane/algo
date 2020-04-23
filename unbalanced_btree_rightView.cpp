#include <iostream>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>

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
    
    free(root);
}

int* rightSideView1(BtreeNode* root, int* returnSize) {
    if (!root) return NULL;
    // use BFS ,first push, loop until empty, get each loop's last element's val
    queue<int> valQ;
    queue<BtreeNode*> nodeQ;
    nodeQ.push(root);
    while(!nodeQ.empty()){
        int total = nodeQ.size();
        for(int i=0; i< total; i++){
            BtreeNode* node = nodeQ.front();
            nodeQ.pop();
            cout << "total is " << total << endl;
            if(node->left) nodeQ.push(node->left);
            if(node->right) nodeQ.push(node->right);
            if(i == total-1){
                (*returnSize)++;
                valQ.push(node->val);
            }
        }
    }
    cout << "returnSize is " << *returnSize << endl; 
    int* arr = (int*)malloc(sizeof(int)*(*returnSize));
    for(int j=0; j<*returnSize; j++){
        arr[j] = valQ.front();
        valQ.pop();
    }
    return arr;
}

void preOrder(BtreeNode* root, int layer, int* pMaxLayer, queue<int> &q){
    if (!root) return;
    if(layer > (*pMaxLayer)){
        q.push(root->val);
        (*pMaxLayer)++;
    }
    preOrder(root->right, layer+1, pMaxLayer, q);
    preOrder(root->left, layer+1, pMaxLayer, q);
}

int* rightSideView2(BtreeNode* root, int* returnSize) {
    if (!root) return NULL;
    // use DFS
    *returnSize = 0;
    queue<int> q;
    int maxLayer = 0;
    preOrder(root, 1, &maxLayer, q);
    *returnSize = q.size();
    int *arr = (int*)malloc(sizeof(int)*(*returnSize));
    for(int i = 0; i<(*returnSize); i++){
        arr[i] = q.front();
        q.pop();
    }
    return arr;
    return NULL;
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
    
    // rightSideView using BFS
    int returnSize = 0;
    int* arr = rightSideView1(root, &returnSize);
    cout << "BFS rightSideView of Btree:" << endl;
    for(int i=0; i< returnSize; i++){
        cout << arr[i] << endl;
    }
    free(arr);
    
    arr = rightSideView2(root, &returnSize);
    cout << "DFS rightSideView of Btree:" << endl;
    for(int i=0; i< returnSize; i++){
        cout << arr[i] << endl;
    }
    free(arr);
    
    // rightSideView using DFS
    freeBtree(root);
    
}
