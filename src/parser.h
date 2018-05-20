#ifndef PARSER_H
#define PARSER_H

#include <cstddef>
#include <vector>
#include <unordered_map>


#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"


class parser
{
private:
    std::vector<csp::csp_variable> variables;
    std::vector<csp::csp_constraint> constraints;
public:
    void parse(char *nom_fichier);

    /**
     * fonction permettant la création d'une nouvelle variable ayant pour numéro num
     */
    void make_variable(std::size_t num);

    /**
     * fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2
     * @param var1
     * @param var2
     */
    void constraint_difference(std::size_t var1, std::size_t var2);

    /**
     * fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
     * dans le tableau portee de taille arite et dont la valeur est val
     * @param portee
     * @param arite
     * @param sum
     */
    void constraint_sum(std::vector<std::size_t> portee, std::size_t arite, std::size_t sum);

    parser() = default;
};


#endif
