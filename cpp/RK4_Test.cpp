#include "RK4.h"
#include "DoublePendEquations.h"

int main() {

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {0.0, -0.5, 1.3, 0.4};

    RK4 rk4(base_ptr);

    rk4.solve(0.0001, 2, in);

    return 0;
}