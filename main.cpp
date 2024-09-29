#include <iostream>
#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"
#include "headers/pricing_models.h"
#include "headers/greeks.h"

// S_0: 100
// vol: 0.22
// rate: 0.05
// Expiry date: 2024-12-15

int main(){
       /*
              Building a Delta-Hedged portfolio
       */
       
       Calendar cal = Calendar::createFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");
       Date expiryDate = Date::create(2024,12,31);

       float S = 100; // stock
       float vol = 0.22; // volatility
       float rate = 0.05; // rate

       EuropeanCallOption call(100,expiryDate,cal); // call
       EuropeanPutOption put(100,expiryDate,cal); // put
       float delta = Greeks::delta(put, S, vol, rate);

       // Stock price fluctuates by 5%
       float S_down = 0.95*S;
       float S_up = 1.05*S;

       /* NEGATIVE PUT PRICE! WTF?!!! */
       std::cout << "call: " << BlackScholes::price(call, 95, vol, rate, 0.178) << std::endl;
       std::cout << "put: " << BlackScholes::price(put, 95, vol, rate, 0.178) << std::endl;

       std::cout << "---------------Standard Portfolio-----------\n";
       std::cout << "Initial value of the portfolio: " << S << std::endl;
       std::cout << "Down portfolio value: " << S_down << std::endl;
       std::cout << "Up portfolio value: " << S_up << std::endl;
       
       std::cout << "---------------Delta Hedged-----------------\n";
       std::cout << "Initial value of the portfolio: " << S+delta*BlackScholes::price(put,S,0.22,0.05) << std::endl;
       std::cout << "Down portfolio value: " << BlackScholes::price(put,S_down,vol,rate) << std::endl;
       std::cout << "Up portfolio value: " << BlackScholes::price(put,S_up,vol,rate) << std::endl;
       return 0;
}