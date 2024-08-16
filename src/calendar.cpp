#include "../headers/calendar.h"

void Calendar::loadHolidaysFromCsv(std::string filename){
       rapidcsv::Document doc(filename);
       std::vector<std::string> col = doc.GetColumn<std::string>("Date");
       for (std::string str : col){
              Date d = Date::create(str);
              //d.print(true);
              holidays.push_back(d);
       }
}

// We assume p2 > p1
int Calendar::tradingDays(const Date& p1, const Date& p2) const{
       Date p = p1; //ugly ugly ugly
       if (p1 == p2){
              std::cout << "The are the same date!" << std::endl;
              return 0;
       }else if (p1 > p2){
              throw std::runtime_error("The time to maturity is negative!");
       }

       int counter=1;
       for (;p<p2;++p){
              if (isTradingDay(p)){ counter++; }
       }

       // This must be fixed better, currently sucks
       if (!isTradingDay(p2)){ counter--; }

       return counter;
}
