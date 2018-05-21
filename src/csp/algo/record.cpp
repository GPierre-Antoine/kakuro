//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "record.h"
#include "../../ostream.h"

csp::record::record(record_type type, csp_variable_ptr variable) : type(type), variable(variable)
{

}

bool csp::record::is_manual() const
{
    return this->type == record_type::manual;
}

void csp::record::forget()
{
    if (variable)
    {
        variable->release_last();
    }
}

csp::record::~record()
{
    this->forget();
}

const csp_variable_ptr csp::record::get_variable() const
{
    return variable;
}

bool csp::record::is_same_variable(const csp::csp_variable &other) const
{
    return *variable == other;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
csp::record::record(csp::record &&other)  noexcept // NOLINT
{
    swap(*this, other);
}
#pragma clang diagnostic pop

