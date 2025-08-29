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

struct  node_2 {
	int from;
	int next_num;
	int len;

	node_2* next = nullptr;
	node_2() {}
	node_2(int fr, int next_number, int length_next) :from(fr), next_num(next_number), len(length_next) {}
};

struct tab_LE {
	int size;
	node_2** tab_vec;

	tab_LE(int s) : size(s) {

		tab_vec = new node_2 * [size];

		for (int i = 0; i < size; i++) {
			tab_vec[i] = nullptr;
		}
	}

	void add(int place, int next_n, int l) {
		node_2* head = new node_2(place, next_n, l);

		if (tab_vec[place] == nullptr) {
			tab_vec[place] = head;
			tab_vec[place]->next = nullptr;
		}

		else if (tab_vec[place] != nullptr) {
			int i = 1;
			node_2* temp = tab_vec[place];
			while (temp->next != nullptr) {
				temp = temp->next;
				i++;
			}

			temp->next = head;
		}
	}

	void show() {
		cout<<"\nLE: "<<"\n";
		for (int i = 0; i < size; i++) {
			cout << i + 1 << ": ";
			node_2* current = tab_vec[i];
			while (current != nullptr) {
				cout << current->from+1 << ", " << current->next_num + 1 << ", " << current->len << " -> ";
				current = current->next;
			}
			cout << "null\n";
		}
	}
};

int main()
{
	int size = 0;
	fstream czytaj;
	czytaj.open("./graf.txt");

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


	cout << "MS: " << "\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << M[i][j] << "	";
		}
		cout << "\n";
	}

	tab LS(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (M[i][j] != 0) {
				LS.add(i, j, M[i][j]);
			}
		}
	}

	LS.show();

	tab_LE LE(size);

	for (int i = 0; i < size; i++) {
		node* temp_le = LS.tab_vec[i];
		
		while (temp_le != nullptr) {
			LE.add(temp_le->next_num, i, temp_le->len);
			temp_le = temp_le->next;
		}
	}

	LE.show();

	return 0;
}
