/*
Meno a priezvisko: Vincent Pálfy

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
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
            : value(value)
            , smaller(smaller)
            , greater(greater)
    {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
            : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    // TODO
    Node* uzol=tree->root;
    if(uzol== nullptr){
        throw ValueNotExistsException();
    }
    else{
        while(uzol->smaller){
            uzol=uzol->smaller;
        }
        return uzol->value;
    }
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

unsigned depth(const BinarySearchTree *tree, int value) {
    // TODO
    Node* uzol=tree->root;
    int depth=0;
    if(uzol== nullptr){
        throw ValueNotExistsException();
    }
    while(1==1){
        if(value==uzol->value){
            return depth;
        }
        if(value<uzol->value){
            uzol=uzol->smaller;
        }
        else if(value>uzol->value){
            uzol=uzol->greater;
        }
        if (uzol== nullptr){
            break;
        }
        depth++;
    }
    throw ValueNotExistsException();
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    // TODO
    list <int> array;
    Node* uzol=tree->root;
    while(1==1) {
        if (uzol == nullptr) {
            break;
        }
        if (value == uzol->value) {
            array.push_back(uzol->value);
            break;
        }
        array.push_back(uzol->value);
        if (value < uzol->value) {
            uzol = uzol->smaller;
        }
        else if (value > uzol->value) {
            uzol = uzol->greater;
        }
    }
    return array;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t count(const Node* uzol)noexcept{
    size_t c=1;
    if(uzol== nullptr){
        return 0;
    }
    else{
        c+=count(uzol->smaller);
        c+=count(uzol->greater);
        return c;
    }
}

size_t count(const BinarySearchTree *tree) noexcept {
    // TODO
    Node* uzol=tree->root;
    size_t c=count(uzol);
    return c;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

void all(const Node *uzol, list<int> *array) noexcept {
    if(uzol== nullptr){
        return;
    }
    else{
        all(uzol->smaller,array);
        array->push_back(uzol->value);
        all(uzol->greater,array);
    }
}

list<int> all(const BinarySearchTree *tree) noexcept {
    // TODO
    list<int> array;
    Node* uzol=tree->root;
    if(uzol== nullptr){
        return array;
    }
    else{
        all(uzol,&array);
    }
    return array;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t count(Node* uzol, int value)noexcept{
    if(uzol== nullptr){
        return 0;
    }
    size_t c=0;
    if(uzol->value>value){
        c++;
    }
    if(uzol->value>value){
        c+=count(uzol->smaller,value);
        c+=count(uzol->greater,value);
    }
    else if(uzol->value<=value){
        c+=count(uzol->greater,value);
    }
    return c;
}

size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    // TODO
    Node* uzol=tree->root;
    size_t c=count(uzol,value);
    return c;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/

void clear(const Node* uzol)noexcept{
    if (uzol== nullptr){
        return;
    }
    clear(uzol->smaller);
    clear(uzol->greater);
    delete uzol;
}

void clear(BinarySearchTree *tree) noexcept {
    // TODO
    if(tree->root==nullptr){
        return;
    }
    else{
        clear(tree->root);
        tree->root= nullptr;
    }
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

void search(const vector<int> & data, int value,int l,int r, int* count)noexcept{
    if(r>=l){
        int mid=l+(r-l)/2;
        (*count)++;
        if(data[mid]==value){
            return;
        }
        if(data[mid]>value){
            search(data,value,l,mid-1,count);
        }
        if(data[mid]<value){
            search(data,value,mid+1,r,count);
        }
    }
    return;
}

unsigned contains(const vector<int> & data, int value) noexcept {
    // TODO
    if(data.size()==0){
        return 0;
    }
    int count=0;
    search(data,value,0,data.size()-1,&count);
    return count;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
    // TODO
    map<string, size_t> histogram;
    for(string i: data){
        if(histogram.count(i)==0){
            histogram.insert({i,1});
        }
        else{
            histogram[i]++;
        }
    }
    return histogram;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
    // TODO
    map<string, set<size_t>> histogram;
    int j=0;
    for(string i: data){
        if(histogram.count(i)==0){
            histogram.insert({i,{}});
        }
        histogram[i].insert(j);
        j++;
    }
    return histogram;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {
    // tu mozete doplnit testovaci kod
    return 0;
}
