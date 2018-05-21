//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "record.h"
#include "../../ostream.h"

csp::record::record(record_type type, csp::csp_variable &variable) : type(type), variable(&variable)
{

}

bool csp::record::is_manual() const
{
    return this->type == record_type::manual;
}

void csp::record::forget()
{
    variable->release_last();
}

csp::record::~record()
{
    if (variable)
    {
        this->forget();
    }
}

const csp::csp_variable &csp::record::get_record() const
{
    return *variable;
}

bool csp::record::is_same_variable(const csp::csp_variable &other) const
{
    return *variable == other;
}

csp::record::record(csp::record && other) noexcept
{
    swap(*this, other);
}
