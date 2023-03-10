#include <bits/stdc++.h>
#include <string.h>
#include <chrono>
#include <cstdlib>

using namespace std; 
string input[5];
int a[5],b[5],op[5];
bool cek[5];
int res;
char cop[4]={'+','-','*','/'};
string cob[]= {"-","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
string convint[]={"-","1","2","3","4","5","6","7","8","9","10","11","12","13"};
bool adasolusi=false;
int permutation[25][5];
int cnt_permutation;
string solution[10000];
int cnt_solution;
string tempsave;
char ss;

void conv(){
    for(int i=0;i<4;i++){
        if(input[i]>="1" && input[i]<="9" && input[i].length()==1){
            a[i]=(input[i][0]-'0');
        }
        else{
            if(input[i]=="10"){
                a[i]=10;
            }
            else if(input[i]=="J" || input[i]=="11"){
                a[i]=11;
            }
            else if(input[i]=="Q" || input[i]=="12"){
                a[i]=12;
            }
            else if(input[i]=="K" || input[i]=="13"){
                a[i]=13;
            }
            else if(input[i]=="A"){
                a[i]=1;
            }
        }
    }
}

double operation(double a,double b,int op){
    double temp;
    if(op==0){
        temp=a+b;
    }
    else if(op==1){
        temp=a-b;
    }
    else if(op==2){
        temp=a*b;
    }
    else if(op==3){
        temp=double(double(a)/double(b));
    }
    return temp;
}

double f(int i,int j){
    double tempa,tempb,result;
    // (a op b) op (c op d)
    if(i==0){
        tempa=operation(permutation[j][0],permutation[j][1],op[0]);
        tempb=operation(permutation[j][2],permutation[j][3],op[2]);
        result=operation(tempa,tempb,op[1]);
    }
    // (a op b) op c) op d
    else if(i==1){
        tempa=operation(permutation[j][0],permutation[j][1],op[0]);
        tempb=operation(tempa,permutation[j][2],op[1]);
        result=operation(tempb,permutation[j][3],op[2]);
    }
    // (a op (b op c)) op d
    else if(i==2){
        tempa=operation(permutation[j][1],permutation[j][2],op[1]);
        tempb=operation(permutation[j][0],tempa,op[0]);
        result=operation(tempb,permutation[j][3],op[2]);
    }
    // a op ((b op c) op d)
    else if(i==3){
        tempa=operation(permutation[j][1],permutation[j][2],op[1]);
        tempb=operation(tempa,permutation[j][3],op[2]);
        result=operation(permutation[j][0],tempb,op[0]);
    }
    // a op (b op (c op d))
    else if(i==4){
        tempa=operation(permutation[j][2],permutation[j][3],op[2]);
        tempb=operation(permutation[j][1],tempa,op[1]);
        result=operation(permutation[j][0],tempb,op[0]);
    }
    return result;
}

void print_solutin(int a,int idx){
    if(a==0){
        solution[cnt_solution]="(" + convint[permutation[idx][0]] + " " + cop[op[0]] + " " + convint[permutation[idx][1]] + ") " + cop[op[1]] + " (" + convint[permutation[idx][2]] + " " + cop[op[2]] + " " + convint[permutation[idx][3]]+ ")";
    }
    else if(a==1){
        solution[cnt_solution]="((" + convint[permutation[idx][0]] + " " + cop[op[0]] + " " + convint[permutation[idx][1]] + ") " + cop[op[1]] + " " + convint[permutation[idx][2]] + ") " + cop[op[2]] + " " + convint[permutation[idx][3]];
    }
    else if(a==2){
        solution[cnt_solution]="(" + convint[permutation[idx][0]] + " " + cop[op[0]] + " (" + convint[permutation[idx][1]] + " " + cop[op[1]] + " " + convint[permutation[idx][2]] + ")) " + cop[op[2]] + " " + convint[permutation[idx][3]];
    }
    else if(a==3){
        solution[cnt_solution]=convint[permutation[idx][0]] + " " + cop[op[0]] + " ((" + convint[permutation[idx][1]] + " " + cop[op[1]] + " " + convint[permutation[idx][2]]+ ") " + cop[op[2]] + " " + convint[permutation[idx][3]] + ")";
    }
    else if(a==4){
        solution[cnt_solution]=convint[permutation[idx][0]] + " " + cop[op[0]] + " (" + convint[permutation[idx][1]] + " " + cop[op[1]] + " (" + convint[permutation[idx][2]]+ " " + cop[op[2]] + " " + convint[permutation[idx][3]]+ "))";
    }
    cnt_solution++;
}

bool cek_in(){
    bool cek=true;
    for(int i=0;i<cnt_permutation;i++){
        if(permutation[i][0]==b[0] && permutation[i][1]==b[1] && permutation[i][2]==b[2] && permutation[i][3]==b[3]){
            return false;
            cek=false;
            break;
        }
    }
    return cek;
}

void per_number(int first,int last){
    if(first==last){
        if(cek_in()){
            permutation[cnt_permutation][0]=b[0];
            permutation[cnt_permutation][1]=b[1];
            permutation[cnt_permutation][2]=b[2];
            permutation[cnt_permutation][3]=b[3];
            cnt_permutation++;
        }
    }
    else {
        for(int i=0;i<4;i++){
            if(cek[i]==false){
                b[first]=a[i];
                cek[i]=true;
                per_number(first+1,last);
                cek[i]=false;
            }
        }
    }
}

void cek_24(){
    for(int j=0;j<cnt_permutation;j++){
        for(int i=0;i<5;i++){
            if(f(i,j)-24>-0.00000000001 && f(i,j)-24<0.00000000001){
                // cout<<f(i,j)<<endl;
                if(adasolusi==false){
                    cout<<"Berikut adalah solusi dari permainan kartu 24"<<endl;
                }
                adasolusi=true;
                res++;
                print_solutin(i,j);
            }
        }
    }
    
}

void per_op(int first,int last){
    if(first==last){
        cek_24();
    }
    else{
        for(int i=0;i<4;i++){
            op[first]=i;
            per_op(first+1,last);
        }
    }
}

bool cekinp(string s){
    if(s=="2"||s=="3"||s=="4"||s=="5"||s=="6"||s=="7"||s=="8"||s=="9"||s=="10"||s=="J"||s=="Q"||s=="K"||s=="A" || s=="11"||s=="12"||s=="13"||s=="1"){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    // mempercepat input output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input angka
    bool cekinput;
    cekinput=true;
    int random;
    cout<<"Masukkan input random atau manual? "<<endl;
    cout<<"1 untuk random"<<endl<<"2 untuk manual"<<endl;
    cin>>random;
    
    while(random!=1 && random!=2){
        cout<<"Input salah, ulangi"<<endl;
        cin>>random;
    }
    if(random==1){
        srand(time(0));
        for(int i=0;i<4;i++){
            input[i]=cob[rand()%13+1];
        }
        cout<<"input berupa"<<endl;
        cout<<input[0]<<" "<<input[1]<<" "<<input[2]<<" "<<input[3]<<endl;
    }
    else if(random==2){
        while(cekinput){
            cout<<"Masukan input berupa 4 angka"<<endl;
            cin>>input[0]>>input[1]>>input[2]>>input[3];
            for(int i=0;i<4;i++){
                if(cekinp(input[i])){
                    cekinput=false;
                }
                else{
                    cout<<"Input salah, ulangi"<<endl;
                    cekinput=true;
                    break;
                }
            }
        }
    }
    

    // kode utama
    auto awal = std::chrono::high_resolution_clock::now();
    conv();
    per_number(0,4);
    per_op(0,3);
    if(adasolusi==false){
        cout<<"Tidak ada solusi"<<endl;
    }
    else{
        cout<<"Jumlah solusi : "<<res<<endl;
    }

    for(int i=0;i<cnt_solution;i++){
        cout<<solution[i]<<endl;
    }
    auto akhir = std::chrono::high_resolution_clock::now();
    
    cout<<endl<<"Apakah anda ingin menyimpan hasil ke file? (y/n)"<<endl;
    cin>>ss;
    
    while(ss!='y' && ss!='n'){
        cout<<"Input salah, ulangi"<<endl;
        cin>>ss;
    }

    if(ss=='y'){
        cout<<endl<<"Masukkan nama file : "<<endl;
        cin>>tempsave;
    }
    auto awalsave = std::chrono::high_resolution_clock::now();
    if(ss=='y'){
        if(cnt_solution==0){
            ofstream MyFile("../test/"+tempsave+".txt");
            MyFile << "Tidak ada solusi"<<endl;
            MyFile.close();
        }
        else{
            ofstream MyFile("../test/"+tempsave+".txt");
            MyFile<<"Berikut adalah solusi dari permainan kartu 24 dengan input"<<endl;
            MyFile<<input[0]<<" "<<input[1]<<" "<<input[2]<<" "<<input[3]<<endl<<endl;
            MyFile<<"Jumlah solusi : "<<cnt_solution<<endl;
            for(int i=0;i<cnt_solution;i++){
                MyFile << solution[i]<<endl;
            }
            MyFile.close();
        }
    }
    auto akhirsave = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(akhir - awal+akhirsave-awalsave);   
    cout<<"Waktu eksekusi selama: "<<elapsed.count() * 1e-6<<" milidetik."<<endl;
    
    return 0;
}  
//g++ code.cpp -o code

