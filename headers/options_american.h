#ifndef __CppAmericanOptions__AmericanOptions__
#define __CppAmericanOptions__AmericanOptions__

#include "options.h"

/*
       AmericaOption is an abstract class from which American Call and American Put are derived. 
       The only real difference is in the payoff method, while the rest is the same.
*/

class AmericanOption : public Option { 
public:
       AmericanOption(float strike, const Date& expiry_date, const Calendar& cal, const OptionType type) : Option(strike, expiry_date, cal, American, type) {}

       //--------------------
       //Getters
       inline OptionType getType() const{ return type; }

       //--------------------
       //Virtual Methods
       virtual float payoff(float stock) const=0;
};

class AmericanCallOption : public AmericanOption{
public:
       AmericanCallOption(float strike, const Date& expiry_date, const Calendar& cal) : AmericanOption(strike, expiry_date, cal, Call) {}

       inline float payoff(float stock) const override{
              return std::max({stock-strike,0.0f});
       }
};

class AmericanPutOption : public AmericanOption{
public:
       AmericanPutOption(float strike, const Date& expiry_date, const Calendar& cal) : AmericanOption(strike, expiry_date, cal, Put) {}

       inline float payoff(float stock) const override{
              return std::max({strike-stock,0.0f});
       }
};

#endif