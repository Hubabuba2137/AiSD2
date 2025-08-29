#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct  node {
	int next_num;
	int len;

	node* next = nullptr;
	node() {}
	node(int next_number, int length_next) : next_num(next_number), len(length_next) {}
};

struct tab {
	int size;
	node** tab_vec;

	tab(int s) : size(s) {

		tab_vec = new node * [size];

		for (int i = 0; i < size; i++) {
			tab_vec[i] = nullptr;
		}
	}

	void add(int place, int next_n, int l) {
		node* head = new node(next_n, l);

		if (tab_vec[place] == nullptr) {
			tab_vec[place] = head;
			tab_vec[place]->next = nullptr;
		}

		else if (tab_vec[place] != nullptr) {
			int i = 1;
			node* temp = tab_vec[place];
			while (temp->next != nullptr) {
				temp = temp->next;
				i++;
			}

			temp->next = head;
		}
	}

	void show() {
		cout<<"\nLS: "<<"\n";
		for (int i = 0; i < size; i++) {
			cout << i + 1 << ": ";
			node* current = tab_vec[i];
			while (current != nullptr) {
				cout << current->next_num +1<< ", " << current->len << " -> ";
				current = current->next;
			}
			cout << "null\n";
		}
	}
};

struct node_2 {
    int from;
    int next_num;
    int len;

    node_2* next = nullptr;
    node_2() {}
    node_2(int fr, int next_number, int length_next) 
        : from(fr), next_num(next_number), len(length_next), next(nullptr) {}
};

struct List_Edge {
    node_2* head;

    List_Edge() : head(nullptr) {}

	void add(int place, int next_n, int l) {
		if (head == nullptr) {
			head = new node_2(place+1, next_n+1, l);
		} else {
			node_2* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = new node_2(place+1, next_n+1, l);
		}
	}

	void show() {
		node_2* current = head;

		while (current != nullptr) {
			cout << current->from  << ", " << current->next_num<< ", " << current->len << "\n";
			current = current->next;
		}
	}
	
	void sort() {
		if (head == nullptr || head->next == nullptr) {
			return;
		}

		node_2* current = head;

		while (current != nullptr) {
			node_2* minNode = current;
			node_2* temp = current->next;

			while (temp != nullptr) {
				if (temp->len < minNode->len) {
					minNode = temp;
				}
				temp = temp->next;
			}

			if (minNode != current) {
				swap(current->from, minNode->from);
				swap(current->next_num, minNode->next_num);
				swap(current->len, minNode->len);
			}

			current = current->next;
		}
	}
};

List_Edge prim(tab List_s, int size, int s) {
	s = s-1;
    List_Edge LER;

    int* tab_kol = new int[size];
    for(int i = 0; i < size; i++) {
        tab_kol[i] = 0;
    }

    tab_kol[s] = 1;

    for(int i = 0; i < size - 1; i++) {
        int min_len = 1000; //wpisałem tu dużą liczbę
        int from = -1, to = -1;

        for(int j = 0; j < size; j++) {
            if(tab_kol[j] == 1) {
                node* temp = List_s.tab_vec[j];
                while(temp != nullptr) {
                    if(tab_kol[temp->next_num] == 0 && temp->len < min_len) {
                        min_len = temp->len;
                        from = j;
                        to = temp->next_num;
                    }
                    temp = temp->next;
                }
            }
        }

        if(to != -1) {
            tab_kol[to] = 1;
            LER.add(from, to, min_len);
        }
    }

    return LER;
}

int main()
{
	//---------------------Przygotowanie listy krawędzi----------------------------//
	int size = 0;
	/*
	//jak mamy plik graf w txt to odkomentarzowac to
	//i odkomentarzowac następne deklaracje macierzy
	
	fstream czytaj;
	czytaj.open("graf.txt");
	czytaj >> size;

	int** M = new int* [size];

	for (int i = 0; i < size; i++) {
		M[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			czytaj >> M[i][j];
		}
	}
	*/
	size = 8;
	int M[8][8] = {	{0, 5, 0, 4, 0, 0, 0, 0},
					{5, 0, 0, 0, 0, 0, 0, 3},
					{0, 0, 0, 0, 7, 8, 1, 7},
					{4, 0, 0, 0, 0, 20, 0, 14},
					{0, 0, 7, 0, 0, 3, 2, 0},
					{0, 0, 8, 20, 3, 0, 0, 0},
					{0, 0, 1, 0, 2, 0, 0, 7},
					{0, 3, 7, 14, 0, 0, 7, 0}};


	tab LS(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (M[i][j] != 0) {
				LS.add(i, j, M[i][j]);
			}
		}
	}
	//LS.show();
	//cout<<"\n";

	List_Edge LE;
	for(int i =0; i<size; i++){
		node* current = LS.tab_vec[i];
		while(current!=nullptr){
			LE.add(i, current->next_num, current->len);
			current=current->next;
		}
	}

	LE.sort();
	//cout<<"LE:\n";
	//LE.show();

	//---------------------Przygotowanie listy krawędzi----------------------------//

	cout<<"\nMinimalne drzewo rozpinające: \n";

	cout<<"\nPrim: \n";
	List_Edge LE_prim = prim(LS, size, 8);
	LE_prim.show();

	return 0;
}
