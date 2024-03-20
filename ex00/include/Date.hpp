#ifndef DATE_HPP
#define DATE_HPP

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <ctime>
#include <sstream>
#include <regex>
#include "iomanip"

class Date
{
private:
    std::string m_date{};
    std::string m_year{};
    std::string m_month{};
    std::string m_day{};

    bool isLeapYear(int year) const;
    bool isValidDateFormat(const std::string &date) const;
    bool isValidDateRange(const std::string &date) const;
    int yearMonthDaySet(const std::string &date) const;

public:
    Date(void);
    Date(std::string &date);
    const std::string &getDate(void) const;
};

#endif