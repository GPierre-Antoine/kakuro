//
// Created by Pierre-Antoine Guillaume on 13/05/2018.
//

#include <limits>
#include "Case.h"


bool Case::is_black() const {
    return this->coul == Couleur::NOIRE;
}

bool Case::is_white() const {
    return !this->is_black();
}

Case::Case() :
        coul(Couleur::NOIRE),
        num(std::numeric_limits<std::size_t>::max()),
        somme_horizontale(std::numeric_limits<std::size_t>::max()),
        somme_verticale(std::numeric_limits<std::size_t>::max()) {
}