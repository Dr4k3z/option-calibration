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

namespace Black76{
       float price(const EuropeanOption& option, float S, float sigma, float rate);
       float price(const EuropeanOption& option, float S, float tmt, float sigma, float rate); // non-calendarized time to maturity
};

namespace CRR{
       extern int N; // defalt number of time steps // maybe try inline vs extern
       float price(const EuropeanOption& option, float S, float sigma, float rate, float tmt=-1.0);
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float tmt=-1.0, float marketPrice=0.0); // non-calendarized time to maturity
};

namespace MC{
       extern int N;
       float price(const EuropeanOption& option, float S, float sigma, float rate, float tmt=-1.0);
       // these two do not work, I need to implement a MC simulation
       float impliedVolatility(const EuropeanOption& option, float S, float rate, float tmt=-1.0, float marketPrice=0.0); // non-calendarized time to maturity
};

#endif