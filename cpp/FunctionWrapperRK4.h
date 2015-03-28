#ifndef FUNC_WRAP_RK4
#define FUNC_WRAP_RK4

#include <vector>
#include <math>


// @class - FunctionWrapperRK4
// @info  - This is to serve as the base class for this hierarchy. All of these classes are meant to be wrappers around sets of equations
//          that are passed into the RK4 class to be solved.
template<class t>
class FunctionWrapperRK4 {

private:
    // number of equations to wrap with this object
    int _num_equations;

public:

    // @func - Constructor
    // @args - #1 number of equations to be wrapped
    FunctionWrapperRK4(int);

    // @func - getValues
    // @args - #1 current time value to be used #2 current state values to be used
    // @info - This function needs to be overwritten by child classes to return the true function values
    std::vector<t> getValues(double, std::vector<t>);

    // @self-documenting
    int getNumEquations() const; 
};



#endif