//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_OSTREAM_H
#define KAKURO_OSTREAM_H

#include <iostream>
#include <vector>
#include <sstream>
#include "typedefs.h"

using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::string;

namespace csp
{
    class csp_variable;
    class algorithm;
    class csp_constraint;
}

string edit(const csp::csp_variable &var);
string edit(const csp::algorithm &var);
string edit(const csp::csp_constraint &constraint);

template <typename T>
string edit(const std::vector<T> &collection){
    std::stringstream os;
    os << "@[";
    std::size_t counter{0};
    for(const auto&i:collection){
        os << edit(*i);
        if (++counter != collection.size()){
            os << ", ";
        }
    }
    os << "]";
    return string(os.str());
}

template <typename T>
ostream& operator<<(ostream&os, const vector<T>&collection){
    return os << edit(collection);
}

ostream &operator<<(ostream &os, const csp::csp_variable &var);
ostream &operator<<(ostream &os, const csp_variable_ptr &var);
ostream &operator<<(ostream &os, const csp::algorithm &var);
ostream &operator<<(ostream &os, const csp::csp_constraint &constraint);


#endif //KAKURO_OSTREAM_H
