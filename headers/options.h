#ifndef __CppOptions__Options__
#define __CppOptions__Options__

#include "calendar.h"
#include "date.h"

/*
       EuropeanOption is an abstract class from which European Call and European Put are derived. 
       The only real difference is in the payoff method, while the rest is the same.
*/

#include <algorithm>

enum Units{
       Days,
       Months,
       Years
};

enum Type{
       Call,
       Put
};

class EuropeanOption{
protected:
       const float strike;
       const Date expiry_date;
       const Calendar cal;
       const Type type;
public:
       //--------------------
       //Constructors
       EuropeanOption(float strike, const Date& expiry_date, const Calendar& cal, Type type) : strike(strike), expiry_date(expiry_date), cal(cal), type(type) {}
       EuropeanOption(const EuropeanOption& p) : strike(p.strike), expiry_date(p.expiry_date), type(p.type) {}
       EuropeanOption &operator=(const EuropeanOption& p); //How does it work with constant members?

       //--------------------
       //Getters
       float getStrike() const{ return strike; }
       Type getType() const{ return type; }

       //--------------------
       //Date management methods
       float time2maturity(Units unit = Days) const;

       //--------------------
       //Virtual Methods
       virtual float payoff(float stock) const=0;
};

class EuropeanCallOption : public EuropeanOption{
public:
       EuropeanCallOption(float strike, Date expiry_date, Calendar cal) : EuropeanOption(strike,expiry_date, cal, Call) {}
       
       float payoff(float stock) const{
              return std::max({stock-strike,0.0f});
       }
};

class EuropeanPutOption : public EuropeanOption{
public:
       EuropeanPutOption(float strike, Date expiry_date, Calendar cal) : EuropeanOption(strike, expiry_date, cal, Put) {}

       float payoff(float stock) const{
              return std::max({strike-stock,0.0f});
       }
};

#endif