#include <iostream>

using namespace std;

struct wez {
    wez* left;
    wez* right;
    wez* up;
    wez* ojciec;
    int val;
};

struct drzew {
    wez* root;

    drzew() {
        root = nullptr;
    }

    void add(wez*& temp, int x, wez* p = nullptr) {
        if (temp == nullptr) {
            temp = new wez;
            temp->val = x;
            temp->left = nullptr;
            temp->right = nullptr;
            temp->ojciec = p;
        }
        else {
            if (x >= temp->val) {  // w prawo
                add(temp->right, x, temp);
            }
            else {  // w lewo
                add(temp->left, x, temp);
            }
        }
    }
    
    wez* find(wez* temp, int num) {
        int x = num;

        if (temp != nullptr) {
            if (x == temp->val) {
                return temp;
            }
            else if (x > temp->val) {
                return find(temp->right, x);
            }
            else {
                return find(temp->left, x);
            }
        }
        else {
            return nullptr;
        }
    }

    int min(wez* temp) {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp->val;
    }

    wez* min_wsk(wez* temp){
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    int max(wez* temp) {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp->val;
    }

    wez* max_wsk(wez* temp) {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }

    void print_inorder(wez* root) {
        if (root != nullptr) {
            print_inorder(root->left);
            cout << root->val << "\n";
            print_inorder(root->right);
        }
    }
    
    void del_leaf(wez*& root) {
        if (root != nullptr) {
            if(root->left !=nullptr){
                if(root->left->left == nullptr && root->left->right ==nullptr){
                    delete root->left;
                    root->left = nullptr;
                }
                else{
                    del_leaf(root->left);
                }
            }

            if(root->right != nullptr){
                if(root->right->left == nullptr && root->right->right == nullptr){
                    delete root->right;
                    root->right = nullptr;
                }
                else{
                    del_leaf(root->right);
                }
            }
        }
        else{
            return;
        }
    }

    //jeżeli funckje popr i nast nie znajdą nic to zwracają nullptr.
    wez* popr(wez* temp) {
        wez* temp_ojciec = temp->ojciec;
        if (temp->left != nullptr) {
            return this->max_wsk(temp->left);  
        } 
        else {
            while (temp_ojciec != nullptr && temp == temp_ojciec->left) { 
                temp = temp_ojciec;
                temp_ojciec = temp->ojciec;
            }
            return temp_ojciec; 
        }
    }

    wez* nast(wez* temp) {
        wez* temp_ojciec = temp->ojciec;
        if (temp->right != nullptr) {
            return this->min_wsk(temp->right);  
        } 
        else {
            while (temp_ojciec != nullptr && temp == temp_ojciec->right) { 
                temp = temp_ojciec;
                temp_ojciec = temp->ojciec;
            }
            return temp_ojciec; 
        }
    }

    void del(wez*& temp) {

        if (temp->left == nullptr && temp->right == nullptr) {//liść
            delete temp;
            temp = nullptr;
        } 

        else if (temp->left != nullptr && temp->right == nullptr) {

            if (temp->ojciec->left == temp){
                temp->ojciec->left = temp->left;
            }

            else{
                temp->ojciec->right = temp->left;
            }

            temp->left->ojciec = temp->ojciec;
            delete temp;
            temp = nullptr;
        } 

        else if (temp->right != nullptr && temp->left == nullptr) {

            if (temp->ojciec->right == temp){
                temp->ojciec->right = temp->right;
            }
            else{
                temp->ojciec->left = temp->right;
            }

            temp->right->ojciec = temp->ojciec;
            delete temp;
            temp = nullptr;
        } 
        else {
            wez* nastepnik = this->nast(temp);
            temp->val = nastepnik->val;
            del(nastepnik);
        }
    }
};

int main()
{
    drzew bst;

    int tab[10] = {12,6,-5,11,3,8,22,16,10,27};

    for (int i = 0; i < 10; i++) {
        bst.add(bst.root, tab[i]);
    }

    bst.print_inorder(bst.root);
    cout<<endl;

    wez* temp = bst.find(bst.root, 6);
    bst.del(temp);
    bst.print_inorder(bst.root);
    
    return 0;
}