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
    Wallet(const BitcoinExchange &db, std::string line);
    void putBtcInEur(void);
};

#endif