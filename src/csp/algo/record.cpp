//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "record.h"
csp::record::record(record_type type, csp::csp_variable &variable) : type(type), variable(variable)
{

}
bool csp::record::is_manual() const
{
    return this->type == record_type::manual;
}
void csp::record::forget()
{
    variable.release_last();
}
csp::record::~record()
{
    this->forget();
}
const csp::csp_variable& csp::record::get_record() const
{
    return variable;
}
bool csp::record::compare_record(const csp::csp_variable &variable) const
{
    return variable==this->variable;
}
