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
   double step = 0.01666;

   
   std::vector<double> ic = {9.8, 2.1, 1.2, 1.5, 0.9, 0.5, -0.5, 1.3, 1.2};
   std::vector<string> ic_str  = {"grav", "len1", "mass1", "len2", "mass2", "theta1", "theta2", "dtheta1", "dtheta2"};

   form_iterator fi; 
   for(int i = 0; i < ic.size(); i++) {
      fi = formData.getElement(ic_str[i]);  
      if( !fi->isEmpty() && fi != (*formData).end()) {  
         ic[i] = atof((**fi).c_str());  
      }
   }
   fi = formData.getElement("disc");  
   if( !fi->isEmpty() && fi != (*formData).end()) {  
      disc = atof((**fi).c_str());  
   }

   fi = formData.getElement("step");  
   if( !fi->isEmpty() && fi != (*formData).end()) {  
      step = atof((**fi).c_str());  
   }

   fi = formData.getElement("tf");  
   if( !fi->isEmpty() &&fi != (*formData).end()) {  
      tf = atof((**fi).c_str());  
   }
   
   cout << "Content-type:text/plain\r\n\r\n";

    DoublePendEquations dp(ic[0], ic[1], ic[2], ic[3], ic[4]);
    // FunctionWrapperRK4 * base_ptr = &dp;
    std::vector<double> in = {ic[5], -ic[6], ic[7], ic[8]};

    RK4 rk4(&dp);

    rk4.solve(disc, tf, in);

    auto ret = rk4.query(0, tf, step);

    // int it = 1; 
    // printf("theta1 Theta2 dTheta1 dTheta2\n");
    for(int i = 0; i < ret[0].size(); i++) {
        for(int j = 0; j < ret.size(); j++) {
          printf("%5.3f ", ret[j][i]);
        }
        printf("\n");
    }
   
   return 0;
}