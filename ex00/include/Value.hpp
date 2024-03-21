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
    /* Default constructor */
    Value(void);
    /* Parameterized constructor */
    Value(std::string &value);
    /* Copy constructor */
    Value(const Value &source);
    /* Copy assignment operator overload */
    Value &operator=(const Value &source);
    /* Destructor */
    ~Value(void);

    float getValue(void);
};

#endif
