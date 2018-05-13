//
// Created by Pierre-Antoine Guillaume on 13/05/2018.
//

#ifndef KAKURO_CASE_H
#define KAKURO_CASE_H

#include <cstddef>
#include "Couleur.h"

class Case {
public:
    enum Couleur coul;      /* la nature de la case */
    size_t num;                /* le numero de la case s'il s'agit d'une case noire */
    size_t somme_horizontale;  /* la valeur de la somme horizontale le cas écheant, -1 sinon */
    size_t somme_verticale;    /* la valeur de la somme verticale le cas écheant, -1 sinon */

    bool is_black() const;
    bool is_white() const;

    Case();
};


#endif //KAKURO_CASE_H
