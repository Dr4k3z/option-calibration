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
#include "options.h"

namespace BlackScholes{
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

namespace CRR{
       extern int N; // defalt number of time steps // maybe try inline vs extern
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

namespace MC{
       float price(const EuropeanOption& option, float S, float rate);
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

#endif