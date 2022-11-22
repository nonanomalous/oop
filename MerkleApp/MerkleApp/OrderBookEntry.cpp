#include "OrderBookEntry.h"

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
	if (s == "bid") return OrderBookType::bid;
	if (s == "ask") return OrderBookType::ask;
	if (s == "bidsale") return OrderBookType::bidsale;
	if (s == "asksale") return OrderBookType::asksale;
	return OrderBookType::unknown;
}

std::string OrderBookEntry::typeToStr(OrderBookType type)
{
	switch (type) {
	case OrderBookType::ask: return "ask";
	case OrderBookType::bid: return "bid";
	case OrderBookType::sale: return "sale";
	}
	return "unknown";
}


