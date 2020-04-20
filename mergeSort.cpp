#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

void shift(int len, int arr[], int pos)
{
    int maxChild;
    int value;
    while(pos < len) 
    {
        int lchild = 2*pos + 1;
        int rchild = 2*pos + 2;
        value = arr[pos];
        
        if (lchild >= len) 
            break;
        if (rchild == len) 
        {
            maxChild=lchild;
        }
        else
        {
            if (arr[lchild] >= arr [rchild])
                maxChild = lchild;
            else
                maxChild = rchild;
        }
        if (arr[pos] < arr[maxChild])
        {
            arr[pos] = arr[maxChild];
            pos = maxChild;
            arr[pos] = value;
        }
        else
            break;
    }
}

void swap (int arr[], int x, int y)
{
    int val = arr[x];
    arr[x] = arr[y];
    arr[y] = val;
}

void heapSort(int len, int arr[])
{
    if(len <= 1) return;
    int i = len/2;
    for (; i >= 0 ; i--)
    {
        shift(len, arr, i);
    }
    for (i=0; i < len-1; i++)
    {
        swap(arr, 0, len-1-i);
        shift(len-1-i, arr, 0);
    }
}

void printArr(int len, int arr[])
{
    cout << "print arr" << endl;
    for (int i=0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}
struct ListNode{
    int val;
    struct ListNode *next;
};

int searchList(struct ListNode** lists, int listsSize, int val)
{
    for (int i=0; i < listsSize; i++)
    {
        if (lists[i] != NULL && lists[i]->val == val)
            return i;
    }
    return -1;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    ListNode* head = NULL;
    ListNode* tail;
    assert(listsSize > 0);
    int searchLen = listsSize;
    if (listsSize == 1) return lists[0];
    // create dynamic int arr
    int *arr = (int*)malloc(sizeof(int)*listsSize);
    int *ptr = arr;
    for (int i=0; i < listsSize; i++)
    {
        arr[i]=lists[i]->val;
    }
    // heapSort arr
    heapSort(listsSize, arr);
    printArr(listsSize, arr);
    while(true)
    {
        // pop smallest:  arr[0]
        // find listNode[x][0] which contains arr[0], output listNode[X][0]
        int index = searchList(lists, searchLen, arr[0]);
        assert( index != -1);
        
        if (head == NULL)
        {
            head = lists[index]; // init head
            tail = head;
        }
        else
        {
            tail->next = lists[index]; // append to tail
            tail = tail->next;
        }
        
        lists[index] = lists[index]->next;
        if (lists[index] == NULL)
        {
            // truncate arr and lists with 1, heapSort arr
            heapSort(--listsSize, ++arr);
            if(listsSize == 1)
            {
                index = searchList(lists, searchLen, arr[0]);
                assert(index != -1);
                tail->next = lists[index];
                break;
            }
        }
        else
        {
            arr[0] = lists[index]->val;
            heapSort(listsSize, arr);
        }
        printArr(listsSize, arr);
    }
    free(ptr);
    return head;
}

void iterList(ListNode* l)
{
    while(l != NULL)
    {
        cout << l->val << endl;
        l = l->next;
    }
}
void freeList(ListNode* l)
{
    ListNode* next;
    while(l != NULL)
    {
        next = l->next;
        free(l);
        l = next;
    }
}

int main() {
    int arr[] = {12,342,545,656,5757,76,78,344,32,342,4989775,342,234,324,324};
    int len = (int)sizeof(arr)/sizeof(*arr);
    heapSort(len, arr);
    printArr(len, arr);
    while (true)
    {
        unsigned int listsSize;
        cout << "please input listsSize:" << endl;
        cin >> listsSize;
        ListNode** lists = (ListNode**)malloc(sizeof(ListNode*)*listsSize);
        for(int i=0; i < listsSize; i++)
        {
            lists[i] = NULL;
        }
        for(int i=0; i < listsSize; i++)
        {
            unsigned int len;
            cout << "\t please input lists index:" << i << "'s list length" << endl;
            cin >> len;
            
            ListNode* prev;
            for (int j=0; j < len; j++)
            {
                ListNode* next = (ListNode*)malloc(sizeof(ListNode));
                int val;
                cout << "\t\t please input element " << j <<"'s value:" << endl;
                cin >> val;
                
                next->val = val;
                next->next = NULL;
                
                if (lists[i] == NULL)
                {
                    lists[i] = next;
                    prev = next;
                }
                else
                {
                    prev->next = next;
                    prev = prev->next;
                }
            }
        }
        ListNode* root = mergeKLists(lists, listsSize);
        iterList(root);
        cout << "cleaning!!!" << endl;
        freeList(root);
        free(lists);
    }
    return 0; 
}
