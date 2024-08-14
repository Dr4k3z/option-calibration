#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"

int main(){
       /*EuropeanCallOption call(100.0,0.1);
       EuropeanPutOption put(100.0,0.1);
       std::cout << call.payoff(110.0) << std::endl;
       std::cout << put.payoff(80) << std::endl;*/
       Calendar cal; cal.loadHolidaysFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");

       Date day1 = Date::create(2024,1,1);
       Date day2 = Date::create(2024,12,31);
       
       EuropeanCallOption call(100.0,day2,cal);

       std::cout << call.time2maturity(Days) << std::endl;
       
       /*day1.print(true);
       day2.print(true);
       ++day1;
       day1.print();
       day1.print(true); */ 
}