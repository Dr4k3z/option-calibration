#include "../headers/pricing_models.h"

float BS::price(const EuropeanOption& option, float S, float rate){
       float t = V.maturity - date;
       
       float d1 = (log(stock/V.strike)+(rate+pow(sigma,2)/2)*t)/(sigma*sqrt(t));           
       float d2 = d1-sigma*sqrt(t);
       if (flag){
              std::cout << "d1 = " << d1 << std::endl;
              std::cout << "d2 = " << d2 << std::endl;
       }

       return normalCDF(d1)*stock-normalCDF(d2)*V.strike*exp(-rate*t);
}