#include <algorithm>
#include <chrono>
#include <ctime>

typedef std::chrono::steady_clock::time_point Date;

class EuropeanOption{
protected:
       const float strike;
       const Date expiry_date;
public:
       // Rule of Three: Constructor, Copy Constructor and Copy Assignment Operator
       EuropeanOption(float strike, Date expiry_date) : strike(strike), expiry_date(expiry_date) {}
       EuropeanOption(const EuropeanOption& p);
       EuropeanOption &operator=(const EuropeanOption& p);

       virtual float payoff(float stock) const=0;

       /*std::string timeToMatury() const {
              Date today = std::chrono::system_clock::now();
              auto duration = std::chrono::duration_cast<std::chrono::>(expiry_date-today).count
       }*/
};

class EuropeanCallOption : public EuropeanOption{
public:
       EuropeanCallOption(float strike, Date expiry_date) : EuropeanOption(strike,expiry_date) {}
       float payoff(float stock) const{
              return std::max({stock-strike,0.0f});
       }
};

class EuropeanPutOption : public EuropeanOption{
public:
       EuropeanPutOption(float strike, Date expiry_date) : EuropeanOption(strike, expiry_date) {}
       float payoff(float stock) const{
              return std::max({strike-stock,0.0f});
       }
};