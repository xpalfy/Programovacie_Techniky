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
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node *next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node *first; // adresa prveho uzla zoznamu
};

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zretazeneho zoznamu 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr') a moze
           mat lubovolny pocet uzlov (0 a viac).

    PARAMETRE:
        [in, out] list - adresa zretazeneho zoznamu, do ktoreho ideme pridavat uzol
        [in] val       - hodnota uzla, ktory sa ma pridat na koniec zoznamu 'list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        prazdny zoznam, 5 ---> (5)
        (1), 1 ---> (1,1)
        (8,2,6,6), 14 ---> (8,2,6,6,14)
        (6,100,33), -85 ---> (6,100,33,-85)
        (1,2,3,4,5), 3 ---> (1,2,3,4,5,3)
*/

void append(Node *node,const int val){
    if(node->next== nullptr){
        node->next=new (Node);
        node->next->data=val;
        node->next->next=nullptr;
    }
    else{
        append(node->next,val);
    }
}

void appendNode(List *list, const int val) {
    // TODO
    if (list->first== nullptr){
        list->first= new (Node);
        list->first->data=val;
        list->first->next=nullptr;
    }
    else{
        append(list->first,val);
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam, ktory bude skonstruovany pomocou udajov vo vstupnej
    strukture 'listData'. Struktura 'listData' obsahuje polozku 'data', ktora reprezentuje pole
    hodnot pre jednotlive uzly zoznamu. Struktura 'listData' taktiez obsahuje polozku 'len', ktora
    hovori aku ma dlzku pole 'data'. Vytvoreny zoznam musi obsahovat uzly, ktore zodpovedaju
    svojimi hodnotami a poradim prvkom ulozenym v poli 'data' (dlzka zoznamu bude 'len').
    Funkcia nakoniec vrati adresu takto vytvoreneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'listData' vzdy existuje (t.j. 'listData' je rozny od 'nullptr').
        2) Pre polozku 'len' plati, ze 'len' >= 0 a nikdy nebude mat vacsiu hodnotu ako je
           realny pocet prvkov v poli 'data'.
    VYSTUPNA PODMIENKA:
        1) Ak je polozka 'len' rovna 0, vtedy sa vytvori a vrati prazdny zretazeny zoznam
           (t.j. platny zoznam, ktory ma 0 uzlov).

    PARAMETRE:
        [in] listData - struktura, pomocou ktorej sa vytvori zoznam

    NAVRATOVA HODNOTA:
        Adresa zretazeneho zoznamu, ktory bol vytvoreny pomocou struktury 'listData'.
        Vid pokyny vyssie.

    PRIKLADY:
        polozka 'data' = (1,2,3)
        polozka 'len' = 0
        vystupny zoznam bude mat 0 uzlov, t.j. ()

        polozka 'data' = (1,2,3)
        polozka 'len' = 2
        vystupny zoznam bude (1,2)

        polozka 'data' = (1,2,3)
        polozka 'len' = 3
        vystupny zoznam bude (1,2,3)

        polozka 'data' = (-9,412,64,72,100,100,6)
        polozka 'len' = 4
        vystupny zoznam bude (-9,412,64,72)
*/

List *createList(const ListData *listData) {
    // TODO
    if (listData== nullptr){
        return nullptr;
    }
    if(listData->len<0){
        return nullptr;
    }
    else{
        List *list=new List;
        list->first = nullptr;
        for (size_t j=0;j<listData->len;j++){
            appendNode(list,listData->data[j]);
        }
        return list;
    }
    ; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' do vzostupne zotriedeneho zoznamu 'sortedList'.
    Pridanie musi prebehnut takym sposobom, aby bol zoznam 'sortedList' po pridani noveho uzla
    stale vzostupne zotriedeny.

    POZNAMKA: Na poradi duplikatov v zozname 'sortedList' nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'sortedList' vzdy existuje (t.j. 'sortedList' je rozny od 'nullptr').
        2) Vstupny zoznam 'sortedList' moze mat lubovolny pocet uzlov (0 a viac).
        3) Vstupny zoznam 'sortedList' je vzostupne zotriedeny.

    PARAMETRE:
        [in, out] sortedList   - adresa vstupneho zretazeneho zoznamu, ktory je zotriedeny
                                 vzostupne (z angl. ascending)
        [in] val               - hodnota uzla, ktory sa ma pridat do zoznamu 'sortedList'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        (), 0 ---> (0}
        (), 156 ---> (156)
        (8), 4 ---> (4,8)
        (7), 10 ---> (7,10)
        (55), 55 ---> (55,55) ... poznamka: na poradi duplikatov nezalezi
        (1,8,236,888), 70 ---> (1,8,70,236,888)
        (5,5,14,82,82,100), 5 ---> (5,5,5,14,82,82,100)
