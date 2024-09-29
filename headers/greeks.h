#ifndef __CppOptions__Greeks__
#define __CppOptions__Greeks__

#include "pricing_models.h"

/*
       We implement the Greeks under the Black Scholes model
*/

#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>


namespace Greeks{
       float delta(const Option& option, float S, float sigma, float rate, float tmt=0.0){
              float d1 = BlackScholes::d1(option,S,sigma,rate,tmt);
              if (option.getType() == Call){
                     return std::exp(-rate*tmt)*Math::normalCDF(d1);
              }else{
                     return std::exp(-rate*tmt)*(Math::normalCDF(d1)-1);
              }
       }

       float gamma(const Option& option, float S, float sigma, float rate, float tmt=0.0){
              if (tmt == 0.0){
                     tmt = option.time2maturity();
              }
              
              float d1 = BlackScholes::d1(option,S,sigma,rate,tmt);
              return Math::normalPDF(d1)/(S*sigma*std::sqrt(tmt));
       }

       float rho(const Option& option, float S, float sigma, float rate, float tmt=0.0){
              if (tmt == 0.0){
                     tmt = option.time2maturity();
              }
              
              float d2 = BlackScholes::d2(option,S,sigma,rate,tmt);
              if (option.getType() == Call){
                     return tmt*std::exp(-rate*tmt)*Math::normalCDF(d2);
              }else{
                     return -tmt*std::exp(-rate*tmt)*Math::normalCDF(-d2);
              }
       }

       float theta(const Option& option, float S, float sigma, float rate, float tmt=0.0){
              if (tmt == 0.0){
                     tmt = option.time2maturity();
              }
              
              float d1 = BlackScholes::d1(option,S,sigma,rate,tmt);
              float d2 = BlackScholes::d2(option,S,sigma,rate,tmt);
              if (option.getType() == Call){
                     return -S*Math::normalPDF(d1)*sigma/(2*std::sqrt(tmt))-rate*S*Math::normalCDF(d1)*std::exp(-rate*tmt);
              }else{
                     return -S*Math::normalPDF(d1)*sigma/(2*std::sqrt(tmt))+rate*S*Math::normalCDF(-d1)*std::exp(-rate*tmt);
              }
       }

       float vega(const Option& option, float S, float sigma, float rate, float tmt=0.0){
              if (tmt == 0.0){
                     tmt = option.time2maturity();
              }
              
              float d1 = BlackScholes::d1(option,S,sigma,rate,tmt);
              return S*Math::normalPDF(d1)*std::sqrt(tmt);
       }
};

#endif