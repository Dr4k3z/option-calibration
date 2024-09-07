#include "../headers/pde.h"
#include <math.h>
#include <iostream>

// PDE coefficients
float BlackScholesPDE::diff_coeff(float t, float x) const{
       return 0.5*pow(volatility,2)*pow(x,2);
}

float BlackScholesPDE::adv_coeff(float t, float x) const{
       return rate*x;
}

float BlackScholesPDE::react_coeff(float t, float x) const{
       return -rate;
}

float BlackScholesPDE::source_coeff(float t, float x) const{
       return 0.0;
}

// Initial and boundary conditions
float BlackScholesPDE::initial_condition(float t) const{
       return this->option->payoff(t);
}

float BlackScholesPDE::boundary_left(float t, float x) const{
/*
       When the stock is null, the value of the option is either
       zero for a call or K for a put, with K being the strike
*/
       return option->payoff(0);
}

float BlackScholesPDE::boundary_right(float t, float x) const{
/*
       Approximation via Put-Call parity for very high values of
       the underlying. If the options is indeed a put, the value
       is just approximated to zero
*/
       if (const EuropeanCallOption* callOption = dynamic_cast<const EuropeanCallOption*>(this->option)){
              std::cout << "this is a call" << std::endl;
              return x - this->option->getStrike()*exp(-rate*(this->option->time2maturity()-t));
       }else if (const EuropeanPutOption* putOption = dynamic_cast<const EuropeanPutOption*>(this->option)){
              std::cout << "this is a put" << std::endl;
              return 0;
       }else{
              throw std::runtime_error("price function unknown input parameters: only pass EuropeanOption objects");
       }
}
