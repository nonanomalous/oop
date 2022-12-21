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
	std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');

	if (order.orderType == OrderBookType::ask)
		return containsCurrency(currs[0], order.amount);

	if (order.orderType == OrderBookType::bid)
		return containsCurrency(currs[1], order.amount * order.price);

	return false;
}

void Wallet::processSale(const OrderBookEntry& sale)
{
	std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

	if (sale.orderType == OrderBookType::asksale)
	{
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currs[0];
		double incomingAmount = sale.amount * sale.price;
		std::string incomingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}


	if (sale.orderType == OrderBookType::bidsale)
	{
		double incomingAmount = sale.amount;
		std::string incomingCurrency = currs[0];
		double outgoingAmount = sale.amount * sale.price;
		std::string outgoingCurrency = currs[1];

		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}

}

std::string Wallet::toString()
{
	std::stringstream ss;
	for (std::pair<std::string, double> pair : currencies)
		ss << pair.first << " : " << pair.second << std::endl;
	return ss.str();
}