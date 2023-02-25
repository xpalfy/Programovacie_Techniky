/*
Meno a priezvisko:Vincent Pálfy

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void insertionSort(int *data, const size_t length) {
    // TODO
    int current,j;
    for (size_t i=1;i<length;i++){
        current=data[i];
        j=i-1;
        while(j>=0 && data[j]<current){
            data[j+1]=data[j];
            j=j-1;
        }
        data[j+1]=current;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    // TODO
    if (data[0]== nullptr){
        return;
    }
    char* current;
    int j;
    size_t i=1;
    while (data[i]!= nullptr){
        current=(char*)data[i];
        j=i-1;
        while(j>=0 && strcmp(data[j],current)<0){
            data[j+1]=data[j];
            j=j-1;
        }
        data[j+1]=current;
        i=i+1;
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/

Node* findPredecessor(const List* list, Node* node){
    Node* tmp = list->first;
    Node* pred;
    while(tmp){
        if(tmp->next == node){
            pred=tmp;
            return pred;
        }
        tmp=tmp->next;
    }
    return nullptr;
}

void insertionSort(List * list) {
    // TODO
    if(list== nullptr || list->first== nullptr){
        return;
    }
    int j,i=1;
    Node* current=list->first->next;
    Node* pred;
    Node* prev;
    Node* next;
    while(current){
        j=i-1;
        pred=findPredecessor(list,current);
        int currentVal=current->data;
        while(j>=0 && pred->data<currentVal){
            prev=findPredecessor(list,pred);
            next=current->next;
            if(prev){
                prev->next=current;
            }
            else{
                list->first=current;
            }
            current->next=pred;
            if(next){
                pred->next=next;
            }
            else{
                pred->next= nullptr;
            }
            j=j-1;
            pred=findPredecessor(list,current);
            if(pred==nullptr){
                break;
            }
        }
        i++;
        current=current->next;
    }
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni.
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    // TODO
    int array_1 [middle - low];
    int array_2 [high - middle];
    for (size_t i=0;i<(middle-low);i++){
        array_1[i]=input[low+i];
    }
    for (size_t j=0;j<(high - middle);j++){
        array_2[j]=input[middle+j];
    }
    size_t i=0,j=0,k=low;
    while(i < (middle-low) && j < (high - middle)){
        if(array_1[i]>=array_2[j]){
            output[k]=array_1[i];
            i++;
        }
        else{
            output[k]=array_2[j];
            j++;
        }
        k++;
    }
    while(i<(middle-low)){
        output[k]=array_1[i];
        i++;
        k++;
    }
    while(j < (high - middle)){
        output[k]=array_2[j];
        j++;
        k++;
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
// void mergeSort(int *arrayA, int *arrayB, const size_t low, const size_t high) { // Priklad deklaracie rekurzivnej funkcie, v pripade pristupu top-down
// }



int min(int x, int y) {
    if(x<y){
        return x;
    }
    else{
        return y;
    }
};

void merge(int* data, int*tmp , int low, int middle, int high, const size_t length)
{
    int i=low, j=middle+1, k=low;
    while (i <= middle && j <= high)
    {
        if (data[i] > data[j]){
            tmp[k++] = data[i++];
        }
        else{
            tmp[k++] = data[j++];
        }
    }
    while ((size_t)i<length && i<=middle)
    {
        tmp[k++] = data[i++];
    }
    for (i = low; i <= high; i++) {
        data[i] = tmp[i];
    }
}

void mergeSort(int *data, const size_t length) {
    // TODO
    if(length==0){
        return;
    }
    int* tmp=new int[length];
    for(size_t i=0;i<length;i++){
        tmp[i]=data[i];
    }
    for (size_t i=1; i<=(length-1); i = 2*i)
    {
        for (size_t j=0; j<(length-1); j += 2*i)
        {
            int mid = j + i - 1;
            int right_end = min(j + 2*i - 1, (length-1));
            merge(data,tmp, j, mid, right_end,length);
        }
    }
    for (size_t i=0;i<length;i++){
        data[i]=tmp[i];
    }
    delete [] tmp;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {
    return 0;
}
