#include <iostream>

using namespace std;

//drzewo AVL

struct wez {
   wez* left;
   wez* right;
   wez* up;
   wez* ojciec;
   int val;
   int bal_fac;
};

struct avl {
   wez* root;

   avl() {
       root = nullptr;
   }

   int get_wys(wez* root){
        if (root == nullptr) {
            return 0;
        }

        return max(get_wys(root->left), get_wys(root->right)) + 1;
   }

    int get_bal(wez* root){
        if (root == nullptr) {
            return 0;
        }

        return (get_wys(root->left) - get_wys(root->right));
   }

    wez* rot_l(wez* node) {
        wez* newRoot = node->right;
        wez* temp = newRoot->left;
        
        newRoot->left = node;
        node->right = temp;

        node->bal_fac = get_bal(node);
        newRoot->bal_fac = get_bal(newRoot);

        return newRoot;
    }

    wez* rot_r(wez* node) {
        wez* newRoot = node->left;
        wez* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->bal_fac = get_bal(node);
        newRoot->bal_fac = get_bal(newRoot);

        return newRoot;
    }

    wez* balanceNode(wez* node) {
        node->bal_fac = get_bal(node);

        if (node->bal_fac > 1) {
            if (get_bal(node->left) < 0) {
                //LR
                node->left = rot_l(node->left);
            }
            return rot_r(node);
        }
        
        if (node->bal_fac < -1) {
            if (get_bal(node->right) > 0) {
                //RL
                node->right = rot_r(node->right);
            }
            return rot_l(node);
        }

        return node;
    }

    void add(wez*& temp, int x, wez* p = nullptr) {
        if (temp == nullptr) {
            temp = new wez;
            temp->val = x;
            temp->left = nullptr;
            temp->right = nullptr;
            temp->ojciec = p;
            temp->bal_fac = 0;
        } else {
            if (x >= temp->val) {
                add(temp->right, x, temp);
            } else {
                add(temp->left, x, temp);
            }

            temp = balanceNode(temp);
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

   wez* min_wsk(wez* temp) {
       while (temp->left != nullptr) {
           temp = temp->left;
       }
       return temp;
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
           cout << root->val<<","<<root->bal_fac << " -> ";
           print_inorder(root->right);
       }
   }

   //jeżeli funckje popr i nast nie znajdą nic to zwracają nullptr.
   wez* popr(wez* temp) {
       wez* temp_ojciec = temp->ojciec;
       if (temp->left != nullptr) {
           return this->max_wsk(temp->left);
       }
       else {
           while (temp_ojciec != nullptr && temp == temp_ojciec->left)
{
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
           while (temp_ojciec != nullptr && temp == temp_ojciec->right)
{
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

           if (temp->ojciec->left == temp) {
               temp->ojciec->left = temp->left;
           }

           else {
               temp->ojciec->right = temp->left;
           }

           temp->left->ojciec = temp->ojciec;
           delete temp;
           temp = nullptr;
       }

       else if (temp->right != nullptr && temp->left == nullptr) {

           if (temp->ojciec->right == temp) {
               temp->ojciec->right = temp->right;
           }
           else {
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

       if(temp!= nullptr){
           temp = balanceNode(temp);
       }
   }

};

int main()
{
   avl tree;

   int tab[10] = {12,16,8,4,-3,6,17,25,30,7};

   for(auto tab : tab){
        tree.add(tree.root, tab);
   }

    tree.print_inorder(tree.root);

    cout<<endl;
    wez* temp = tree.find(tree.root, 30);
    tree.del(temp);
    tree.print_inorder(tree.root);
   
   return 0;
}