#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
plik graf.txt ma wyglądać tak:

8
0 5 0 4 0 0 0 0
5 0 0 0 0 0 0 3
0 0 0 0 7 8 1 7
4 0 0 0 0 20 0 14
0 0 7 0 0 3 2 0
0 0 8 20 3 0 0 0
0 0 1 0 2 0 0 7
0 3 7 14 0 0 7 0

int M[8][8] = {	{0, 5, 0, 4, 0, 0, 0, 0},
				{5, 0, 0, 0, 0, 0, 0, 3},
				{0, 0, 0, 0, 7, 8, 1, 7},
				{4, 0, 0, 0, 0, 20, 0, 14},
				{0, 0, 7, 0, 0, 3, 2, 0},
				{0, 0, 8, 20, 3, 0, 0, 0},
				{0, 0, 1, 0, 2, 0, 0, 7},
				{0, 3, 7, 14, 0, 0, 7, 0}};

*/

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

List_Edge krus(List_Edge LE, int size){
	List_Edge LER;

	//inicjujemy i wypełniamy zerami tablice
	int* tab_kol = new int[size];
	int* tab_las = new int[size];
	int i_las = 0; //iterator lasu

	for(int i=0; i<size; i++){
		tab_las[i] = 0;
		tab_kol[i] = 0;
	}

	//zaczynamy od pierwszego elementu listy krawędzi
	node_2* current = LE.head;

	while(current != nullptr){
		int current_from = current->from-1;
		int current_next = current->next_num-1;

		i_las++;
		//dwa białe
		if(tab_kol[current_from] == 0 && tab_kol[current_next] == 0){
			//kolorujemy oba
			tab_kol[current_from] = 1;
			tab_kol[current_next] = 1;

			//zalesiamy oba
			tab_las[current_from] = i_las;
			tab_las[current_next] = i_las;
			LER.add(current_from, current_next, current->len);
			//cout<< current_from<<", "<<current_next<<", "<<current->len<<"\n";
		}

		//jedno białe, jedno szare
		else if(tab_kol[current_from] == 1 && tab_kol[current_next] == 0){
			tab_kol[current_next] = 1;
			tab_las[current_next] = tab_las[current_from];

			LER.add(current_from, current_next, current->len);
			//cout<< current_from<<", "<<current_next<<", "<<current->len<<"\n";
		}
		else if(tab_kol[current_from] == 0 && tab_kol[current_next] == 1){
			tab_kol[current_from] = 1;
			tab_las[current_from] = tab_las[current_next];

			LER.add(current_from, current_next, current->len);
			//cout<< current_from<<", "<<current_next<<", "<<current->len<<"\n";
		}

		//dwa szare
		else if(tab_kol[current_from] == 1 && tab_kol[current_next] == 1){

			//złączenie lasów
			if(tab_las[current_from] != tab_las[current_next]){
				int iter_1 = tab_las[current_from];
				int iter_2 = tab_las[current_next];

				for(int i=0; i<size; i++){
					if(tab_las[i] == iter_1 || tab_las[i] == iter_2){
						tab_las[i] = i_las;
					}
				}
				LER.add(current_from, current_next, current->len);
			}

			//ten sam las - nic nie robimy, idziemy do kolejnego node'a
		}
		current = current->next;
	}
	delete tab_kol;
	delete tab_las;
	return LER;
}

int main()
{
	//---------------------Przygotowanie listy krawędzi----------------------------//
	int size = 0;

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
	cout<<"LE:\n";
	LE.show();

	//---------------------Przygotowanie listy krawędzi----------------------------//

	cout<<"\nMinimalne drzewo rozpinające: \n";
	List_Edge LER = krus(LE, size);
	LER.show();

	return 0;
}
