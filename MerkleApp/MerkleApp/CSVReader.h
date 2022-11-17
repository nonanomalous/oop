#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"

class CSVReader
{
public:
	CSVReader();

	static std::vector<OrderBookEntry> readCSV(std::string csvFile);

private:
	static std::vector<std::string> tokenise(std::string csvLine, char separator);
	static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};

