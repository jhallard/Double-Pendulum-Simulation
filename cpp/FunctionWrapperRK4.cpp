
#include "FunctionWrapperRK4.h"

template <class t>
FunctionWrapperRK4::FunctionWrapperRK4(int num_equations) {
    if(num_equations >= 1) 
        _num_equations = num_equations;
}

template <class t>
std::vector<t> FunctionWrapperRK4::getValues(double time, const std::vector<t> & state) {
    return std::vector<t>(_num_equations) = {0};
}

template<class t>
int getNumEquations() const {
    return _num_equations;
}