#ifndef PARSER_H
#define PARSER_H

#include <cstddef>
#include <vector>
#include <memory>


#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/algorithm.h"

struct kakuro_parser {
public:
    void parse(char *nom_fichier);

    /**
     * fonction permettant la création d'une nouvelle variable ayant pour numéro num
     */
    void make_variable(std::vector<csp_variable_ptr> &variables, std::size_t num);

    /**
     * fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2
     * @param var1
     * @param var2
     */
    void constraint_difference(std::vector<csp_variable_ptr> &variables,
                               constraint_vector &constraints,
                               std::size_t var1,
                               std::size_t var2);

    /**
     * fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
     * dans le tableau portee de taille arite et dont la valeur est val
     * @param portee
     * @param arite
     * @param sum
     */
    void constraint_sum(std::vector<csp_variable_ptr> &variables,
                        constraint_vector &constraints, std::vector<std::size_t> portee,
                        std::size_t arite, std::size_t sum);

    void run_algorithm(const csp::algorithm &algo,
                       variable_vector &variables, constraint_vector &constraints, csp::heuristic heuristic);

};


#endif
