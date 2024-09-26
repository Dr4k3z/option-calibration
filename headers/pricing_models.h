#ifndef PRICING_MODELS_HEADER
#define PRICING_MODELS_HEADER

/*
       This file contains all the different way to price derivatives.
       They are grouped in namespaces to avoid name conflict. 
       Most namespaces have a price method, that returns the price according 
       to some specific methodology and a impliedVolatility methods, that returns
       the market implied volatility according to the said pricing routine. 
*/

#include "date.h"
#include "calendar.h"
#include "options_european.h"

namespace BlackScholes{
       float price(const Option& option, float S, float sigma, float rate, float tmt=0.0); 
       // I dont like the doulbe default value, I should find a way to avoid it
       float impliedVolatility(const Option& option, float S, float rate, float tmt=0.0, float marketPrice=0.0); // non-calendarized time to maturity
       std::vector<float> calibrate(const OptionChain* chain, float S, float rate);
};

namespace Black76{
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // non-calendarized time to maturity
}

namespace CRR{
       extern int N; // defalt number of time steps // maybe try inline vs extern
       float price(const EuropeanOption& option, float S, float sigma, float rate, float tmt=0.0);
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float tmt=0.0, float marketPrice=0.0); // non-calendarized time to maturity
};

namespace MC{
       extern int N;
       float price(const EuropeanOption& option, float S, float sigma, float rate, float tmt=0.0);
       // these two do not work, I need to implement a MC simulation
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float tmt=0.0, float marketPrice=0.0); // non-calendarized time to maturity
};

#endif