*/
void insert(Node *node,int val){
    size_t tmp;
    if(node->data>=val){
        tmp=node->data;
        node->data=val;
        val=tmp;
        if(node->next== nullptr) {
            append(node, val);
        }
        else{
            insert(node->next,val);
        }
    }
    else{
        if(node->next== nullptr){
            append(node,val);
        }
        else{
            insert(node->next,val);
        }
    }
}
void insertNode(List *sortedList, const int val) {
    // TODO
    if(sortedList!=nullptr){
        if(sortedList->first== nullptr){
            appendNode(sortedList,val);
        }
        else{
            insert(sortedList->first,val);
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zoznam spojenim zoznamov 'list1' a 'list2'. Funkcia vrati adresu
    novo vytvoreneho zoznamu. V spojenom zozname idu najprv uzly zoznamu 'list1' (v nezmenenom poradi)
    a potom nasleduju uzly zoznamu 'list2' (v nezmenenom poradi). Pri vytvarani noveho zoznamu mozete
    pouzit hlboku alebo plytku kopiu existujucich uzlov (obe riesenia budu akceptovane).

    POZNAMKA:
        Prazdny zoznam je taky zoznam, ktory je platny, ale obsahuje 0 uzlov
        (t.j. polozka 'first' je nastavena na 'nullptr').

    VSTUPNE PODMIENKY:
        1) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).

    PARAMETRE:
        [in, out] list1 - adresa prveho zoznamu
        [in, out] list2 - adresa druheho zoznamu

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol spojenim zoznamov 'list1' a 'list2'.

    PRIKLADY:
        () + () ---> ()
        (5,9) + () ---> (5,9)
        () + (2,2,2) ---> (2,2,2)
        (1) + (2) ---> (1,2)
        (7) + (3,9,16) ---> (7,3,9,16)
        (50,-47,23,1) + (0,0,9,-8) ---> (50,-47,23,1,0,0,9,-8)
*/

List *joinLists(List *list1, List *list2) {
    // TODO
    if(list1== nullptr || list2== nullptr){
        return nullptr;
    }
    if (list1->first==nullptr) {
        if(list2->first== nullptr){
            List *jointlist=new(List);
            jointlist->first= new Node;
            jointlist->first= nullptr;
            return jointlist;
        }
        else{
            List *jointlist=new(List);
            jointlist->first= nullptr;
            Node *p2=list2->first;
            while(1==1){
                appendNode(jointlist,p2->data);
                if(p2->next==nullptr){
                    break;
                }
                else{
                    p2=p2->next;
                }
            }
            return jointlist;
        }
    }
    else if(list2->first==nullptr){
        List *jointlist=new(List);
        jointlist->first= nullptr;
        Node *p1=list1->first;
        while(1==1){
            appendNode(jointlist,p1->data);
            if(p1->next==nullptr){
                break;
            }
            else{
                p1=p1->next;
            }
        }
        return jointlist;
    }
    else{
        List *jointlist=new(List);
        jointlist->first= nullptr;
        Node *p1=list1->first;
        Node *p2=list2->first;
        while(1==1){
            appendNode(jointlist,p1->data);
            if(p1->next==nullptr){
                break;
            }
            else{
                p1=p1->next;
            }
        }
        while(1==1){
            appendNode(jointlist,p2->data);
            if(p2->next==nullptr){
                break;
            }
            else{
                p2=p2->next;
            }
        }
        return jointlist;
    }
     // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani posledny uzol zo zoznamu 'list'. Ak je zoznam 'list' prazdny, funkcia nic
    nevykona. Pamat uzla, ktory funkcia vymaze musi byt korektne dealokovana.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in, out] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        () ---> ()
        (1) ---> ()
        (1,2) ---> (1)
        (1,2,3) ---> (1,2)
*/
void remove(Node *node){
    if(node->next->next==nullptr){
        delete node->next;
        node->next=nullptr;
    }
    else{
        remove(node->next);
    }
}
void removeLastNode(List *list) {
    // TODO
    if(list!=nullptr){
        if(list->first!=nullptr){
            if(list->first->next==nullptr){
                delete list->first;
                list->first=nullptr;
            }
            else{
                remove(list->first);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci je vstupny zoznam 'list' palindrom. Prazdny zoznam budeme povazovat za
    palindrom.

    Poznamka: Palindrom predstavuje taku postupnost hodnot, ktora sa cita rovnako v oboch smeroch.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Priklad palindromu: 1212121 alebo 4953594

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci vstupny zoznam je/nie je palindrom.

    PRIKLADY:
        () ---> true
        (1) ---> true
        (2,2,2,2) ---> true
        (1,2,3,4,5) ---> false
        (1,2,2,1) ---> true
        (8,4,8,4,8) ---> true
        (9,842,613,2,613,842,9) ---> true
        (7,9,1,2) ---> false
        (0,0,0,7,0,0) ---> false
*/

bool isPalindrome(const List *list) {
    // TODO
    if(list==nullptr || list->first==nullptr || list->first->next==nullptr){
        return true;
    }
    Node *p=list->first;
    size_t n=0,i=0;
    while(1==1){
        if(p->next==nullptr){
            n++;
            break;
        }
        else{
            n++;
            p=p->next;
        }
    }
    int data[n];
    p=list->first;
    while(1==1) {
        if (p->next == nullptr) {
            data[i] = p->data;
            i++;
            break;
        }
        else {
            data[i] = p->data;
            p = p->next;
            i++;
        }
    }
    //cout<<data[i-1];
    size_t k=0;
    for (size_t j=i-1;j>0;j--){
        cout<<data[j];
        cout<<data[k]<<std::endl;
        if(data[k]!=data[j]){
            return false;
        }
        k++;
    }
    return true; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati sucet hodnot prvych 'n' uzlov v zozname 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).
        3) Parameter 'n' nebude zaporny a nebude mat nikdy vyssiu hodnotu ako je realny pocet
           uzlov v zozname.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] n - pocet uzlov od zaciatku zoznamu 'list', ktorych sucet sa vrati

    NAVRATOVA HODNOTA:
        Sucet hodnot prvych 'n' uzlov zoznamu 'list'. Ak 'n'=0, vtedy funkcia vrati hodnotu 0.

    PRIKLADY:
        (), 0 ---> 0
        (1,2,3), 0 ---> 0
        (6), 1 ---> 6
        (5,6,7), 2 ---> 11
        (4,4,4,4,4,4), 6 ---> 24
        (-8,41,-314,21), 3 ---> -281
*/

int sumNodes(const List *list, const size_t n) {
    // TODO
    if(n==0){
        return 0;
    }
    if(list!=nullptr && list->first!=nullptr && n>=0){
        int sucet=0;
        Node *p=list->first;
        for (size_t i=0;i<n;i++){
            sucet+=p->data;
            p=p->next;
        }
        return sucet;

    }
    return -1;
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci zoznam 'list1' obsahuje vsetky hodnoty uzlov zoznamu 'list2'.
    Na poradi nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list1' a 'list2' vzdy existuju (t.j. su rozne od 'nullptr').
        2) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).
        3) Zoznam 'list2' nebude obsahovat duplicitne uzly.

    PARAMETRE:
        [in] list1 - prvy zoznam
        [in] list2 - druhy zoznam

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci zoznam 'list1' obsahuje/neobsahuje
        vsetky hodnoty uzlov zoznamu 'list2'.

    PRIKLADY:
        (), () ---> true
        (), (1,2,3) ---> false
        (1,2,3), () ---> true
        (5,6,7), (5,6,8) ---> false
        (8,4,3), (3,8,4) ---> true
        (7,6,1,9,8), (1,6,8) ---> true
        (3,3,3,3,3), (2,3) ---> false
        (8,6,1,2,5,0,7,7), (7) ---> true
        (9,5,10), (41,10,5) ---> false
*/

bool contains(const List *list1, const List *list2) {
    // TODO
    if (list1!=nullptr && list2!=nullptr){
        if (list1->first==nullptr && list2->first==nullptr){
            return true;
        }
        else if(list1->first==nullptr && list2->first!=nullptr){
            return false;
        }
        else if(list2->first==nullptr && list1->first!=nullptr){
            return true;
        }
        else{
            Node *p=list2->first;
            size_t n=0;
            while(1==1){
                n++;
                if(p->next==nullptr){
                    break;
                }
                else{
                    p=p->next;
                }
            }
            int data[n];
            p=list2->first;
            n=0;
            while(1==1){
                if(p->next==nullptr){
                    data[n]=p->data;
                    n++;
                    break;
                }
                else{
                    data[n]=p->data;
                    n++;
                    p=p->next;
                }
            }
            for(size_t i=0;i<n;i++){
                p=list1->first;
                while(1==1){
                    if(p->next==nullptr){
                        if(data[i]==p->data){
                            break;
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        if(data[i]==p->data){
                            break;
                        }
                        p=p->next;
                    }
                }
            }
            return true;
        }
    }
    return false; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati HLBOKU kopiu zoznamu 'list'. Vo vytvorenej kopii musia byt zachovane
    hodnoty a poradie uzlov z povodneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa zoznamu, ktoreho hlboku kopiu treba vytvorit

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol ako hlboka kopia vstupneho zoznamu 'list'. Kopiou
        prazdneho zoznamu je prazdny zoznam.

    PRIKLADY:
        Vstup = ()
        Vystup = ()

        Vstup = (1,2,3)
        Vystup = (1,2,3)
        Poznamka: adresy uzlov na rovnakych poziciach v oboch zoznamoch sa musia lisit
        (pretoze je to hlboka kopia)
*/

List *deepCopyList(const List *list) {
    // TODO
    if (list== nullptr ){
        return nullptr;
    }
    List *copy=new List;
    copy->first=new Node;
    if(list->first==nullptr){
        copy->first=nullptr;
        return copy;
    }
    else{
        Node *p=list->first;
        size_t n=0,i=0;
        while(1==1){
            if(p->next==nullptr){
                n++;
                break;
            }
            else{
                n++;
                p=p->next;
            }
        }
        int data[n];
        p=list->first;
        while(1==1) {
            if (p->next == nullptr) {
                data[i] = p->data;
                i++;
                break;
            }
            else {
                data[i] = p->data;
                p = p->next;
                i++;
            }
        }
        copy->first->data=data[0];
        copy->first->next=nullptr;
        for(size_t j=1;j<n;j++){
            append(copy->first,data[j]);
        }
        return copy;
    }
    // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde posledny vyskyt uzla s hodnotou 'val' v zozname 'list' a vrati jeho adresu.
    Ak sa v zozname 'list' takyto uzol nenachadza, funkcia vrati 'nullptr'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hladana hodnota uzla

    NAVRATOVA HODNOTA:
        Adresa posledneho vyskytu uzla s hodnotou 'val' v zozname 'list'.

    PRIKLADY (treba otestovat pomocou debuggera):
        (), 2 ---> nullptr
        (5,4,3,2), 1 ---> nullptr
        (-5,4,-9,66), 4 ---> adresa 2. uzla
        (1,1,1,5,6,41), 1 ---> adresa 3. uzla
        (8,6,7,3,2,6), 6 ---> adresa 6. uzla
*/

Node *findLastNodeOccurrence(const List *list, const int val) {
    // TODO
    if(list==nullptr){
        return nullptr;
    }
    if(list->first==nullptr){
        return nullptr;
    }
    Node *p=list->first;
    Node *pointer=nullptr;
    while(1==1){
        if(p->next==nullptr){
            if(p->data==val){
                pointer=p;
            }
            if (pointer== nullptr){
                return nullptr;
            }
            else{
                return pointer;
            }
        }
        else{
            if(p->data==val){
                pointer=p;
            }
            p=p->next;
        }
    }
    return nullptr; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    // tu mozete doplnit testovaci kod
    return 0;
}
