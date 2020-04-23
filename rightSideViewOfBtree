/*int height(struct TreeNode*root){
    if(!root)return 0;
    int L = height(root->left);
    int R = height(root->right);
    return fmax(L,R)+1;
} 
void dfs(struct TreeNode* root,int depth,int *returnSize,int*res){数
    if(!root) return;
    if(*returnSize==depth) res[(*returnSize)++]=root->val;
    dfs(root->right,depth+1,returnSize,res);
    dfs(root->left,depth+1,returnSize,res);
}
int* rightSideView(struct TreeNode* root, int* returnSize){
    int H = height(root);
    int*res = (int*)malloc(sizeof(int)*H);
    *returnSize = 0;
    dfs(root,0,returnSize,res);
    return res;        
}*/

/*
int*rightSideView(struct TreeNode* root,int*returnSize) {
    *returnSize=0;
    if(!root) return NULL;
    int*res=(int*)malloc(sizeof(int*)*100);
    struct TreeNode** q=(struct TreeNode**)malloc(sizeof(struct TreeNode*)*1000);
    int front=0,back=-1;
    q[++back]=root; 
	// dynamic arr not override, append at back, pop at front
    while(front!=back+1){
        res[(*returnSize)++]=q[back]->val;
        int size=back-front+1;
        for(int i=0;i<size;++i){
            struct TreeNode*t=q[front++];
            if(t->left) q[++back]=t->left;
            if(t->right) q[++back]=t->right;
        }           
    }
	  free(q);
    return res;
}
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <assert.h>

typedef struct TreeNode TreeNode;
#define QueueInitLen 256
// imp queue push/pop opeartion
typedef struct queue {
    unsigned int total_size;
    unsigned int cur_size;
    int* buffer;
    unsigned int front;
    unsigned int back;
} Queue;

Queue* initQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->total_size = QueueInitLen;
    q->cur_size = 0;
    q->buffer = (int*) malloc(sizeof(int)*QueueInitLen);
    q->front = 0;
    q->back = 0;
    return q;
}

unsigned int sizeofQueue(Queue* q){
    return q->cur_size;
}

bool isEmptyQueue(Queue* q){
    return q->front == q->back? true:false;
}

//one empty left 
bool isFullQueue(Queue* q){
    unsigned int next = (q->front + 1) % QueueInitLen;
    return q->back == next?true:false;
}

void delQueue(Queue* q){
    free(q->buffer);
    free(q);
}

void resizeQueue(Queue* q){
    unsigned int newCapacity = q->total_size + QueueInitLen;
    int* newBuffer = (int*)malloc(sizeof(int)*newCapacity);
    if(q->front > q->back){
        memcpy(newBuffer, &q->buffer[q->back],q->front-q->back);
    }
    else{
        unsigned int part = q->total_size-1-q->back;
        memcpy(newBuffer, &q->buffer[q->back], part);
        memcpy(newBuffer+part, &q->buffer[0], q->front+1);
    }
    free(q->buffer);
    q->buffer = newBuffer;
    q->total_size = newCapacity;
}
bool pushQueue(Queue* q, int val){
    if(isFullQueue(q)){
        resizeQueue(q);
    }
    if(isFullQueue(q)) return false;
    q->buffer[q->front] = val;
    q->front = (q->front + 1) % QueueInitLen;
    q->cur_size++;
    return true;
}

bool popQueue(Queue* q, int* val){
    if (isEmptyQueue(q)) return false;
    *val = q->buffer[q->back];
    q->back = (q->back + 1) % QueueInitLen;
    q->cur_size--;
    return true;
}
 
void preOrder(TreeNode* root, int* cur_layer, int* max_layer, Queue* q){
    if(root == NULL) return;
    (*cur_layer)++;
    if(*cur_layer > *max_layer){
        pushQueue(q, root->val);
        (*max_layer)++;
    }
    preOrder(root->right, cur_layer, max_layer, q);
    preOrder(root->left, cur_layer, max_layer,q);
    (*cur_layer)--;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize){
    if(root == NULL){
        if(returnSize!=NULL) *returnSize = 0;
        return NULL;
    }
    int cur_layer = 0;
    int max_layer = 0;
    Queue* q = initQueue();
    preOrder(root, &cur_layer, &max_layer, q);
    *returnSize = (int)sizeofQueue(q);
    int* arr = (int*) malloc(sizeof(int)*(*returnSize));
    for(int i=0; i< *returnSize; i++){
        assert(popQueue(q, &arr[i]));
    }
    delQueue(q);
    return arr;
}
