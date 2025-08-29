#include <iostream>
#include <string>

using namespace std;

int naive(string key, string text){
    int k=0;
    int p = 0;
    string a = text.substr(0, key.length());

    for(int i=key.length(); i<text.length(); i++){
        //cout<<a<<endl;

        if(key == a){
            return i-key.length();
        }

        a.push_back(text[i]);
        a.erase(0,1);
    }

    return -1;
}  

int main(){

    cout<<naive("ipsum", "Lorem ipsum dolor sit amet")<<endl;

    return 0;
}