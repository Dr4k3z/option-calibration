#ifndef __Cpp_EuropeanOptions__EuropeanOptions__
#define __Cpp_EuropeanOptions__EuropeanOptions__

#include "options.h"

class EuropeanOption : public Option{
protected:
       const OptionType type;
public:
       EuropeanOption(float strike, const Date& expiry_date, const Calendar& cal, OptionType type) : Option(strike, expiry_date, cal, European, type), type(type) {}

       inline OptionType getType() const{ return type; }
};

class EuropeanCallOption : public EuropeanOption{
public:
       EuropeanCallOption(float strike, const Date& expiry_date, const Calendar& cal) : EuropeanOption(strike, expiry_date, cal, Call) {}

       inline float payoff(float stock) const override{
              return std::max({stock-strike,0.0f});
       }
};

class EuropeanPutOption : public EuropeanOption{
public:
       EuropeanPutOption(float strike, const Date& expiry_date, const Calendar& cal) : EuropeanOption(strike, expiry_date, cal, Put) {}

       inline float payoff(float stock) const override{
              return std::max({strike-stock,0.0f});
       }
};

#endif