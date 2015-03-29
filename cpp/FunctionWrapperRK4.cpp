
#include "FunctionWrapperRK4.h"

FunctionWrapperRK4::FunctionWrapperRK4(int num_equations) {
    if(num_equations >= 1) 
        _num_equations = num_equations;
}

std::vector<double> FunctionWrapperRK4::getValues(double time, const std::vector<double> & state) {
    return std::vector<t>(_num_equations) = {0};
}

int getNumEquations() const {
    return _num_equations;
}