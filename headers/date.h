#ifndef __CppOptions__Date__
#define __CppOptions__Date__
#include <string>
#include <iostream>
#include <vector>

enum WeekDay{
       Sunday,
       Monday,
       Tuesday,
       Wednesday,
       Thursday,
       Friday,
       Saturday,
       UNKNOWN
};

enum Month{
       January, 
       Febraury,
       March,
       April, 
       May,
       June,
       July,
       August, 
       September,
       October,
       November,
       December
};

class Calendar; //forward declaration

class Date{
private:
       int year;
       int month;
       int day;
       WeekDay weekday;

       void initializeWeekDay();
public:
       // --------------------
       // Constructors
       Date(int year, int month, int day) : year(year), month(month), day(day), weekday(UNKNOWN) {}
       Date(const Date& p) : year(p.year), month(p.month), day(p.day), weekday(p.weekday) {}
       Date &operator=(const Date& p);
       Date(std::string datetime);

       bool isLeapYear();

       //--------------------
       // Methods for visualization
       std::string month_name() const;
       std::string day_name() const;
       void print(bool text = false);

       //--------------------
       // Methods for computation
       static int diff(const Date& p1, const Date& p2);
       int dayDifference(const Date& p, bool trading = true);
       void add(int days);
       void subtract(int days);

       //--------------------
       // Methods for importing and format change

       //--------------------
       // Operator overloading
       bool operator==(const Date& p) const;
       Date &operator+(int days);
       Date &operator++();
       Date &operator-(int days);
       Date &operator--();
       bool operator>(const Date& p) const;
       bool operator<(const Date& p) const;

       ~Date() {}
};

#endif