#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"
#include "headers/pricing_models.h"
#include "headers/pde.h"
#include "headers/solve.h"




int main(){
       // Create a Calendar object to specify holidays. We use 2024 US financial holidays
       Calendar cal = Calendar::createFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");

       // Set call value and expiry date
       Date valueDate = Date::create(2024,2,15);
       Date expiryDate = Date::create(2024,5,15);

       // Create european options
       EuropeanCallOption call(1,expiryDate,cal); call.setValueDate(valueDate);
       EuropeanPutOption put(1,expiryDate,cal); put.setValueDate(valueDate);

       // Price using different methods
       std::cout << "Call BS = " << BlackScholes::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Call CRR = " << CRR::price(call,1,0.22,0.03) << std::endl;

       std::cout << "--------------------" << std::endl;

       std::cout << "ImpliedVol BS = " << BlackScholes::impliedVolatility(call,1,0.03,0.0389972) << std::endl;
       std::cout << "ImpliedVol CRR = " << CRR::impliedVolatility(call,1,0.03,0.0389029) << std::endl;

       /*std::cout << "Call CRR(" << CRR::N << ") = " << CRR::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Put CRR(" << CRR::N  << ") = " << CRR::price(put,1,0.22,0.03) << std::endl; 

       std::cout << "--------------------" << std::endl;

       std::cout << "Call MC(" << MC::N << ") = " << MC::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Put MC(" << MC::N << ") = " << MC::price(put,1,0.22,0.03) << std::endl;*/
       /*BlackScholesPDE* eqt = BlackScholesPDE::create(&call);
       
       auto fdm = PDESolver::create<ForwardEulerMethod>(eqt);
       auto fem = PDESolver::create<FiniteElementMethod>(eqt);

       Eigen::MatrixXd uh(2,2);
       uh(0,0) = 1;
       uh(0,1) = 2;
       uh(1,0) = 3;
       uh(1,1) = 4;

       std::cout << uh << std::endl;*/
}