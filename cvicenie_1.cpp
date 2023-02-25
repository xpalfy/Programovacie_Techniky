// Program cita cisla zo standardneho vstupu a ich sucet vypise na standardny vystup.

// Citanie sa ukonci pri chybe konverzie udajov na hodnotu typu 'int',
//             alebo pri chybe citania zo standardneho vstupu, ktora moze byt sposobena napriklad uzavretim standardneho vstupu

#include <iostream>

int main() {

    int current; // aktualne nacitane cislo
    int sum = 0; // suma doteraz nacitanych cisiel

    while(true) {
        std::cout << "zadaj cislo: ";
        std::cin >> current;
        if(std::cin.good()) {
            sum += current;
        }
        else { // std::cin.fail()
            break;
        }
    }

    std::cout << "suma = " << sum <<  std::endl;

    return 0;
}
