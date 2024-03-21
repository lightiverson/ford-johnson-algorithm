#include "Value.hpp"

/* Default constructor */
Value::Value(void)
{
}

/* Parameterized constructor */
Value::Value(std::string &value) : m_value(value)
{
    std::size_t pos{};

    try
    {
        m_valueFloat = std::stof(m_value, &pos);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::runtime_error("Error: invalid value");
    }
    catch (const std::out_of_range &e)
    {
        throw std::runtime_error("Error: out of range");
    }
    if (pos != m_value.length())
        throw std::runtime_error("Error: invalid value");
    if (m_valueFloat < 0)
        throw std::runtime_error("Error: not a positive number");
    if (m_valueFloat > 1000)
        throw std::runtime_error("Error: too large a number");
}

/* Copy constructor */
Value::Value(const Value &source) : m_value(source.m_value), m_valueFloat(source.m_valueFloat)
{
}

/* Copy assignment operator overload */
Value &Value::operator=(const Value &source)
{
    if (this == &source)
        return *this;

    m_value = source.m_value;
    m_valueFloat = source.m_valueFloat;

    return *this;
}

/* Destructor */
Value::~Value(void)
{
}

float Value::getValue(void)
{
    return m_valueFloat;
}