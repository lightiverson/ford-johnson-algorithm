#ifndef WALLET_HPP
#define WALLET_HPP

#include "Date.hpp"
#include "Value.hpp"
#include "BitcoinExchange.hpp"

class Wallet
{
private:
    const BitcoinExchange &m_bitcoinexchange;
    Date m_date{};
    Value m_value{};

public:
    /* Default constructor */
    Wallet(void) = delete;
    /* Parameterized constructor */
    Wallet(const BitcoinExchange &db, std::string line);
    /* Copy constructor */
    Wallet(const Wallet &source);
    /* Copy assignment operator overload */
    Wallet &operator=(const Wallet &source) = delete;
    /* Destructor */
    ~Wallet(void);

    void putBtcInEur(void);
};

#endif