#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"
#include "headers/pricing_models.h"

int main(){
       /*EuropeanCallOption call(100.0,0.1);
       EuropeanPutOption put(100.0,0.1);
       std::cout << call.payoff(110.0) << std::endl;
       std::cout << put.payoff(80) << std::endl;*/
       Date expiryDate = Date::create(2024,12,31);
       Calendar cal; cal.loadHolidaysFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");

       EuropeanCallOption call(100,expiryDate,cal);
       EuropeanPutOption put(100,expiryDate,cal);

       std::cout << "Call = " << BS::price(call,100,0.2,0.05) << std::endl;
       std::cout << "Put = " << BS::price(put,100,0.2,0.05) << std::endl;

       /*day1.print(true);
       day2.print(true);
       ++day1;
       day1.print();
       day1.print(true); */ 
}