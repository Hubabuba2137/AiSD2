#include <iostream>
#include <string>
#include <vector>
using namespace std;

int compare(string a, string b, int n) {
    if (a.substr(0, n) == b.substr(b.size() - n, n)) {
        return n;
    } else {
        return 0;
    }
}

int gen_state_mach(string a, string b) {
    int max_match = 0; 
    
    for (int n = 0; n < min(a.size(), b.size()); n++) {
        int match_length = compare(a, b, n);
        if (match_length > 0) {
            max_match = max(max_match, match_length);
        }
    }
    return max_match;
}

bool naive(string a, string b){
    if(a == b){
        return true;
    }
    else{
        return false;
    }
}

string pre(string word, int n){
    return word.substr(0,n);
}

string suf(string word, int n){
    return word.substr(word.length()-n, n);
}

int* pre_suf_tab(string key){
    int* ptab = new int[key.length()];
    for(int i=0; i<key.length();i++){
        ptab[i] = 0;
    }

    string temp_word;
    for(int i=0; i<key.length();i++){
        temp_word.push_back(key[i]);
        cout<<temp_word<<"\n";
        ptab[i] = gen_state_mach(pre(temp_word, i), suf(temp_word, i));
        cout << ptab[i]<<"\n";
    }
    
    return ptab;
}

vector<int> kmp(string key, string tekst){
    vector<int> roz;
    int txt_len = tekst.length();
    int key_len = key.length();
    
    int* ptab = pre_suf_tab(key);

    int i = 0;
    int j = 0;

    while(i<txt_len){
        if(tekst[i]==key[j]){
            i++;
            j++;

            if(j == key_len){
                //cout<<i-j<<", ";
                roz.push_back(i-j);
                j = ptab[j-1];
            }
        }

        else{
            if(j != 0){
                j = ptab[j-1];
            }
            else{
                i++;
            }
        }
    }

    return roz;
}


int main() {
    string key = "ababababca";
    string tekst = "bacbababaababababababca";
    //string key = "dolor";
    //string tekst = "lorem ipsum dolor sit amet dolor";

    vector<int> roz = kmp(key, tekst);

    for(int i: roz){
        cout<<i<<", ";
    }

    return 0;
}