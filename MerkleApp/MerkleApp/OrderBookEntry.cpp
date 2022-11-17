#include "OrderBookEntry.h"

//std::vector<OrderBookEntry> orders;
//
//orders.push_back(OrderBookEntry{
//    10000,
//    0.002,
//    "2020/03/17 17:01:24.884492",
//    "DOGE/USDT",
//    OrderBookType::bid });

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
	if (s == "bid") return OrderBookType::bid;
	if (s == "ask") return OrderBookType::ask;
	return OrderBookType::unknown;
}
