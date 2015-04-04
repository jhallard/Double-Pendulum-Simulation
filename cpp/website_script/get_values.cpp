#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 
#include <iostream>

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h> 

#include "/home/jhallard/Double-Pendulum-Simulation/cpp/RK4.h"
#include "/home/jhallard/Double-Pendulum-Simulation/cpp/DoublePendEquations.h"


using namespace std;
using namespace cgicc;


int main ()
{
   Cgicc formData;

   double tf = 2.5;
   double disc = 0.00001;

   form_iterator fi = formData.getElement("disc");  
   if( !fi->isEmpty() && fi != (*formData).end()) {  
      disc = atof((**fi).c_str());  
   }

   fi = formData.getElement("tf");  
   if( !fi->isEmpty() &&fi != (*formData).end()) {  
      tf = atof((**fi).c_str());  
   }
   
   cout << "Content-type:text/plain\r\n\r\n";

    DoublePendEquations dp(9.8, 2.0, 1.0, 2.0, 1.0);
    // FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {0.0, -0.5, 1.3, 0.4};

    RK4 rk4(&dp);

    rk4.solve(disc, tf, in);

    auto ret = rk4.query(0, tf, disc*10.0);

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