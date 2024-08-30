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
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // non-calendarized time to maturity
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

namespace Black76{
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // todo
}

namespace CRR{
       extern int N; // defalt number of time steps // maybe try inline vs extern
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // todo

       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

namespace MC{
       extern int N;
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // todo
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

#endif