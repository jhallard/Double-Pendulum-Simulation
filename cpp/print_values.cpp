#include "RK4.h"
#include "DoublePendEquations.h"

#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atof */
#include <iostream>

int main(int argc, char ** argv) {

    double disc = 0.0001;
    double tf = 5.0;
    if(argc == 2 || argc == 3)
        disc = atof(argv[1]);
    if(argc == 3)
        tf = atof(argv[2]);

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    // FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {0.0, -0.5, 1.3, 0.4};

    RK4 rk4(&dp);

    rk4.solve(disc, tf, in);

    auto ret = rk4.query(0, tf, 0.001);

    // int it = 1; 
    // printf("theta1 Theta2 dTheta1 dTheta2\n");
    for(int i = 0; i < ret[0].size(); i++) {
        for(int j = 0; j < ret.size(); j++) {
          printf("%4.2f ", ret[j][i]);
        }
        printf("\n");
    }

    return 0;
}
