#include "BitcoinExchange.hpp"

/* Default constructor */
BitcoinExchange::BitcoinExchange(void)
{
    m_bitcoinexchange = dataParse();
}

/* Copy constructor */
BitcoinExchange::BitcoinExchange(const BitcoinExchange &source)
{
    m_bitcoinexchange = source.m_bitcoinexchange;
}

/* Copy assignment operator overload */
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &source)
{
    if (this == &source)
        return *this;

    m_bitcoinexchange = source.m_bitcoinexchange;

    return *this;
}

/* Destructor */
BitcoinExchange::~BitcoinExchange(void)
{
    ;
}

void BitcoinExchange::mapPrint(const std::string &comment, const std::map<std::string, float> &m)
{
    std::cout << comment;

    for (const auto &[key, value] : m)
        std::cout << '[' << key << "] = " << value << "\n";
}

std::map<std::string, float>::value_type BitcoinExchange::dataLineParse(const std::string &line) const
{
    float floatValue{-1};
    size_t commaPos = line.find(',');
    std::string datePart = line.substr(0, commaPos);
    std::string floatPart = line.substr(commaPos + 1);

    try
    {
        floatValue = std::stof(floatPart);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: database => |" << line << "|\n";
    }

    return std::map<std::string, float>::value_type(datePart, floatValue);
}

std::map<std::string, float> BitcoinExchange::dataParse(void) const
{
    std::ifstream inf{"data.csv"};
    std::map<std::string, float> data{};

    if (!inf)
        throw std::runtime_error("Error: could not open data.csv file.!\n");

    while (!inf.eof())
    {
        std::string strInput{};
        std::getline(inf, strInput);
        std::map<std::string, float>::value_type vt = dataLineParse(strInput);
        if (vt.second == -1)
            continue;
        data.insert(vt);
    }

    return data;
}

std::map<std::string, float> BitcoinExchange::getBitcoinexchange(void) const
{
    return m_bitcoinexchange;
}