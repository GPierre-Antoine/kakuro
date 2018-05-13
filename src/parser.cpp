#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <limits>
#include <cassert>

#include "parser.h"
#include "Couleur.h"
#include "Case.h"

using std::cerr;
using std::cout;
using std::endl;

typedef std::vector<Case> CaseLine;
typedef std::vector<CaseLine> CaseGrid;

void parser::parse(char *nom_fichier)
{
    std::ifstream filestream;

    char c;            /* le caractère courant */
    std::size_t nb_lignes;    /* le nombre de lignes de la grid */
    std::size_t nb_colonnes;  /* le nombre de colonnes de la grid */
    std::size_t num_ligne;    /* le numero de la ligne courante */
    std::size_t num_colonne;  /* le numero de la colonne courante */
    std::size_t nb_variables; /* le nombre de variables déjà trouvées */
    std::size_t somme;        /* une somme */

    CaseGrid grid;
    Portee portee;     /* la portee d'une contrainte */
    std::size_t arite;        /* l'arité d'une contrainte */
    std::size_t i, j;          /* des compteurs de boucle */

    filestream.open(nom_fichier, std::ifstream::in);

    if (!filestream.is_open())
    {
        throw std::runtime_error(std::string("Fichier ") + nom_fichier + " non trouve");
    }

    /* on calcule la taille de la grid */

    nb_lignes = 0;
    nb_colonnes = 0;
    filestream.get(c);

    while (!filestream.eof())
    {
        if (c == '\n')
        {
            nb_lignes++;
        }
        else if ((nb_lignes == 0) && ((c == '.') || (c == '\\')))
        {
            nb_colonnes++;
        }
        filestream.get(c);
    }

    cout << "Taille : " << nb_lignes << " x " << nb_colonnes << endl;

    /* remplissage de la grid */

    grid.reserve(nb_lignes);
    for (std::size_t numligne = 0; numligne < nb_lignes; numligne++)
    {
        CaseLine line;
        line.reserve(nb_colonnes);
        for (std::size_t numcol{0}; numcol < nb_colonnes; ++numcol)
        {
            line.emplace_back(Case());
        }
        grid.push_back(line);

    }

    assert(grid.size() != 0);

    for (const auto &line : grid)
    {
        assert(line.size() != 0);
    }

    filestream.clear();
    filestream.seekg(0, std::ios::beg);

    num_ligne = 0;
    num_colonne = 0;
    nb_variables = 0;

    filestream.get(c);

    while (!filestream.eof())
    {
        if (c == '\n')
        {
            num_ligne++;
            num_colonne = 0;
        }
        else if (c == ' ')
        {
            num_colonne++;
        }
        else if (c == '.')     /* case blanche */
        {
            grid[num_ligne][num_colonne].coul = BLANCHE;
            grid[num_ligne][num_colonne].num = nb_variables;
            Variable(nb_variables);

            nb_variables++;
        }
        else if (c == '\\')    /* case noire de la forme \y ou \ */
        {
            grid[num_ligne][num_colonne].coul = NOIRE;
            filestream.get(c);

            if (isdigit(c))    /* case noire de la forme \y */
            {
                filestream.putback(c);
                filestream >> somme;
                grid[num_ligne][num_colonne].somme_horizontale = somme;
            }
            else  /* case noire de la forme \ */
            {
                filestream.putback(c);
            }
        }
        else if (isdigit(c))    /* case noire de la forme x\ ou x\y */
        {
            grid[num_ligne][num_colonne].coul = NOIRE;

            filestream.putback(c);
            filestream >> somme;
            grid[num_ligne][num_colonne].somme_verticale = somme;

            filestream.get(c);   /* on lit le caractère \ */
            filestream.get(c);

            if (isdigit(c))  /* case noire de la forme x\y */
            {
                filestream.putback(c);
                filestream >> somme;
                grid[num_ligne][num_colonne].somme_horizontale = somme;
            }
            else   /* case noire de la forme x\ */
            {
                filestream.putback(c);
            }
        }
        filestream.get(c);
    }
    filestream.close();

    cout << "Nombre de variables trouvées : " << nb_variables << endl;


    /* on crée les contraintes */

    if (nb_lignes < nb_colonnes)
    {
        portee.resize(nb_colonnes);
    }
    else
    {
        portee.resize(nb_lignes);
    }

    for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
    {
        for (num_colonne = 0; num_colonne < nb_colonnes; num_colonne++)
        {
            if (grid[num_ligne][num_colonne].is_black())
            {
                if (grid[num_ligne][num_colonne].somme_horizontale != std::numeric_limits<std::size_t>::max())
                {
                    arite = 0;
                    i = num_colonne + 1;
                    while ((i < nb_colonnes) && (grid[num_ligne][i].is_white()))
                    {
                        portee[arite] = grid[num_ligne][i].num;
                        arite++;

                        j = i + 1;
                        while ((j < nb_colonnes) && (grid[num_ligne][j].is_white()))
                        {
                            Contrainte_Difference(grid[num_ligne][i].num, grid[num_ligne][j].num);
                            j++;
                        }
                        i++;
                    }

                    Contrainte_Somme(portee, arite, grid[num_ligne][num_colonne].somme_horizontale);
                }

                if (grid[num_ligne][num_colonne].somme_verticale != std::numeric_limits<std::size_t>::max())
                {
                    arite = 0;
                    i = num_ligne + 1;
                    while ((i < nb_lignes) && (grid[i][num_colonne].is_white()))
                    {
                        portee[arite] = grid[i][num_colonne].num;
                        arite++;

                        j = i + 1;
                        while ((j < nb_lignes) && (grid[j][num_colonne].is_white()))
                        {
                            Contrainte_Difference(grid[i][num_colonne].num, grid[j][num_colonne].num);
                            j++;
                        }
                        i++;
                    }

                    Contrainte_Somme(portee, arite, grid[num_ligne][num_colonne].somme_verticale);
                }
            }
        }
    }
}

/* fonctions à compléter pour remplir vos structures de données */


void parser::Variable(std::size_t num)
/* fonction permettant la création d'une nouvelle variable ayant pour numéro num */
{
    cout << "Variable " << num << endl;
}

void parser::Contrainte_Difference(std::size_t var1, std::size_t var2)
/* fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2*/
{
    cout << "Contrainte binaire de difference entre " << var1 << " et " << var2 << endl;
}

void parser::Contrainte_Somme(Portee portee, std::size_t arite, std::size_t val)
/* fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
 * dans le tableau portee de taille arite et dont la valeur est val */
{
    cout << "Contrainte n-aire de somme portant sur";
    for (std::size_t i = 0; i < arite; i++)
    {
        cout << " " << portee[i];
    }
    cout << " et de valeur " << val << endl;
}
