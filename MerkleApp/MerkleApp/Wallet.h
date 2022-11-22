#pragma once
#include <map>
#include <string>

class Wallet
{
public:
	Wallet();
	/** make a deposit*/
	void insertCurrency(std::string type, double amount);

	/** verify a trade can be covered*/
	bool containsCurrency(std::string type, double amount);

	/** print the wallet contents */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};