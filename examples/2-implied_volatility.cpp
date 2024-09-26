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
       Date expiryDate = Date::create(2024,12,15);

       EuropeanCallOption call(1,expiryDate,cal); // if value data not set, it is set to today

       float marketPrice = 0.0389972;

       // Calculate implied volatility and calibrate your model
       std::cout << "ImpliedVol BS = " << BlackScholes::impliedVolatility(call,1,0.03,call.time2maturity(),marketPrice) << std::endl;
       std::cout << "ImpliedVol CRR = " << CRR::impliedVolatility(call,1,0.03,call.time2maturity(),marketPrice) << std::endl;
}