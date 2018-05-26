//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "record.h"
#include "../../ostream.h"

csp::record::record(record_type type, csp_variable_ptr variable, std::size_t timestamp, std::size_t count)
    : type(type), variable(std::move(variable)), timestamp(timestamp), count(count)
{

}

csp::record::record(csp::record &&other) noexcept : timestamp(other.timestamp), count(other.count) // NOLINT
{
    swap(*this, other);
}


bool csp::record::is_manual() const
{
    return this->type == record_type::manual;
}

void csp::record::forget()
{
    if (variable)
    {
        variable->release_last(count);
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
