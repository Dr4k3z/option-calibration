#include "headers/date.h"
#include "headers/calendar.h"
#include "headers/options.h"
#include "headers/pricing_models.h"
#include <chrono>

template<typename T>
void writeCsv(const std::string filename, const std::vector<T>& strikes, const std::vector<T>& data){
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
float measure_time_execution(std::function<void()> func){
       auto start = std::chrono::high_resolution_clock::now();
       func();
       auto end = std::chrono::high_resolution_clock::now();
       std::chrono::duration<float> duration = end-start;
       return duration.count();
}

void func(){
       // Create a Calendar object to specify holidays. We use 2024 US financial holidays
       //Calendar cal = Calendar::createFromCsv("/mnt/c/Users/matte/Documents/option-calibration/resources/us_holidays.csv");
       Calendar cal = Calendar::noHolidays();

       Date valueDate = Date::create(2024,7,31);
       Date expiryDate = Date::create(2024,8,1);
       
       OptionChain* chain = OptionChain::createFromCsv(valueDate, expiryDate, cal, European, Put, "/mnt/c/Users/matte/Documents/option-calibration/resources/NIFTY_put_data_1_aug_2024.csv");

       float S = 24950.0; // NIFTY value at the 2024-7-31
       float rate = 0.1; // Risk-free rate

       std::vector<float> impliedVol = BlackScholes::calibrate(chain, S, rate);
       std::vector<float> strikes = chain->getStrikes();
       writeCsv<float>("implied_volatility.csv", strikes, impliedVol);
}

int main(){
       auto f = [](){func();};
       auto measure = measure_time_execution(f);
       std::cout << "Execution time: " << measure << " seconds\n";
       return 0;
}