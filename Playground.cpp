#include "header.hpp"
int main(void){
    vector<Room> vec;
    for(int i = 0;i<100;i++){
        Room temp(i,3,320);
        cout << temp << endl;
    }
    return 0;
}