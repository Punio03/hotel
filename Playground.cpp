#include "header.hpp"
int main(void){
    vector<Room> vec;
    for(int i = 0;i<100;i++){
        Room temp(i,3,320);
        cout << temp << endl;
    }
    DateTime data1(2003,12,23);
    DateTime data2(2003,12,30);
    cout << data2 - data1;
    return 0;
}