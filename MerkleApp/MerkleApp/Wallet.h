#pragma once
#include <map>
#include <string>
#include "OrderBookEntry.h"

class Wallet
{
public:
	Wallet();
	/** make a deposit*/
	void insertCurrency(std::string type, double amount);

	/** verify a trade can be covered*/
	bool containsCurrency(std::string type, double amount);

	/** remove Currency from a wallet */
	bool removeCurrency(std::string type, double amount);

	/** checks if wallet can cope with ask or bid*/
	bool canFulfillOrder(const OrderBookEntry& order);

	/** update the contents of the wallet */
	void processSale(const OrderBookEntry& sale);

	/** print the wallet contents */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};