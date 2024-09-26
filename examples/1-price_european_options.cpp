#include <iostream>
#include "../headers/date.h"
#include "../headers/calendar.h"
#include "../headers/options.h"
#include "../headers/pricing_models.h"

/*
       Price a European Options with the following characteristics:
       strike = 1 euro
       value date = 2024-02-15
       maturity = 3 months
       volatility = 0.22
       rate = 0.03
       dividen = 0.06  how do you quote options with dividend?
       settlement = physical delivery
       n contracts = 1 mln
       underlying = 1 euro
*/

int main(){
       // Create a Calendar object to specify holidays. We use 2024 US financial holidays
       Calendar cal = Calendar::createFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");

       // Set call value and expiry date
       Date valueDate = Date::create(2024,2,15);
       Date expiryDate = Date::create(2024,5,15);

       // Create european options
       EuropeanCallOption call(1,expiryDate,cal); call.setValueDate(valueDate);
       EuropeanPutOption put(1,expiryDate,cal); put.setValueDate(valueDate);

       // Price using different methods
       std::cout << "Call BS = " << BlackScholes::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Put BS = " << BlackScholes::price(put,1,0.22,0.03) << std::endl;

       std::cout << "--------------------" << std::endl;

       std::cout << "Call CRR = " << CRR::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Put CRR = " << CRR::price(put,1,0.22,0.03) << std::endl;

       std::cout << "--------------------" << std::endl;

       std::cout << "Call MC = " << MC::price(call,1,0.22,0.03) << std::endl;
       std::cout << "Put MC = " << MC::price(put,1,0.22,0.03) << std::endl;
}