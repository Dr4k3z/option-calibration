#include "Date.h"
#include "rapidcsv.h"

class Calendar{
private:
       std::vector<Date> holidays;
public:
       void setHolidays(const std::vector<Date>& p){ holidays = p; }
       std::vector<Date> getHolidays() const{ return holidays; }

       void loadHolidaysFromCsv(std::string filename){
              rapidcsv::Document doc(filename);
              std::vector<std::string> col = doc.GetColumn<std::string>("Date");
              for (std::string str : col){
                     Date d(str);
                     d.print(true);
                     holidays.push_back(d);
              }
       }

       bool isHoliday(const Date& p){
              return std::find(holidays.begin(), holidays.end(), p)!=holidays.end();
       }
};