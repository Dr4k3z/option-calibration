#include "../headers/pricing_models.h"
#include "../headers/math.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>
#include <cassert>
#include <functional>
#include <fstream>

//--------------------
/*Here goes a list a various useful functions that are called throughtout
  the file. Some are called by a singular namespace, some arent. It doesnt feel
  very clean and organized, I wanna find another solution to that.*/

// thanks to @Tony the Lion from stackoverflow for this warning class
class warning : public std::exception{
public:
     warning(const std::string& msg) {}
     const char* what() { return msg.c_str(); } //message of warning
private:
     std::string msg;
};

/*class Warning{
private:
       std::string msg;
public:
       Warning(const std::string& msg) : msg(msg){}
       friend std::ofstream& operator<<(std::ofstream& os, const Warning& w){
              os << w.msg;
              return os;
       }
};*/

//--------------------
//Black76 namespace
float Black76::price(const EuropeanOption& option, float S, float sigma, float rate){
       float tmt = option.time2maturity();
       float K = option.getStrike();

       float d1 = (std::log(S/K)+(0.5*sigma*sigma)*tmt)/(sigma*std::sqrt(tmt));
       float d2 = d1-sigma*std::sqrt(tmt);

       if (const EuropeanCallOption* callOption = dynamic_cast<const EuropeanCallOption*>(&option)){
              //std::cout << "this is a call" << std::endl;
              return std::exp(-rate*tmt)*(Math::normalCDF(d1)*S-Math::normalCDF(d2)*K);       
       }else if (const EuropeanPutOption* callOption = dynamic_cast<const EuropeanPutOption*>(&option)){
              //std::cout << "this is a put" << std::endl;
              return std::exp(-rate*tmt)*(K*Math::normalCDF(-d2) - S*Math::normalCDF(-d1));
       }else{
              throw std::runtime_error("price function unknown input parameters: only pass EuropeanOption objects");
       }
}

//--------------------
//CRR namespace
int CRR::N = 100;

float CRR::price(const EuropeanOption& option, float S, float sigma, float rate, float tmt){
       float strike = option.getStrike();

       if (tmt == -1.0){
              tmt = option.time2maturity();
       }

       // edge case
       if (sigma == 0){
              return std::exp(-rate*tmt)*option.payoff(S);
       }

       float deltaT = tmt/N; //time step
       float up = std::exp(sigma*std::sqrt(deltaT)); float down = 1/up; //for a derivation of these, see Cox,Ross,Rubenstein original paper

       float q = (std::exp(rate*deltaT)-down)/(up-down); //Risk neutral measure

       std::vector<float> price(N+1);
       for (int i = 0; i <= N; i++){
              price[i] = option.payoff(S*pow(up, N-2*i));
       }

       // Code written by ChatGPT - hope it works
       for (int j = N; j >= 1; --j) {
              for (int i = 0; i < j; ++i) {
                     price[i] = exp(-rate * deltaT) * (q * price[i] + (1 - q) * price[i + 1]);
              }
       }

       return price[0];
}

float CRR::impliedVolatility(const EuropeanOption& option, float S, float rate, float tmt, float marketPrice){
       if (marketPrice == 0.0){
              marketPrice = option.getPrice();
       }
       auto func = [&option,S,tmt,rate,marketPrice](float x){return CRR::price(option,S,x,rate,tmt)-marketPrice;};
       float impliedVol = Math::bisectionMethod<float>(func,0.0,1.0,0.0001);
       return impliedVol;
}

//--------------------
//MC namespace

int MC::N = 100;

float MC::price(const EuropeanOption& option, float S, float tmt, float sigma, float rate){
       float strike = option.getStrike();

       if (tmt == -1.0){
              tmt = option.time2maturity();
       }

       // Random numbers from standard gaussian
       std::default_random_engine engine;
       std::normal_distribution<float> normalRand;

       std::vector<float> stockPrice(N);
       for (int i=0;i<N;i++){
              float g = normalRand(engine);
              stockPrice[i] = S*std::exp((rate-0.5*sigma*sigma)*tmt + sigma *std::sqrt(tmt)*g);
       }

       float mean;
       for (float s : stockPrice){
              mean += std::exp(-rate*tmt)*option.payoff(s);
       }
       mean = mean/float(N);
       return mean;
}

// this does not work, I need to find a way to make them work
float MC::impliedVolatility(const EuropeanOption& option, float S, float tmt, float rate, float marketPrice){
       if (marketPrice == 0.0){
              marketPrice = option.getPrice();
       }
       auto func = [&option,S,tmt,rate,marketPrice](float x){return MC::price(option,S,x,rate,tmt)-marketPrice;};
       float impliedVol = Math::bisectionMethod<float>(func,0.0,1.0,0.0001);
       return impliedVol;
}