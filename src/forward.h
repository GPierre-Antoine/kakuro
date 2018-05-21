//
// Created by Pierre-Antoine on 21/05/2018.
//

#ifndef KAKURO_FORWARD_H
#define KAKURO_FORWARD_H

#include <memory>
namespace csp
{
    class csp_variable;
}

typedef std::shared_ptr<csp::csp_variable> csp_variable_ptr;
csp_variable_ptr make_yield(std::size_t var);

#endif //KAKURO_FORWARD_H
