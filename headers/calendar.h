#ifndef __CppOptions__Calendar__
#define __CppOptions__Calendar__

/*
       This class build a bit more structure around the Holidays object,
       which is basically a vector of Dates. It enables to count trading days
*/

#include "Date.h"
#include "rapidcsv.h"

class Calendar{
private:
       std::vector<Date> holidays;
public:
       //--------------------
       //Configuration methods
       void loadHolidaysFromCsv(std::string filename);

       //--------------------
       //Getters and Setters
       void setHolidays(const std::vector<Date>& p){ holidays = p; }
       std::vector<Date> getHolidays() const{ return holidays; }

       //--------------------
       //Binary Checking methods
       bool isHoliday(const Date& p){
              return std::find(holidays.begin(), holidays.end(), p)!=holidays.end();
       }

       bool isTradingDay(const Date& p){
              if (p.isWeekend() || isHoliday(p)){
                     return false;
              }else{
                     return true;
              }
       }

       //---------------------
       //Methods for computations
       int tradingDays(const Date& p1, const Date& p2);
};

#endif