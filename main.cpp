#include <iostream>
//#include "headers/options.h"
#include "headers/date.h"

int main(){
       /*EuropeanCallOption call(100.0,0.1);
       EuropeanPutOption put(100.0,0.1);
       std::cout << call.payoff(110.0) << std::endl;
       std::cout << put.payoff(80) << std::endl;*/
       Date day1(2024,8,13);
       Date day2(2024,7,15);

       day1.print(true);
       (++day1).print(true);
       day2.print(true);

       /*day1.print(true);
       day2.print(true);
       ++day1;
       day1.print();
       day1.print(true); */ 
}