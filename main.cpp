#include <iostream>

#include "src/kakuro_parser.h"

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Utilisation: " << argv[0] << " fichier" << endl;
        exit(EXIT_FAILURE);
    }

    kakuro_parser p{};

    try {
        for (auto it = argv + 1; it < (argv + argc); ++it) {
            p.parse(*it);
        }
    }
    catch (std::runtime_error &error) {
        cerr  << "Error : " << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
