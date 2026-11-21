#include <iostream>
#include <fstream>
using namespace std;

int main () {
    ifstream file("simple.txt", ios::binary);

    if (!file) {
        cout<<"error opening file"<<endl;
        return 1 ;
    }

    char byte ;
    int count = 0 ;

    while (file.get(byte)) {
        cout<<"Byte Value:"<< static_cast<unsigned char>(static_cast<unsigned char>(byte))<<endl;
        count++;
    }
    cout<<"total bytes:"<<count<<endl;
    file.close();
    return 0 ;
}