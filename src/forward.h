//
// Created by Pierre-Antoine on 21/05/2018.
//

#ifndef KAKURO_FORWARD_H
#define KAKURO_FORWARD_H

#include <memory>
#include <vector>
#include <functional>

namespace csp
{
    class csp_variable;
    class csp_constraint;
    class record;
}

typedef std::shared_ptr<csp::csp_variable> csp_variable_ptr;
csp_variable_ptr make_yield_variable(std::size_t);

typedef std::vector<csp_variable_ptr> variable_vector;

typedef std::shared_ptr<csp::csp_constraint> csp_constraint_ptr;
csp_constraint_ptr make_yield_c_sum(variable_vector &, std::size_t);
csp_constraint_ptr make_yield_c_diff(variable_vector &);


typedef std::vector<csp::record> record_vector;

template<typename iter_t, class T, class type>
T reduce(iter_t begin, iter_t end, T init, std::function<T (T,type)> f)
{
    for (; begin != end; std::advance(begin, 1))
    {
        init = f(init, *begin);
    }
    return init;
}

typedef std::vector<csp_constraint_ptr> constraint_vector;
typedef variable_vector::iterator iter_v;
typedef variable_vector::const_iterator const_iter_v;

#endif //KAKURO_FORWARD_H
