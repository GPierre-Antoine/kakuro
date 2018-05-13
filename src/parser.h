#ifndef PARSER_H
#define PARSER_H

class parser
{
public:
    void parse(char *nom_fichier);

    /**
     * fonction permettant la création d'une nouvelle variable ayant pour numéro num
     */
    void Variable(int num);

    /**
     * fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2
     * @param var1
     * @param var2
     */
    void Contrainte_Difference(int var1, int var2);

    /**
     * fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant
     * dans le tableau portee de taille arite et dont la valeur est val
     * @param portee
     * @param arite
     * @param val
     */
    void Contrainte_Somme(int portee[], int arite, int val);
};


#endif
