#include "RK4.h"
#include "DoublePendEquations.h"

int main() {

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {0.0, -0.5, 1.3, 0.4};

    RK4 rk4(base_ptr);

    rk4.solve(0.001, 10, in);

    auto ret = rk4.query(0, 2, 0.1);

    int it = 1;
    for(auto x : ret) {
       printf("%d : ", it++);
        for(auto y : x) {
            printf("%f ", y);
        }
        printf("\n");
    }
    return 0;
}