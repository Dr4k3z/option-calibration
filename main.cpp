#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"
//#include "headers/pricing_models.h"
#include "headers/black_scholes.h"
#include <algorithm>
#include <chrono>

template<typename T>
void writeCsv(const std::string& filename, const std::vector<T>& strikes, const std::vector<T>& data){
       std::ofstream file;
       file.open(filename);

       size_t n = strikes.size();
       assert(n == data.size() && "Warning! Strikes and data have different sizes");

       file << "STRIKE" << "," << "DATA" << "\n";

       for (int i=0;i<n;i++){
              file << strikes[i] << "," << data[i] << "\n";
       }

       file.close();
}

float measure_time_execution(const std::function<void()>& func){
       const auto start = std::chrono::high_resolution_clock::now();
       func();
       const auto end = std::chrono::high_resolution_clock::now();
       const std::chrono::duration<float> duration = end-start;
       return duration.count();
}

void func(){
       // Create a Calendar object to specify holidays. We use 2024 US financial holidays
       //Calendar cal = Calendar::createFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");
       const Calendar cal = Calendar::noHolidays();

       const Date valueDate = Date::create(2024,7,31);
       const Date expiryDate = Date::create(2024,8,1);

       const OptionChain* chain = OptionChain::createFromCsv(valueDate, expiryDate, cal, European, Put, "../resources/NIFTY_put_data_1_aug_2024.csv");

       constexpr float S = 24950.0; // NIFTY value at the 2024-7-31
       constexpr float rate = 0.1; // Risk-free rate

       const std::vector<float> impliedVol = BlackScholes::calibrate(chain, S, rate);
       const std::vector<float> strikes = chain->getStrikes();
       writeCsv<float>("implied_volatility.csv", strikes, impliedVol);
}

void func2() {
       // Create a Calendar object to specify holidays. We use 2024 US financial holidays
       Calendar cal = Calendar::createFromCsv("../../option-calibration/resources/us_holidays.csv");
       Date expiryDate = Date::create(2024,12,15);

       EuropeanCallOption call(1,expiryDate,cal); // if value data not set, it is set to today

       float marketPrice = BlackScholes::price(call,1,0.2,0.05);

       // Calculate implied volatility and calibrate your model
       std::cout << "ImpliedVol BS newton = " << BlackScholes::impliedVolatility(call,1,0.03,call.time2maturity(),marketPrice,NewtonRaphson) << std::endl;
       std::cout << "ImpliedVol BS bisection = " << BlackScholes::impliedVolatility(call,1,0.03,call.time2maturity(),marketPrice, BisectionMethod) << std::endl;
}

int main(){
       auto f = [](){func();};
       const auto measure = measure_time_execution(f);
       std::cout << "Execution time: " << measure << " seconds\n";
       return 0;
}