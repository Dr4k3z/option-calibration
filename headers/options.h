#include <algorithm>

class EuropeanOption{
protected:
       const float strike;
       const float tmt;
public:
       // Rule of Three: Constructor, Copy Constructor and Copy Assignment Operator
       EuropeanOption(float strike,float tmt) : strike(strike), tmt(tmt) {}
       EuropeanOption(const EuropeanOption& p);
       EuropeanOption &operator=(const EuropeanOption& p);
       virtual float payoff(float stock) const=0;
};

class EuropeanCallOption : public EuropeanOption{
public:
       EuropeanCallOption(float strike, float tmt) : EuropeanOption(strike,tmt) {}
       float payoff(float stock) const{
              return std::max({stock-strike,0.0f});
       }
};

class EuropeanPutOption : public EuropeanOption{
public:
       EuropeanPutOption(float strike, float tmt) : EuropeanOption(strike,tmt) {}
       float payoff(float stock) const{
              return std::max({strike-stock,0.0f});
       }
};