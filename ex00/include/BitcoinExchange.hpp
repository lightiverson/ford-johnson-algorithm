#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>

class BitcoinExchange
{
private:
    std::map<std::string, float> m_bitcoinexchange{};

    static void mapPrint(const std::string &comment, const std::map<std::string, float> &m);
    std::map<std::string, float>::value_type dataLineParse(const std::string &line) const;
    std::map<std::string, float> dataParse(void) const;

public:
    /* Default constructor */
    BitcoinExchange(void);
    /* Copy constructor */
    BitcoinExchange(const BitcoinExchange &source);
    /* Copy assignment operator overload */
    BitcoinExchange &operator=(const BitcoinExchange &source);
    /* Destructor */
    ~BitcoinExchange(void);

    std::map<std::string, float> getBitcoinexchange(void) const;
};

#endif