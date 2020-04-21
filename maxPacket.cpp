#include <iostream>
#include <assert.h>
using namespace std;

int maxStone(unsigned int num, int* wArr, int* vArr, int packetWeight){
    if(packetWeight <= 0) return 0;
    
    int maxPacketValue;
    
    //init int* Map[num]
    int** vMap = (int**)malloc(sizeof(int*)*(packetWeight+1));
    for (int i=0; i<=packetWeight; i++)
    {
        vMap[i]=(int*)malloc(sizeof(int)*num);
    }
    cout << "enter loop for counting vMap" << endl;
    for (int i=0; i<=packetWeight; i++){
        for(int j=0; j<num; j++){
            if(i==0){
                vMap[i][j] = 0;
                continue;
            }
            if(j==0){
                if (wArr[j]>i){
                    vMap[i][j]=0;
                    cout << "packetWeight:" << i << " and stone num:" << j << " valueMap is " << vMap[i][j] <<endl;
                }
                else{
                    vMap[i][j]=vArr[j];
                    cout << "packetWeight:" << i << " and stone num:" << j << " valueMap is " << vMap[i][j] <<endl;
                }
            }
            else{
                if(wArr[j] < i){
                    int w = i - wArr[j];
                    int v = vMap[w][j-1] + vArr[j];
                    vMap[i][j]=v>vMap[i][j-1]?v:vMap[i][j-1];
                    cout << "packetWeight:" << i << " and stone num:" << j << " valueMap is " << vMap[i][j] <<endl;
                }
                else{
                    vMap[i][j]=vMap[i][j-1];
                    cout << "packetWeight:" << i << " and stone num:" << j << " valueMap is " << vMap[i][j] <<endl;
                }
            }
        }
    }
    maxPacketValue = vMap[packetWeight][num-1];
    //release int** Map
    for(int i=0; i<packetWeight; i++){
        free(vMap[i]);
    }
    free(vMap);
    return maxPacketValue;
}
int main() {
    unsigned int num;
    cout << "please input how many stone" << endl;
    cin >> num;
    int* wArr = (int*)malloc(sizeof(int)*num);
    int* vArr = (int*)malloc(sizeof(int)*num);
    cout << "please input each stone's weight and value" << endl;
    for (int i=0; i < num; i++){
        cout << "input stone:" << i << "'s weight and value" << endl;
        cin >> wArr[i];
        cin >> vArr[i];
    }
    int packetWeight;
    cout << "please input your packet max weight" << endl;
    cin >> packetWeight;
    int max = maxStone(num, wArr, vArr, packetWeight);
    cout << "max value is:" << max << endl;
    
    free(wArr);
    free(vArr);
}
