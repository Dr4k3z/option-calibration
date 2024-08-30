#include "../headers/pricing_models.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>
#include <cassert>

//--------------------
/*Here goes a list a various useful functions that are called throughtout
  the file. Some are called by a singular namespace, some arent. It doesnt feel
  very clean and organized, I wanna find another solution to that.*/

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

//--------------------
//BlackScholes namespace
float BlackScholes::price(const EuropeanOption& option, float S, float sigma, float rate){
       /*
              UNITS OF TIME MUST BE CONSISTENT, THINK OF SOMEWAY TO ENFORCE THAT
       */
       
       float tmt = option.time2maturity();
       float K = option.getStrike();

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

float BlackScholes::price(const EuropeanOption& option, float S, float tmt, float sigma, float rate){
       float K = option.getStrike();

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
/*
float CRR::price(const EuropeanOption& option, float S, float sigma, float rate){
       I found this algorithm here: 
       Nine Ways to Implement the Binomial Method for
       Option Valuation in MATLAB - Desmond J. Higham
       I'm not really sure what's going on 
       

       float K = option.getStrike();
       float deltaT = option.time2maturity()/CRR::N;

       std::cout << option.time2maturity() << std::endl;

       // Cox-Ross-Rubenstein Model assumptions
       float up = std::exp(sigma*deltaT); float down = 1/up;
       float q = (std::exp(rate*deltaT)-down)/(up-down); //risk neutral probability

       std::cout << "deltaT: " << deltaT << std::endl;
       std::cout << "up: " << up << std::endl;
       std::cout << "down: " << down << std::endl;
       std::cout << "risk-neutral: " << q << std::endl;

       int z = std::max(1, std::min(CRR::N + 1, static_cast<int>(std::floor(std::log((K * up) / (S * std::pow(down, N + 1))) / std::log(up / down)))));

       // Calculate W
       std::vector<float> W(z);
       for (int i = 0; i < z; ++i) {
              W[i] = K - S * std::pow(down, CRR::N - i) * std::pow(up, i);
       }

       // Calculate tmp1
       std::vector<float> seq1 = linspace(1, CRR::N - z + 2);
       std::vector<float> log_seq1(seq1.size());
       for (size_t i = 0; i < seq1.size(); ++i) {
              log_seq1[i] = std::log(seq1[i]);
       }

       std::vector<float> seq2 = linspace(1, z - 1);
       std::vector<float> log_seq2(seq2.size());
       for (size_t i = 0; i < seq2.size(); ++i) {
              log_seq2[i] = std::log(seq2[i]);
       }

       std::vector<float> tmp1 = cumsum(log_seq1);
       std::vector<float> tmp_sub = cumsum(log_seq2);

       for (size_t i = 0; i < tmp1.size(); ++i) {
              tmp1[i] -= (i < tmp_sub.size() ? tmp_sub[i] : 0);
       }

       // Calculate tmp2
       std::vector<float> tmp3 = linspace(0, z - 1);
       std::vector<float> tmp4 = linspace(CRR::N, CRR::N - z + 1, -1);

       std::vector<float> tmp2(z);

       for (int i = 0; i < z; ++i) {
              std::cout << tmp1[i] << " " << tmp3[i] << " " << tmp4[i] << std::endl;
              tmp2[i] = tmp1[i] + std::log(1-q) * tmp3[i] + std::log(q) * tmp4[i]; //this line doesn't work
       }

       float value = 0.0;
       for (int i = 0; i < z; ++i) {
              value += std::exp(tmp2[i]) * W[i];
              std::cout << i << " " << W[i] << " " << tmp2[i] << " " << value << std::endl;
       }


       value *= std::exp(-rate * option.time2maturity());
       return value;
}*/

float CRR::price(const EuropeanOption& option, float S, float sigma, float rate){
       float strike = option.getStrike();
       float tmt = option.time2maturity();

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


//--------------------
//MC namespace

// put price is way off

int MC::N = 100;
float MC::price(const EuropeanOption& option, float S, float sigma, float rate){
       float strike = option.getStrike();
       float tmt = option.time2maturity();
              
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