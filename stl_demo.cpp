#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
void showStack(stack<int> s)
{
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}
int main() {
    // stl stack push/pop top
    stack<int> s;
    s.push(10);
    s.push(12);
    showStack(s);
    cout << s.size() << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;

    // queue support push/pop front/back
    queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.pop();
    cout << "queue front:" << queue.front() << endl;
    cout << "queue end:" << queue.back() << endl;
    
    // list support push_back push_front pop_back pop_front
    list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(3);
    list.pop_back();
    std::list<int>::iterator iter = std::find(list.begin(), list.end(), 2);
    if(iter != list.end())
        cout << "find val:" << *iter << endl;
    cout << "print list element on by one!!!" << endl;
    for (std::list<int>::iterator iter = list.begin(); iter != list.end(); iter++)
    {
        cout << "elements:" << *iter << endl;
    }
    
    // stl vector support push_back pop_back insert
    vector<int> vect = {1,2,3,4,5};
    vect.insert(vect.begin()+2,100);
    unsigned index=0;
    for(std::vector<int>::iterator iter = vect.begin(); iter != vect.end(); iter++)
        cout << "elements:" << index++ << " value is " << *iter << endl;
    vect.push_back(6);
    std::vector<int>::iterator ite = std::find(vect.begin(), vect.end(), 100);
    if (ite != vect.end()) 
        cout << "suc find element:" << *ite << endl;
    vect.erase(vect.begin(), vect.begin()+3);
    for(int i=0; i < vect.size(); i++)
    {
        cout << "elememt:" << i << " value is " << vect[i] << endl;
    }
}
