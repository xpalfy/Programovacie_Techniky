/*
 * Meno: Vincent Pálfy
 */

#include <iostream>

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Spravnost kontrolnej sumy
enum class CheckSum {
    OK,       // kontrolna suma je dobra
    ERROR,    // kontrolna suma je chybna
    NOT_EXISTS // kontrolna suma nie je definovana
};

//-------------------------------------------------------------------------------------------------
// ULOHA
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci posledny prvok pola obsahuje sucet vsetkych predchadzajucich prvkov (kontrolny sucet (angl.: check sum)).

    PARAMETRE:
        [in] data   - testovane pole
        [in] length - pocet prvkov pola 'data'

    NAVRATOVA HODNOTA:
        CheckSum::OK - ak posledny prvok 'data' obsahuje sucet vsetkych predchadzajucich prvkov
        CheckSum::ERROR - ak posledny prvok 'data' neobsahuje sucet vsetkych predchadzajucich prvkov
        ChcekSum::NOT_EXISTS - ak 'data' neobsahuje ziadne prvky
*/
CheckSum checkCheckSum(const int *data, size_t length) {
    if(length == 0) {
        return CheckSum::NOT_EXISTS;
    }

    int sum = 0;
    for(size_t i = 0; i < length-1; ++i) {
        sum += data[i];
    }

    return sum == data[length-1] ? CheckSum::OK : CheckSum::ERROR;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury pre testovanie

int main() {
    // tu mozete doplnit testovaci kod

    std::cout << "---------- test vypisu true a false --------------------------------------------" << std::endl;
    std::cout << true  << std::endl;
    std::cout << false << std::endl;

    std::cout << "---------- test checkCheckSum --------------------------------------------------" << std::endl;
    int data1[] = {1, 2, 3, 4, 10}; // pre zrychlenie testovania zadajte hodnoty v kode (nie v konzole)
    std::cout << (checkCheckSum(data1, 5) == CheckSum::OK)         << std::endl;
    std::cout << (checkCheckSum(data1, 4) == CheckSum::ERROR)      << std::endl;
    std::cout << (checkCheckSum(data1, 1) == CheckSum::ERROR)      << std::endl;
    std::cout << (checkCheckSum(data1, 0) == CheckSum::NOT_EXISTS) << std::endl;

    return 0;
}
