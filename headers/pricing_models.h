#ifndef __CppOptions__PricingModels__
#define __CppOptions__PricingModels__

#include "date.h"
#include "calendar.h"
#include "options.h"

class PricingModel{
public:
       virtual float price(const EuropeanOption& option)=0;
       virtual float impliedVolatility(const EuropeanCallOption& option, float S, float rate, float marketPrice)=0;
       virtual ~PricingModel();
};

class BS : public PricingModel{
public:
       static float price(const EuropeanOption& option, float S, float sigma, float rate);
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

#endif