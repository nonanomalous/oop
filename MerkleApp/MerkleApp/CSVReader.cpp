#include <fstream>
#include <iostream>
#include "CSVReader.h"

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
    std::ifstream csvFile{ csvFileName };
    std::string line;
	std::vector<OrderBookEntry> entries;

    if (csvFile.is_open())
    {
        std::cout << "File open" << std::endl;
        while (std::getline(csvFile, line))
        {
            try
            {
                auto obe = CSVReader::stringsToOBE(CSVReader::tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (...)
            {
                std::cout << "!";
            }

        }
        std::cout << std::endl << "CSVReader::readCSV read " << entries.size() << " records." << std::endl;
    }
    else
    {
        std::cout << "File not open" << std::endl;
    }
   
    csvFile.close();
	return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;

    } while (end != std::string::npos);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(
    std::string priceString,
    std::string amountString,
    std::string timestamp,
    std::string product,
    OrderBookType orderType
)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE: " << e.what() << '\n';
        throw;
    }
    OrderBookEntry obe{ price,
        amount,
        timestamp,
        product,
        orderType };
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    if (tokens.size() != 5)
    {
        throw std::exception{};        
    }
    double price, amount;
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (...)
    {
        std::cout << "CSVReader::stringsToOBE: " << '\n';
        throw;
    }
    try {
        OrderBookEntry obe{
            price,
            amount,
            tokens[0],
            tokens[1],
            OrderBookEntry::stringToOrderBookType(tokens[2]) };
        return obe;
    }
    catch (const std::exception& e)
    {
        std::cout << "Failed initializing OBE";
    }

}
