#include <sstream>
#include "Wallet.h"
#include <vector>
#include "CSVReader.h"

Wallet::Wallet()
{}

void Wallet::insertCurrency(std::string type, double amount)
{
	if (amount < 0) 
		throw std::exception{ "Cannot insert negative amounts" };
	
	double balance;
	
	if (currencies.count(type) == 0)
		balance = 0;
	else
		balance = currencies[type];

	currencies[type] = balance + amount;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
	if (currencies.count(type) == 0)
		return false;
	else
		return currencies[type] >= amount;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
	if (amount < 0) throw std::exception{ "Cannot remove negative amounts" };

	if (currencies.count(type) > 0 && containsCurrency(type, amount))
	{
		currencies[type] -= amount;
		return true;
	}
	return false;
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order)
{
	std::vector<std::string> currencies = CSVReader::tokenise(order.product, '/');

	if (order.orderType == OrderBookType::ask)
		return containsCurrency(currencies[0], order.amount);

	if (order.orderType == OrderBookType::bid)
		return containsCurrency(currencies[1], order.amount * order.price);

	return false;
}

std::string Wallet::toString()
{
	std::stringstream ss;
	for (std::pair<std::string, double> pair : currencies)
		ss << pair.first << " : " << pair.second << std::endl;
	return ss.str();
}