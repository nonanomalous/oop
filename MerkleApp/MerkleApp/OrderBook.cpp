#include <algorithm>
#include <map>
#include "OrderBook.h"

OrderBook::OrderBook(std::string filename)
{
	orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;
	
	for (OrderBookEntry& e : orders)
		prodMap[e.product] = true;
	
	for (auto const& e : prodMap)
		products.push_back(e.first);

	return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> orders_sub;
	for (OrderBookEntry const& e : orders)
	{
		if (e.orderType == type &&
			e.product == product &&
			e.timestamp == timestamp)
		{
			orders_sub.push_back(e);
		}
	}
	return orders_sub;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAskToBids(std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

	std::vector<OrderBookEntry> sales;

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

	for (OrderBookEntry& ask : asks)
	{
		for (OrderBookEntry& bid : bids)
		{
			if (bid.price >= ask.price)
			{
				OrderBookEntry sale{ ask.price, 0, timestamp, product, OrderBookType::sale };

				if (bid.amount == ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;
				}
				if (bid.amount > ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount -= ask.amount;
					break;
				}
				if (bid.amount < ask.amount)
				{
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount -= bid.amount;
					continue;
				}

			}
		}
	}
	return sales;
}

std::string OrderBook::getEarliestTime()
{
	std::string earliest = orders[0].timestamp;
	return earliest;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp = "";
	for (OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;
			break;
		}
	}
	if (next_timestamp == "") 
		next_timestamp = orders[0].timestamp;
	return next_timestamp;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders)
		if (e.price > max) max = e.price;
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
		if (e.price < min) min = e.price;
	return min;
}

double OrderBook::getMeanPrice(std::vector<OrderBookEntry>& orders)
{
	double total = 0.0;
	for (OrderBookEntry& e : orders)
		total += e.price;
	return total / orders.size();
}

double OrderBook::getMedianPrice(std::vector<OrderBookEntry>& orders)
{
	double median;
	std::vector<double> prices;
	for (auto& e : orders)
		prices.push_back(e.price);
	sort(prices.begin(), prices.end());
	int index, size = prices.size();
	if (size % 2 == 1) 
		median = prices.at(size / 2);
	else median = (prices.at(size / 2) + prices.at((size / 2) - 1)) / 2;
	return median;
}