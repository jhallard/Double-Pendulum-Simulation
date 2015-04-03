#include "RK4.h"
#include "DoublePendEquations.h"

int main() {

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    // FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {0.0, -0.5, 1.3, 0.4};

    RK4 rk4(&dp);

    rk4.solve(0.0001, 10, in);

    auto ret = rk4.query(0, 2, 0.001);

    int it = 1; 
    printf("theta1 Theta2 dTheta1 dTheta2\n");
    for(int i = 0; i < ret[0].size(); i++) {
        for(int j = 0; j < ret.size(); j++) {
          printf("%4.2f ", ret[j][i]);
        }
        printf("\n");
    }

    return 0;


}
