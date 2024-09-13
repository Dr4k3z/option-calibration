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
       Date value_date = Date::today(); // I don't really like this is handled

       // I need to put some thought into this shite
       float price;
       float bid_price;
       float ask_price;
       float volatility;        
public:
       //--------------------
       //Constructors
       EuropeanOption(float strike, const Date& expiry_date, const Calendar& cal, Type type) : strike(strike), expiry_date(expiry_date), cal(cal), type(type) {}
       EuropeanOption(const EuropeanOption& p) : strike(p.strike), value_date(p.value_date), expiry_date(p.expiry_date), cal(p.cal), type(p.type) {}
       EuropeanOption &operator=(const EuropeanOption& p); //How does it work with constant members?

       //--------------------
       //Getters
       inline float getStrike() const{ return strike; }
       inline Type getType() const{ return type; }
       inline Date getValueDate() const{ return value_date; }
       inline Date getExpiryDate() const{ return expiry_date; }
       inline Calendar getCalendar() const{ return cal; }
       inline float getPrice() const{ return price; }
       inline float getBidPrice() const{ return bid_price; }
       inline float getAskPrice() const{ return ask_price; }

       //--------------------
       //Setters
       inline void setValueDate(const Date& d){ value_date = d; }
       inline void setPrice(float p){ price = p; }
       inline void setBidPrice(float p){ bid_price = p; }
       inline void setAskPrice(float p){ ask_price = p; }

       //--------------------
       //Date management methods
       float time2maturity(Units unit = Years) const;

       //--------------------
       //Virtual Methods
       virtual float payoff(float stock) const=0;
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

/*
       Option chains are sets of options on th esame underlying asset, with different strike prices and/or expiry dates.
       In this case, we only consider options with the same expiry date.
*/
class OptionChain{
private:
       const Date& value_date;
       const Date& expiry_date;
       const Calendar& cal;
       const Type type;
       std::vector<std::unique_ptr<EuropeanOption>> options;

       // Constructor
       OptionChain(const Date& value_date, const Date& expiry_date, const Calendar& cal, const Type type) : value_date(value_date), expiry_date(expiry_date), cal(cal), type(type) {}
public:
       // Factory methods
       static OptionChain* create(const Date& value_date, const Date& expiry_date, const Calendar& cal, const Type type){
              return new OptionChain(value_date, expiry_date, cal, type);
       }
       static OptionChain* createFromCsv(const Date& value_date, const Date& expiry_date, const Calendar& cal, const Type type, const std::string& filename);

       // Methods to add options to the chain
       void addOption(std::unique_ptr<EuropeanOption> option);
       void loadOptionChain(const std::string& filename); // TODO

       // Getters
       Date valueDate() const{ return value_date; }
       Date getExpiryDate() const{ return expiry_date; }
       float getTime2Maturity() const{ return options[0]->time2maturity(); }
       const std::vector<std::unique_ptr<EuropeanOption>>& getOptions() const{ return options; } // I dont like this getter, should return a reference
       std::vector<float> getStrikes() const;

       // Methods to visualize the chain
       void print();

       // Operator overloading
       //std::string operator<<();
};

#endif