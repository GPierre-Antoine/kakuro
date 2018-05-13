
#include <iostream>
#include <stdexcept>
#include <fstream>

#include "parser.h"
#include "Couleur.h"
#include "Case.h"

using std::cerr;
using std::cout;
using std::endl;

void parser::parse(char *nom_fichier) {
    std::ifstream filestream;

    char c;            /* le caractère courant */
    int nb_lignes;    /* le nombre de lignes de la grille */
    int nb_colonnes;  /* le nombre de colonnes de la grille */
    int num_ligne;    /* le numero de la ligne courante */
    int num_colonne;  /* le numero de la colonne courante */
    int nb_variables; /* le nombre de variables déjà trouvées */
    int somme;        /* une somme */

    Case **grille;   /* la grille de jeu */
    int *portee;     /* la portee d'une contrainte */
    int arite;        /* l'arité d'une contrainte */
    int i, j;          /* des compteurs de boucle */

    filestream.open(nom_fichier, std::ifstream::in);

    if (!filestream.is_open()) {
        throw std::runtime_error(std::string("Fichier ") + nom_fichier + " non trouve");
    }

    /* on calcule la taille de la grille */

    nb_lignes = 0;
    nb_colonnes = 0;
    filestream.get(c);

    while (!filestream.eof()) {
        if (c == '\n')
            nb_lignes++;
        else if ((nb_lignes == 0) && ((c == '.') || (c == '\\')))
            nb_colonnes++;
        filestream.get(c);
    }

    cout << "Taille : " << nb_lignes << " x " << nb_colonnes << endl;

    /* remplissage de la grille */

    grille = (Case **) malloc(sizeof(Case *) * nb_lignes);
    for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++) {
        grille[num_ligne] = (Case *) malloc(sizeof(Case) * nb_colonnes);
    }

    filestream.clear();
    filestream.seekg(0, std::ios::beg);

    num_ligne = 0;
    num_colonne = 0;
    nb_variables = 0;

    filestream.get(c);

    while (!filestream.eof()) {
        if (c == '\n') {
            num_ligne++;
            num_colonne = 0;
        } else if (c == ' ')
        {
            num_colonne++;
        }
        else if (c == '.')     /* case blanche */
        {
            grille[num_ligne][num_colonne].coul = BLANCHE;
            grille[num_ligne][num_colonne].num = nb_variables;
            grille[num_ligne][num_colonne].somme_horizontale = -1;
            grille[num_ligne][num_colonne].somme_verticale = -1;

            Variable(nb_variables);

            nb_variables++;
        } else if (c == '\\')    /* case noire de la forme \y ou \ */
        {
            grille[num_ligne][num_colonne].coul = NOIRE;
            grille[num_ligne][num_colonne].num = -1;
            grille[num_ligne][num_colonne].somme_verticale = -1;

            filestream.get(c);

            if (isdigit(c))    /* case noire de la forme \y */
            {
                filestream.putback(c);
                filestream >> somme;
                grille[num_ligne][num_colonne].somme_horizontale = somme;
            } else  /* case noire de la forme \ */
            {
                grille[num_ligne][num_colonne].somme_horizontale = -1;

                filestream.putback(c);
            }
        } else if (isdigit(c))    /* case noire de la forme x\ ou x\y */
        {
            grille[num_ligne][num_colonne].coul = NOIRE;
            grille[num_ligne][num_colonne].num = -1;

            filestream.putback(c);
            filestream >> somme;
            grille[num_ligne][num_colonne].somme_verticale = somme;

            filestream.get(c);   /* on lit le caractère \ */
            filestream.get(c);

            if (isdigit(c))  /* case noire de la forme x\y */
            {
                filestream.putback(c);
                filestream >> somme;
                grille[num_ligne][num_colonne].somme_horizontale = somme;
            } else   /* case noire de la forme x\ */
            {
                grille[num_ligne][num_colonne].somme_horizontale = -1;
                filestream.putback(c);
            }
        }
        filestream.get(c);
    }
    filestream.close();

    cout << "Nombre de variables trouvées : " << nb_variables << endl;


    /* on crée les contraintes */

    if (nb_lignes < nb_colonnes)
        portee = (int *) malloc(sizeof(int) * nb_colonnes);
    else portee = (int *) malloc(sizeof(int) * nb_lignes);

    for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
        for (num_colonne = 0; num_colonne < nb_colonnes; num_colonne++)
            if (grille[num_ligne][num_colonne].coul == NOIRE) {
                if (grille[num_ligne][num_colonne].somme_horizontale != -1) {
                    arite = 0;
                    i = num_colonne + 1;
                    while ((i < nb_colonnes) && (grille[num_ligne][i].coul == BLANCHE)) {
                        portee[arite] = grille[num_ligne][i].num;
                        arite++;

                        j = i + 1;
                        while ((j < nb_colonnes) && (grille[num_ligne][j].coul == BLANCHE)) {
                            Contrainte_Difference(grille[num_ligne][i].num, grille[num_ligne][j].num);
                            j++;
                        }
                        i++;
                    }

                    Contrainte_Somme(portee, arite, grille[num_ligne][num_colonne].somme_horizontale);
                }

                if (grille[num_ligne][num_colonne].somme_verticale != -1) {
                    arite = 0;
                    i = num_ligne + 1;
                    while ((i < nb_lignes) && (grille[i][num_colonne].coul == BLANCHE)) {
                        portee[arite] = grille[i][num_colonne].num;
                        arite++;

                        j = i + 1;
                        while ((j < nb_lignes) && (grille[j][num_colonne].coul == BLANCHE)) {
                            Contrainte_Difference(grille[i][num_colonne].num, grille[j][num_colonne].num);
                            j++;
                        }
                        i++;
                    }

                    Contrainte_Somme(portee, arite, grille[num_ligne][num_colonne].somme_verticale);
                }
            }


    /* liberation de la mémoire allouée pour la grille et la portée des contraintes */
    free(portee);

    for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
        free(grille[num_ligne]);
    free(grille);
}


/* fonctions à compléter pour remplir vos structures de données */


void parser::Variable(int num)
/* fonction permettant la création d'une nouvelle variable ayant pour numéro num */
{
    printf("Variable %d\n", num);
}


void parser::Contrainte_Difference(int var1, int var2)
/* fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2*/
{
    printf("Contrainte binaire de difference entre %d et %d\n", var1, var2);
}


void parser::Contrainte_Somme(int portee[], int arite, int val)
/* fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
 * dans le tableau portee de taille arite et dont la valeur est val */
{
    printf("Contrainte n-aire de somme portant sur");
    for (int i = 0; i < arite; i++)
        printf(" %d", portee[i]);
    printf(" et de valeur %d\n", val);
}
