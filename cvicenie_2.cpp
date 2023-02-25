// Tema: assert, static_assert, struktura, new, delete, sizeof, pretazenie funkcie
// Autor: Vladislav Novak

#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <bit>
#include <climits>
#include <cstring>

using namespace std;

struct Gif {
    char signature[3];
    char version[3];
    uint16_t width;
    uint16_t height;
    // ...
};

static_assert(std::endian::native == std::endian::little); // je pouzity little endian (opacne poradie bajtov) https://en.cppreference.com/w/cpp/types/endian
static_assert(CHAR_BIT == 8); // 1 baj ma 8 bitov https://en.cppreference.com/w/cpp/types/climits

void printLine(const Gif *gif) {
    assert(gif); // gif != nullptr

    cout << "Gif: {signature: " << gif->signature[0] << gif->signature[1] << gif->signature[2]
         << ", version: " << gif->version[0] << gif->version[1] << gif->version[2]
         << ", width: " << gif->width
         << ", height: " << gif->height
         << "}" << endl;
}

Gif* create(const char *fileName) {
    assert(fileName); // fileName != nullptr

    FILE *file = fopen(fileName, "rb");
    if(file == nullptr) {
        return nullptr;
    }

    Gif* image = new Gif;
    size_t readObjects = fread((void*)image, sizeof(Gif), 1, file);
    if(readObjects != 1) {
        delete image;
        return nullptr;
    }

    fclose(file);
    return image;
}

void destroy(Gif **image) {
    assert(image);  // image != nullptr
    assert(*image); // *image != nullptr

    delete *image;
    *image = nullptr;
}

Gif* create(const char *version, uint16_t width, uint16_t height /* dalsie parametre */) {
    const size_t VERSION_LENGTH = 3;

    assert(std::strlen(version) == VERSION_LENGTH);

    Gif *image = new Gif;

    char signature[] = {'G', 'I', 'F'};
    std::memcpy(image->signature, signature, sizeof(signature));
    std::memcpy(image->version, version, VERSION_LENGTH);
    image->width = width;
    image->height = height;

    return image;
}

int main() {
    Gif image1 = {{'G', 'I', 'F'}, { '8', '7', 'a'}, 1280, 720};
    printLine(&image1);

    Gif *image2 = new Gif;
    printLine(image2);
    delete image2;

    // Gif *image3 = nullptr;
    // printLine(image3);

    Gif *image4 = create("dog.gif");
    if(! image4) {
        cerr << "chyba pri citani obrazku" << endl;
        return EXIT_FAILURE;
    }
    printLine(image4);
    destroy(&image4);

    Gif *image5 = create("89a", 100, 200);
    printLine(image5);
    destroy(&image5);

    return EXIT_SUCCESS;
}
