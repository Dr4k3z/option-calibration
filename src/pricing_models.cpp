#include "../headers/pricing_models.h"

float normalCDF(float value, float mean=0, float std = 1){
       return 0.5 * (1.0 + std::erf((value - mean) / (std * std::sqrt(2.0))));
}

float BS::price(const EuropeanOption& option, float S, float sigma, float rate){
       float tmt = option.time2maturity(Years);

       std::cout << "time to maturity: " << tmt << std::endl;

       float K = option.getStrike();

       float d1 = (std::log(S/K)+(rate+0.5*sigma*sigma)*tmt)/(sigma*std::sqrt(tmt));
       float d2 = d1-sigma*std::sqrt(tmt);

       if (option.getType() == Call){
              return normalCDF(d1)*S-normalCDF(d2)*K*exp(-rate*tmt);
       }else{
              return K*std::exp(-rate*tmt)*normalCDF(-d2) - S*normalCDF(-d1);
       }
}
