#include <iostream>

#include "src/parser.h"

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Utilisation: " << argv[0] << " fichier" << endl;
        exit(EXIT_FAILURE);
    }

    parser p{};

    try {
        p.parse(argv[1]);
    }
    catch (std::runtime_error &error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
