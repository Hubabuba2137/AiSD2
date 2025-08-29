#include <iostream>

using namespace std;

constexpr int SIZE = 13; //wielkość tablicy hashowania

int hashing(string name) {
   int sum = 0;
   int temp = 0;

   for (char c : name) {
       temp = int(c);
       sum += temp;
   }

   return sum % 13;
}

struct node {
   string name;

   node* next = nullptr;

   node() {}
   node(string n) : name(n) {}
};

struct tab {
   node* tab_vec[SIZE] = {nullptr};

   void add(string name) {
       int place = hashing(name);
       node* head = new node(name);

       if (tab_vec[place] == nullptr) {
           tab_vec[place] = head;
           tab_vec[place]->next = nullptr;
       }

       else if (tab_vec[place] != nullptr){
        int i = 1;
            node* temp = tab_vec[place];
            while(temp->next!=nullptr){
                temp = temp->next;
                i++;
            }

            temp->next = head;
       }
   }

   void find(string name){
        int place = hashing(name);

        cout << "Pozycja: " <<name<<" to " << place << ": ";
        node* current = tab_vec[place];
        while (current != nullptr) {
            cout << current->name << " -> ";
            current = current->next;
        }
        cout << "nullptr\n";
   }

   void del(string name){
        int place = hashing(name);
        node* current = tab_vec[place];
        node* previous = nullptr;

        if (current == nullptr) {
            cout << "Element " << name << " nie istnieje.\n";
            return;
        }

        while (current != nullptr && current->name != name) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Element " << name << " nie istnieje.\n";
            return;
        }

        if (previous == nullptr) {
            tab_vec[place] = current->next; 
        } else {
            previous->next = current->next; 
        }

        delete current;  
   }

   void print(){
        for (int i = 0; i < SIZE; ++i) {
            cout << "Index " << i << ": ";
            node* current = tab_vec[i];
            while (current != nullptr) {
                cout << current->name << " -> ";
                current = current->next;
            }
            cout << "nullptr\n";
        }
   }
};

int main()
{
   string imiona[10] = { "Ola", "Gerwazy", "Piotr", "Gosia","Pola", "Asia", "Alfred", "Gabrysia", "Stefan", "Jacek"};

   tab tabela;

   for (string it : imiona) {
       tabela.add(it);
   }

    tabela.print();
    tabela.del("Jacek");
    tabela.del("Gosia");
    cout<<"\n";
    tabela.print();

    cout<<"\n";
    tabela.find("Pola");

   return 0;
}