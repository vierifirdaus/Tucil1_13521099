#include <iostream>
#include <fstream>
using namespace std;
string tempsave;
int main() {
    char s;
    cout<<"Apakah anda ingin menyimpan hasil ke file? (y/n)"<<endl;
    cin>>s;
    
    while(s!='y' && s!='n'){
        cout<<"Input salah, ulangi"<<endl;
        cin>>s;
    }

    if(s=='y'){
        cout<<"Masukkan nama file : ";
        cin>>tempsave;
    }
}