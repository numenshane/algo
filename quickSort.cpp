#include <iostream>
#include <algorithm>
using namespace std;

void quickSort(unsigned int len, int arr[])
{
    if(len <= 1) return;
    unsigned int pos = 0;
    int val = arr[pos];
    int beg = pos;
    int end = len-1;
    
    while(beg < end)
    {
        while(beg < end && val <= arr[end]) end--;
        if(end == beg) break;
        arr[pos] = arr[end];
        pos = end;
        while(end > beg && val >= arr[beg]) beg++;
        if(end == beg) break;
        arr[pos] = arr[beg];
        pos = beg;
    }
    if(pos != 0) arr[pos] = val;
    quickSort(pos, arr);
    quickSort(len-pos-1, arr+pos+1);
}

void printArr(unsigned int len, int arr[])
{
    cout << "print arr of elements:" << len << endl;
    for(int i=0; i<len; i++)
    {
        cout<<arr[i]<<endl;
    }
}

int main() {
    int arr[]= {23,45,2,54,88,1,234134,2,3,4,5,6,4};
    unsigned int len = sizeof(arr)/sizeof(*arr);
    quickSort(len, arr);
    printArr(len, arr);
}
