//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_OSTREAM_H
#define KAKURO_OSTREAM_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "typedefs.h"

using std::ostream;
using std::vector;
using std::string;

namespace csp
{
    class csp_variable;
    class algorithm;
    class csp_constraint;
    class record;
    class solution;
    class heuristic;
}

string edit(const const_iter_v &var);
string edit(const csp::heuristic &var);
string edit(const csp::csp_variable &var);
string edit_value_v(const csp::csp_variable &var);
string edit_domain(const csp::csp_variable &var);
string edit(const csp::algorithm &var);
string edit(const csp::csp_constraint &constraint);
string edit(const csp::record & r);
string edit(const std::size_t & r);

std::string tellHistory(const std::vector<csp::record>&vector, std::size_t explore);

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
string edit_value(const std::vector<T> &collection){
    std::stringstream os;
    os << "@[";
    std::size_t counter{0};
    for(const auto&i:collection){
        os << edit_value_v(*i);
        if (++counter != collection.size()){
            os << ", ";
        }
    }
    os << "]";
    return string(os.str());
}

string edit_fn(variable_vector::const_iterator first, variable_vector::const_iterator second, std::function<string(const csp::csp_variable&)> fn);

template <class T>
string edit(T first, T second){
    std::stringstream os;
    os << "{size:" << std::to_string(std::distance(first,second))  << ",values:[";
    while (first != second){
        os << edit(*first);
        first+=1;
        if (first != second){
            os << ", ";
        }
    }
    os << "]}";
    return os.str();
}

template <typename T>
ostream& operator<<(ostream&os, const vector<T>&collection){
    return os << edit(collection);
}

ostream &operator<<(ostream &os, const csp::csp_variable &var);
ostream &operator<<(ostream &os, const csp_variable_ptr &var);
ostream &operator<<(ostream &os, const csp::algorithm &var);
ostream &operator<<(ostream &os, const csp::csp_constraint &constraint);
ostream &operator<<(ostream &os, const csp::solution &solution);


#endif //KAKURO_OSTREAM_H
