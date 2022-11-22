#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"

class CSVReader
{
public:
	CSVReader();

	static std::vector<OrderBookEntry> readCSV(std::string csvFile);
	static std::vector<std::string> tokenise(std::string csvLine, char separator);
	static OrderBookEntry stringsToOBE(
		std::string priceString,
		std::string amountString,
		std::string timestamp,
		std::string product,
		OrderBookType orderType,
		std::string username
	);

private:
	static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};

