#include "DoublePendEquations.h"

int main() {

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {1.0, -2.5, 2.3, 1.4};

    for(auto x : in) {
        printf("%f ", x);
    }

    std::vector<double> vec;
    base_ptr->getValues(2.4, in, &vec);

    for(auto x : vec) {
        printf("%f ", x);
    }

    printf("\n");

    return 0;
}