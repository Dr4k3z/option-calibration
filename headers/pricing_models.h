#include <iostream>
#include "options.h"

class BS{
public:
       static float price(const EuropeanOption& option, float S, float rate);
       static float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

class CRR{
public:
       static float price(const EuropeanOption& option, float S, float rate);
       static float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};

class MC{
       static float price(const EuropeanOption& option, float S, float rate);
       static float impliedVolatility(const EuropeanOption& option, float S, float rate, float marketPrice);
};