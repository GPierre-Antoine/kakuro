//
// Created by Pierre-Antoine Guillaume on 13/05/2018.
//

#ifndef KAKURO_CASE_H
#define KAKURO_CASE_H

#include "Couleur.h"

class Case {
public:
    enum Couleur coul;      /* la nature de la case */
    int num;                /* le numero de la case s'il s'agit d'une case noire */
    int somme_horizontale;  /* la valeur de la somme horizontale le cas écheant, -1 sinon */
    int somme_verticale;    /* la valeur de la somme verticale le cas écheant, -1 sinon */
};


#endif //KAKURO_CASE_H
