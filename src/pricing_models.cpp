#include "../headers/pricing_models.h"
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

float normalCDF(float value, float mean=0, float std = 1){
       // Normal Distribution
       return 0.5 * (1.0 + std::erf((value - mean) / (std * std::sqrt(2.0))));
}

std::vector<float> linspace(float start, float end, float step = 1.0){
       std::vector<float> seq;

       if (start < end && step > 0){
              for (float i = start; i <= end; i += step){
                     seq.push_back(i);
              }
       }else if (start > end && step < 0){
              for (float i = start; i >= end; i += step){
                     seq.push_back(i);
              }
       }else{
              throw std::runtime_error("Something went wrong in linspace function");
       }

       return seq;
}

std::vector<float> cumsum(const std::vector<float>& vec) {
       // Function to compute the cumulative sum
       std::vector<float> result(vec.size());
       std::partial_sum(vec.begin(), vec.end(), result.begin());
       return result;
}

// I need a LINALG library no cap
float vectorCumSum(const std::vector<float>& v1, const std::vector<float>& v2){
       if (v1.size() != v2.size()){
              throw std::runtime_error("Vectors must be of the same size");
       }

       size_t n = v1.size();
       float sum = 0.0;
       for (size_t i=0; i<n;i++){
              sum += v1[i]+v2[i];
       }
       return sum;
}

template<typename T>
void print(std::vector<T> v){
       for (auto c : v){
              std::cout << c << " ";
       }
       std::cout << std::endl;
}

template<typename T>
float bisectionMethod(std::function<T(T)> func, T x0, T xmax, T tol){
       // Bisection method to find the root of a function
       unsigned long maxIter = 10*9;       

       T fa = func(x0);
       T fb = func(xmax);

       // I dont like this way of handling errors and warnings
       if (fa*fb > 0){
              std::cout << "Warning! The function has the same sign at the endpoints of the interval\n";
              return 0;
       }

       //assert(fa*fb < 0 && "The function has the same sign at the endpoints of the interval");

       T c = x0;
       unsigned long iter = 0;
       while ((xmax-x0) > tol && iter < maxIter){
              c = (x0+xmax)/2.0;

              if (std::fabs(func(c)) < tol){
                     break;
              }
              
              if (func(x0)*func(c) < 0){
                     xmax = c;
              }else{
                     x0 = c;
              }
              iter++;
       }

       //std::cout << "Bisection method converged in " << iter << " iterations\n";

       if (iter >= maxIter){
              throw warning("Bisection method did not converge");
       }
       return c;
}

//--------------------
//BlackScholes namespace
float BlackScholes::price(const Option& option, float S, float sigma, float rate, float tmt){
       float K = option.getStrike();

       if (tmt == 0.0){
              tmt = option.time2maturity();
       }

       float d1 = (std::log(S/K)+(rate+0.5*sigma*sigma)*tmt)/(sigma*std::sqrt(tmt));
       float d2 = d1-sigma*std::sqrt(tmt);

       // Honestly I just wanted to play with dynamic casting, It could've been done way easier
       if (const EuropeanCallOption* callOption = dynamic_cast<const EuropeanCallOption*>(&option)){
              //std::cout << "this is a call" << std::endl;
              return normalCDF(d1)*S-normalCDF(d2)*K*exp(-rate*tmt);       
       }else if (const EuropeanPutOption* callOption = dynamic_cast<const EuropeanPutOption*>(&option)){
              //std::cout << "this is a put" << std::endl;
              return K*std::exp(-rate*tmt)*normalCDF(-d2) - S*normalCDF(-d1);
       }else{
              throw std::runtime_error("price function unknown input parameters: only pass EuropeanOption objects");
       }
}

float BlackScholes::impliedVolatility(const Option& option, float S, float rate, float tmt, float marketPrice){
       if (marketPrice == 0){
              marketPrice = option.getPrice();
       }

       auto func = [&option,S,tmt,rate,marketPrice](float x){return BlackScholes::price(option,S,x,rate,tmt)-marketPrice;};
       float impliedVol = bisectionMethod<float>(func,0.0,1.0,0.0001);
       return impliedVol;
}

std::vector<float> BlackScholes::calibrate(const OptionChain* chain, float S, float rate){
       std::vector<float> impliedVol;
       float tmt = chain->getTime2Maturity();

       for (const auto& option : chain->getOptions()){
              float marketPrice = option->getPrice();



              float implied = BlackScholes::impliedVolatility(*option,S,rate,tmt,marketPrice);
              impliedVol.push_back(implied);
       }
       return impliedVol;
}

//--------------------
//Black76 namespace
float Black76::price(const EuropeanOption& option, float S, float sigma, float rate){
       float tmt = option.time2maturity();
       float K = option.getStrike();

       float d1 = (std::log(S/K)+(0.5*sigma*sigma)*tmt)/(sigma*std::sqrt(tmt));
       float d2 = d1-sigma*std::sqrt(tmt);

       if (const EuropeanCallOption* callOption = dynamic_cast<const EuropeanCallOption*>(&option)){
              //std::cout << "this is a call" << std::endl;
              return std::exp(-rate*tmt)*(normalCDF(d1)*S-normalCDF(d2)*K);       
       }else if (const EuropeanPutOption* callOption = dynamic_cast<const EuropeanPutOption*>(&option)){
              //std::cout << "this is a put" << std::endl;
              return std::exp(-rate*tmt)*(K*normalCDF(-d2) - S*normalCDF(-d1));
       }else{
              throw std::runtime_error("price function unknown input parameters: only pass EuropeanOption objects");
       }
}

//--------------------
//CRR namespace
int CRR::N = 100;

float CRR::price(const EuropeanOption& option, float S, float sigma, float rate, float tmt){
       float strike = option.getStrike();

       if (tmt == 0.0){
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
       float impliedVol = bisectionMethod<float>(func,0.0,1.0,0.0001);
       return impliedVol;
}

//--------------------
//MC namespace

int MC::N = 100;

float MC::price(const EuropeanOption& option, float S, float tmt, float sigma, float rate){
       float strike = option.getStrike();

       if (tmt == 0.0){
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
       float impliedVol = bisectionMethod<float>(func,0.0,1.0,0.0001);
       return impliedVol;
}