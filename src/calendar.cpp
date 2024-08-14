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

// Figure out a way to handle negative trading days,
// I mean return a minus or something
int Calendar::tradingDays(const Date& p1, const Date& p2) const{
       Date p = Date::max(p1,p2);
       Date q = Date::min(p1,p2);
       if (p == q){
              std::cout << "The are the same date!" << std::endl;
              return 0;
       }

       int counter=1;
       for (;q<p;++q){
              if (isTradingDay(q)){ counter++; }
       }
       return counter;
}
