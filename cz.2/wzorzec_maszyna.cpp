#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
using namespace std;

int compare_prefix_suffix(string a, string b, int n) {
    if (a.substr(0, n) == b.substr(b.size() - n, n)) {
        return n;
    } else {
        return 0;
    }
}

int gen_state_mach(string a, string b) {
    int max_match = 0;

    for (int n = min(a.size(), b.size()); n > 0; n--) {
        int match_length = compare_prefix_suffix(a, b, n);
        //cout<< match_length<<"\n";
        if (match_length > 0) {
            max_match = max(max_match, match_length);
        }
    }
    return max_match;
}

uint32_t bin_rep_2(const string key) {
    uint32_t temp = 0b00000000000000000000000000000000;
    for (char c : key) {
        temp |= (1 << (c - 'a'));
    }
    return temp;
}

string masking(uint32_t binar) {
    string temp;
    for (int i = 0; i < 26; i++) {
        if (binar & (1 << i)) {
            temp += ('a' + i);
        }
    }
    return temp;
}

int mask_index(string mask, char c) {
    //którym znakiem w masce jest dany znak
    for (int i = 0; i < mask.length(); i++) {
        if (c == mask[i]) {
            return i;
        }
    }
    return -1;
}

vector<int> search(string pat, string text){
    vector<int> res;

    string mask = masking(bin_rep_2(pat));
    int rows = pat.length() + 1;
    int col = mask.length();

    vector<vector<int>> arr(rows, vector<int>(col, 0));

    string key;
    string temp;

    for (int j = 0; j < rows; j++) {
        if (j < pat.length()) {
            key.push_back(pat[j]);
            //cout<<key<<"\n";
        }
        for (int i = 0; i < col; i++) {
            temp.push_back(mask[i]);
            arr[j][i] = gen_state_mach(key, temp);
            temp.pop_back();
        }
        temp = key;
    }

    //wypisanie maski z odstępami
    for(char c: mask){
        cout<<c<<" ";
    }
    cout<<"\n";

    string temp_row = pat;
    temp_row.push_back(' ');

    //wypisanie macierzy stanu maszyny
    for(int i=0; i<rows;i++){
        for(int j =0; j<col;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<< temp_row[i]<<"\n";
    }

    vector<int> tab(text.length() + 1, 0); //tablica stanu maszyny

    for (int i = 1; i <= text.length(); i++) {
        char c = text[i - 1]; //text[0]
        int index = mask_index(mask, c);

        if (index != -1) {
            int index2 = tab[i - 1];
            tab[i] = arr[index2][index];
        }
    }

    for (int i = 0; i <= text.length(); i++) {
        if (tab[i] == pat.length()) {
            int poz = i - pat.length() +1;
            res.push_back(poz);
        }
    }

    return res;
}

int main() {
    string pat = "dolor";
    string text = "lorem ispum dolor sit amet dolor";

    vector<int> res = search(pat, text);

    cout<<"\n";
    for (auto it : res) {
        cout << it << ", ";
    }

    return 0;
}
