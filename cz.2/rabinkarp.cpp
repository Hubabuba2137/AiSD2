#include <iostream>

//algorytm Rabina-Karpa

#define m 5 //długość wzorca
#define max 17 //długość całego klucza

using namespace std;

int hashing(int tab[m]) {
   int sum = 0;
   for (int i = 0; i < m; i++) {
       sum = sum *10 + tab[i];
   }

   return sum%13;
}

bool naive(int tab1[m], int tab2[m]) {
   int k = 0;
   for (int i = 0; i < m; i++) {
       if (tab1[i] == tab2[i]){
           k++;
       }
   }

   if (k == m) {
       return true;
   }
   else {
       return false;
   }
}


int rabin(int wz[m], int tab[max]) {
   int temp[m];
   int hashed=0;
   int h_wz = hashing(wz);

   int temp2[m];

   for (int i = 0; i < max; i++) {
       for (int j = 0; j < m; j++) {
           temp[j] = tab[i+j];
       }
       hashed = hashing(temp);

       if (hashed == h_wz && naive(wz,temp)) {
           return i;
       }
   }

   return -1;
}

void wzor(int wz[m], int tab[max]){
    int i = rabin(wz, tab);

    if(i != -1){
        cout<< i+1<<", ";
    }
    else{
        cout<<"Nie znaleziono wzorca"<<"\n";
    }
}

int main()
{
   int wzorzec[m] = { 3,1,4,1,5 };
   int tekst[max] = { 2,3,5,9,0,2,3,1,4,1,5,2,6,7,3,9,9 };

   wzor(wzorzec, tekst);

   return 0;
}