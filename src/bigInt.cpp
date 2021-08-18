#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class bigInt{
private:
    vector<int> v;
    bool sign = true;
public:
    bigInt(int m){
        if(m<0){
            sign = false;
            m*=-1;
        }
        string l = to_string(m);
        for(char& c: l){
            v.push_back(((int)c)-48);
        }
        reverse(v.begin(), v.end());
    }
    bigInt(string m){
        if(m[0] == '-'){
            sign = false;
            m = m.substr(1,m.size()-1);
        }
        for(char& c: m){
            v.push_back(((int)c)-48);
        }
        reverse(v.begin(), v.end());
    }
    void operator=(string m)
    {
        if(m[0] == '-'){
            sign = false;
            m = m.substr(2,m.size()-1);
        }
        else{
            sign = true;
        }
        for(char& c: m){
            v.push_back(((int)c)-48);
        }
        reverse(v.begin(), v.end());
    }
    void operator=(int m)
    {
        if(m<0){
            sign = false;
            m*=-1;
        }
        else{
            sign = true;
        }
        string l = to_string(m);
        for(char& c: l){
            v.push_back(((int)c)-48);
        }
        reverse(v.begin(), v.end());
    }
    bigInt operator+(bigInt m){ //Only for two pos bigInt
        bigInt l = *this;
        for(int i =0; i<(m.v.size()<l.v.size() ? m.v.size() : l.v.size()); i++){
            l.v[i]+=m.v[i];
        }
        for(int i =l.v.size(); i<m.v.size(); i++){
            l.v.push_back(m.v[i]);
        }
        for(int i =0; i<l.v.size(); i++){
            if((i==l.v.size()-1)&&l.v[i]/10!=0){
                l.v.push_back(0);
                l.v[i+1]+=l.v[i]/10;
                l.v[i] %=10;
                break;
            }
            l.v[i+1]+=l.v[i]/10;
            l.v[i] %=10;
        }
        return l;
    }
    bigInt operator+(int m){ //(+) + (+) & (-) + (-)
        bigInt l = *this;
        if(sign ? (m<0) : (m>0)){
            return l-(m*-1);
        }
        l.v[0]+=abs(m);
        for(int i =0; i<l.v.size(); i++){
            if((i==l.v.size()-1)&&l.v[i]/10!=0){
                l.v.push_back(0);
                l.v[i+1]+=l.v[i]/10;
                l.v[i] %=10;
                break;
            }
            l.v[i+1]+=l.v[i]/10;
            l.v[i] %=10;
        }
        return l;
    }
    bigInt operator-(int m){ //(+) - (+) & (-) - (-)
        bigInt l = *this;
        if(sign ? (m<0) : (m>0)){
            return l+(m*-1);
        }
        l.v[0]-=abs(m);
        for(int i =0; i<l.v.size(); i++){
            if((i==l.v.size()-1)){
                if(l.v[i]<0){
                    l.sign = !l.sign;
                    for(int j =0; j<l.v.size(); j++) l.v[j]*=-1;
                    for(int k =0; k<l.v.size(); k++){
                        if((k==l.v.size()-1)&&l.v[k]/10!=0){
                            l.v.push_back(0);
                            l.v[k+1]+=l.v[k]/10;
                            l.v[k] %=10;
                            break;
                        }
                        if(l.v[k]>=0) break;
                        l.v[k+1]-=(((l.v[k]+1)/10)-1)*-1;
                        l.v[k]+=(((l.v[k]+1)/10)-1)*-10;
                    }
                    break;
                }
                else{
                    l.v.push_back(0);
                    l.v[i+1]+=l.v[i]/10;
                    l.v[i] %=10;
                    break;
                }
            }
            if(l.v[i]>=0) break;
            l.v[i+1]-=(((l.v[i]+1)/10)-1)*-1;
            l.v[i]+=(((l.v[i]+1)/10)-1)*-10;
        }
        return l;
    }
    bigInt operator*(int n){
        bigInt l = *this;
        l.sign = n<0 ? !sign : sign;
        for(auto it = l.v.begin(); it != l.v.end(); it++) *it *=n;
        for(int j=0; j<l.v.size(); j++){
            if(l.v[j] <10) continue;
            if(j+1 == l.v.size()) l.v.push_back(0);
            l.v[j+1] += l.v[j]/10;
            l.v[j] %=10;
        }
        return l;
    }
    /*
    bigInt operator/(int n){
        bigInt l = *this;
        l.sign = n<0 ? !sign : sign;
        bigInt quotient = bigInt(0);
        while(true){
            
        }
        return l;
    }
     */
    void show(){
        if(!sign) cout<<'-';
        bool first_zeros=v[v.size()-1]==0;
        for(int it= v.size()-1; it>-1; it-- ){
            if(first_zeros){
                if(v[it] == 0) continue;
                else first_zeros=false;
            }
            cout<<v[it];
        }
    }
};
