
#include "FunctionWrapperRK4.h"

FunctionWrapperRK4::FunctionWrapperRK4(int num_equations) {
    if(num_equations >= 1) 
        _num_equations = num_equations;
}

int getNumEquations() const {
    return _num_equations;
}