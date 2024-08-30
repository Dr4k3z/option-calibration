#include "../headers/options.h"

float EuropeanOption::time2maturity(Units unit) const{
       int tmt = cal.tradingDays(value_date, expiry_date);
       switch (unit){
       case Days:
              return tmt;
       case Months:
              return tmt/30.0;
       case Years:
              return tmt/365.0;
       default:
              return cal.tradingDays(value_date, expiry_date);
       }
}