#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <ctime>
#include <vector>
#include <sstream>
#include <regex>
#include "Wallet.hpp"
#include "BitcoinExchange.hpp"
#include "Value.hpp"
#include "Date.hpp"

void inputParse(const char *inputFileName, const BitcoinExchange &bitcoinexchange)
{
    std::ifstream inf{inputFileName};

    if (!inf)
        throw std::runtime_error("Error: could not open input file.\n");

    while (!inf.eof())
    {
        std::string strInput{};
        std::getline(inf, strInput);
        try
        {
            Wallet wallet{bitcoinexchange, strInput};
            wallet.putBtcInEur();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

int main(int argc, char *argv[2])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc input.csv\n";
        return 2;
    }
    try
    {
        BitcoinExchange bitcoinexchange{};
        inputParse(argv[1], bitcoinexchange);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
        return 1;
    }

    return 0;
}