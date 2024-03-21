#include "Date.hpp"

/* Default constructor */
Date::Date(void)
{
}

/* Parameterized constructor */
Date::Date(std::string &date) : m_date(date)
{
    if (!isValidDateFormat(m_date))
        throw std::runtime_error("Error: bad input => |" + m_date + "|");

    if (!isValidDateRange(m_date))
        throw std::runtime_error("Error: bad input => |" + m_date + "|");
}

/* Copy constructor */
Date::Date(const Date &source) : m_date(source.m_date), m_year(source.m_year), m_month(source.m_month), m_day(source.m_day)
{
}

/* Copy assignment operator overload */
Date &Date::operator=(const Date &source)
{
    if (this == &source)
        return *this;

    m_date = source.m_date;
    m_year = source.m_year;
    m_month = source.m_month;
    m_day = source.m_day;

    return *this;
}

/* Destructor */
Date::~Date(void)
{
}

bool Date::isValidDateFormat(const std::string &date) const
{
    std::regex iso8601Pattern(R"(^\d{4}-\d{2}-\d{2}$)");

    if (!std::regex_match(date, iso8601Pattern))
        return false;

    return true;
}

bool Date::isLeapYear(int year) const
{
    if (year % 4 != 0)
        return false; /* Not divisible by 4 is not a leap year */

    if (year % 100 != 0)
        return true; /* Divisible by 4, and not by 100 is a leap year */

    if (year % 400 != 0)
        return false; /* Divisible by 4, and by 100, but not by 400 is not a leap year */

    return true; /* Divisible by 4, and by 100, and by 400 is a leap year */
}

bool Date::isValidDateRange(const std::string &date) const
{
    std::tm t = {};
    std::istringstream ss(date);

    ss >> std::get_time(&t, "%Y-%m-%d");
    if (ss.fail())
        return false;

    if (t.tm_mon < 0 || t.tm_mon > 11) /* Check for valid month */
        return false;

    static const int daysInMonth[] = {31, 28 + isLeapYear(t.tm_year + 1900), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (t.tm_mday < 1 || t.tm_mday > daysInMonth[t.tm_mon]) /* Check for valid day */
        return false;

    return true;
}

const std::string &Date::getDate(void) const
{
    return m_date;
}