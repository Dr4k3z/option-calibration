#ifndef __PDE__H
#define __PDE__H

#include <memory>
#include "options.h"

class AdvDiffReactEquation{
public:
       // PDE coefficients
       virtual float diff_coeff(float t, float x) const = 0;
       virtual float adv_coeff(float t, float x) const = 0;
       virtual float react_coeff(float t, float x) const = 0;
       virtual float source_coeff(float t, float x) const = 0;

       // Initial and boundary conditions
       virtual float initial_condition(float x) const = 0;
       virtual float boundary_left(float t, float x) const = 0;
       virtual float boundary_right(float t, float x) const = 0;
};

class BlackScholesPDE : public AdvDiffReactEquation{
private:
       const EuropeanOption* option;
       float volatility;
       float rate;

       // Constructor
       BlackScholesPDE(const EuropeanOption* option, float volatility, float rate) : option(option), volatility(volatility), rate(rate) {}
public:
       // Factory methods
       /*static std::unique_ptr<BlackScholesPDE> create(const EuropeanOption* option, float volatility = 0, float rate = 0){
              // This syntax looks quite shite 
              return std::unique_ptr<BlackScholesPDE>(new BlackScholesPDE(option, volatility, rate));
       }*/
       static BlackScholesPDE* create(const EuropeanOption* option, float volatility = 0, float rate = 0){
              return new BlackScholesPDE(option, volatility, rate);
       }

       // Getters
       inline float getVolatility(){ return volatility; }
       inline float getRate(){ return rate; }

       // Setters
       inline void setVolatility(float vol){ volatility = vol; }
       inline void setRate(float r){ rate = r;}

       // PDE coefficients
       float diff_coeff(float t, float x) const override;
       float adv_coeff(float t, float x) const override;
       float react_coeff(float t, float x) const override;
       float source_coeff(float t, float x) const override;

       // Initial and boundary conditions
       float initial_condition(float x) const override;
       float boundary_left(float t, float x) const override;
       float boundary_right(float t, float x) const override;
};

#endif