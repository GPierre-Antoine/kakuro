#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <limits>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <ctime>

#include "kakuro_parser.h"
#include "Couleur.h"
#include "Case.h"
#include "csp/algo/algorithm_backtrack.h"
#include "csp/constraint/csp_constraint_sum.h"
#include "csp/constraint/csp_constraint_difference.h"
#include "../cpp11_compat.h"
#include "csp/algo/algorithm_forward_checking.h"

using std::cerr;
using std::cout;
using std::endl;

typedef std::vector<Case>     CaseLine;
typedef std::vector<CaseLine> CaseGrid;

void kakuro_parser::parse(char *nom_fichier)
{
    std::ifstream filestream;

    char        c;            /* le caractère courant */
    std::size_t nb_lignes;    /* le nombre de lignes de la grid */
    std::size_t nb_colonnes;  /* le nombre de colonnes de la grid */
    std::size_t num_ligne;    /* le numero de la ligne courante */
    std::size_t num_colonne;  /* le numero de la colonne courante */
    std::size_t nb_variables; /* le nombre de variables déjà trouvées */
    std::size_t somme;        /* une somme */

    CaseGrid                 grid;
    std::vector<std::size_t> portee;     /* la portee d'une contrainte */
    std::size_t              arite;        /* l'arité d'une contrainte */

    filestream.open(nom_fichier, std::ifstream::in);

    if (!filestream.is_open())
    {
        throw std::runtime_error(std::string("Fichier ") + nom_fichier + " non trouve");
    }

    /* on calcule la taille de la grid */

    nb_lignes   = 0;
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

    assert(!grid.empty());

    for (const auto &line : grid)
    {
        assert(!line.empty());
    }

    filestream.clear();
    filestream.seekg(0, std::ios::beg);

    num_ligne    = 0;
    num_colonne  = 0;
    nb_variables = 0;

    std::vector<csp_variable_ptr>   variables;
    std::vector<std::unique_ptr<csp::csp_constraint>> constraints;

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
            grid[num_ligne][num_colonne].num  = nb_variables;
            make_variable(variables, nb_variables);
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
    std::sort(variables.begin(), variables.end(),
              [](const csp_variable_ptr &f, const csp_variable_ptr &s)
              { return f->get_id() < s->get_id(); });
    constraints.reserve(3 * nb_variables);

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
                    std::size_t i = num_colonne + 1;
                    while ((i < nb_colonnes) && (grid[num_ligne][i].is_white()))
                    {
                        portee[arite] = grid[num_ligne][i].num;
                        arite++;

                        std::size_t j = i + 1;
                        while ((j < nb_colonnes) && (grid[num_ligne][j].is_white()))
                        {
                            constraint_difference(variables, constraints, grid[num_ligne][i].num,
                                                  grid[num_ligne][j].num);
                            j++;
                        }
                        i++;
                    }

                    constraint_sum(variables, constraints, portee, arite,
                                   grid[num_ligne][num_colonne].somme_horizontale);
                }

                if (grid[num_ligne][num_colonne].somme_verticale != std::numeric_limits<std::size_t>::max())
                {
                    arite = 0;
                    std::size_t i = num_ligne + 1;
                    while ((i < nb_lignes) && (grid[i][num_colonne].is_white()))
                    {
                        portee[arite] = grid[i][num_colonne].num;
                        arite++;

                        std::size_t j = i + 1;
                        while ((j < nb_lignes) && (grid[j][num_colonne].is_white()))
                        {
                            constraint_difference(variables, constraints, grid[i][num_colonne].num,
                                                  grid[j][num_colonne].num);
                            j++;
                        }
                        i++;
                    }

                    constraint_sum(variables, constraints, portee, arite, grid[num_ligne][num_colonne].somme_verticale);
                }
            }
        }
    }

    heuristic base = [](const csp_variable_ptr &f, const csp_variable_ptr & s)
    { return f->get_id() < s->get_id(); };


    run_algorithm(csp::algorithm_backtrack(true), variables, constraints, base);
    run_algorithm(csp::algorithm_forward_checking(true), variables, constraints, base);



    auto dom_deg = [](const csp_variable_ptr &f){
        return f->get_constraint_count();
    };

    auto dom_deg_comp =
                 [&dom_deg](const csp_variable_ptr & f, const csp_variable_ptr & s)
                 {
                     return  dom_deg(f) < dom_deg(s);
                 };

    run_algorithm(csp::algorithm_forward_checking(true), variables, constraints, dom_deg_comp);

}

/*
 * fonctions à compléter pour remplir vos structures de données
 */


/**
 * fonction permettant la création d'une nouvelle variable ayant pour numéro num
 */
void kakuro_parser::make_variable(std::vector<csp_variable_ptr> &variables, std::size_t num)
{
    cout << "Variable " << num << endl;
    variables.push_back(make_yield(num));
}

/**
 * fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2
 */

void kakuro_parser::constraint_difference(std::vector<csp_variable_ptr> &variables,
                                          std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                          std::size_t var1, std::size_t var2)
{
    cout << "Contrainte binaire de difference entre " << var1 << " et " << var2 << endl;
    auto v1 = variables.at(var1);
    v1->increment_constraint_count();
    auto v2 = variables.at(var2);
    v2->increment_constraint_count();
    std::vector<csp_variable_ptr> holder{v1, v2};
    constraints.emplace_back(make_unique<csp::csp_constraint_difference>(holder));
}

/**
 * fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
 * dans le tableau portee de taille arite et dont la valeur est val
 */
void kakuro_parser::constraint_sum(std::vector<csp_variable_ptr> &variables,
                                   std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                   std::vector<std::size_t> portee, std::size_t arite, std::size_t sum)
{
    std::string                                     text;
    std::vector<csp_variable_ptr> holder;
    holder.reserve(arite);
    for (std::size_t index = 0; index < arite; index++)
    {
        auto var = variables.at(portee[index]);
        var->increment_constraint_count();
        holder.push_back(var);
        text += " " + std::to_string(portee[index]);
    }
    constraints.emplace_back(make_unique<csp::csp_constraint_sum>(holder, sum));
    cout << "Contrainte n-aire de somme portant sur" << text << " et de valeur " << std::to_string(sum) << endl;
}

void kakuro_parser::run_algorithm(const csp::algorithm &algo,
                                  std::vector<csp_variable_ptr> &variables,
                                  const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                  heuristic heuristic)
{
    for (auto &i:variables)
    {
        i->release_all();
        i->reset();
    }

    std::sort(variables.begin(), variables.end(), heuristic);

    std::clock_t begin        = std::clock();
    auto         affectations = algo.run(variables, constraints, heuristic);
    std::clock_t end          = std::clock();

    auto elasped_clock = (static_cast<std::size_t >(end - begin));

    cout << "Ran algorithm " + algo.name + " in " << elasped_clock << " clocks" << endl;
    cout << "Affectations found : " << affectations.size() << endl;
    auto            solution_number = 0u;
    for (const auto &solution:affectations)
    {

        std::string     text;
        for (const auto &value:solution)
        {
            text += "{" + std::to_string(value) + "}";
        }
        cout
                << "Solution #"
                << std::setfill('0')
                << std::setw(3)
                << std::to_string(++solution_number)
                << " : "
                << text
                << endl;
    }
}
