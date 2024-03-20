#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <stdexcept>

class Value
{
private:
    std::string m_value{};
    float m_valueFloat{};

public:
    Value(void);
    Value(std::string &value);
    float getValue(void);
};

#endif
