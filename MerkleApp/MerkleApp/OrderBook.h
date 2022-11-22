#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>

class OrderBook
{
public:
	OrderBook(std::string filename);
	/** get all known products from the Order Book */
	std::vector<std::string> getKnownProducts();
	/** filter orders by params */
	std::vector<OrderBookEntry> getOrders(OrderBookType type,
		std::string product,
		std::string timestamp);
	
	void insertOrder(OrderBookEntry& order);
	std::vector<OrderBookEntry> matchAskToBids(std::string product, std::string timestamp);
	
	/** Returns earliest time */
	std::string getEarliestTime();
	
	/** returns next time after sent time */
	std::string getNextTime(std::string timestamp);

	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
	static double getMeanPrice(std::vector<OrderBookEntry>& orders);
	static double getMedianPrice(std::vector<OrderBookEntry>& orders);
	//static double getModePrice(std::vector<OrderBookEntry>& orders);

private:
	std::vector<OrderBookEntry> orders;
};

