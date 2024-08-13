#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"
#include "headers/calendar.h"

int main(){
       /*EuropeanCallOption call(100.0,0.1);
       EuropeanPutOption put(100.0,0.1);
       std::cout << call.payoff(110.0) << std::endl;
       std::cout << put.payoff(80) << std::endl;*/
       Calendar cal; cal.loadHolidaysFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");

       cal.getHolidays();

       Date day1(2024,8,13);
       Date day2(2024,7,15);
       Date day3(2024,12,25);

       std::cout << cal.isHoliday(day1) << std::endl;
       std::cout << cal.isHoliday(day2) << std::endl;
       std::cout << cal.isHoliday(day3) << std::endl;
       /*day1.print(true);
       day2.print(true);
       ++day1;
       day1.print();
       day1.print(true); */ 
}