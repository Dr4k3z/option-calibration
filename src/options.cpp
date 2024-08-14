#include "../headers/options.h"

float EuropeanOption::time2maturity(Units unit) const{
       Date t = Date::today();
       int tmt = cal.tradingDays(t,expiry_date);
       switch (unit){
       case Days:
              return tmt;
       case Months:
              return tmt/30.0;
       case Years:
              return tmt/365.0;
       default:
              return cal.tradingDays(t,expiry_date);
       }
}