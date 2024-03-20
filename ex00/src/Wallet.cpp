#include "Wallet.hpp"

Wallet::Wallet(const BitcoinExchange &db, std::string line) : m_bitcoinexchange(db)
{
    size_t separatorPos = line.find(" | ");
    if (separatorPos == std::string::npos)
        throw std::runtime_error("Error: bad input => |" + line + "|");

    std::string datePart = line.substr(0, separatorPos);
    m_date = Date{datePart};

    std::string floatPart = line.substr(separatorPos + 3);
    m_value = Value(floatPart);
}

void Wallet::putBtcInEur(void)
{
    const std::string &date = m_date.getDate();
    const float &value = m_value.getValue();
    const std::map<std::string, float> &bitcoinexchange = m_bitcoinexchange.getBitcoinexchange();
    float lastSmallerElement{};
    float y{};

    auto it = bitcoinexchange.find(date);
    if (it != bitcoinexchange.end())
        y = it->second * value;
    else
    {
        for (const auto &[key, value] : bitcoinexchange)
        {
            if (key < date)
                lastSmallerElement = value;
            else
                break;
        }
        y = lastSmallerElement * value;
    }
    std::cout << date << " => " << value << " = " << y << '\n';
}