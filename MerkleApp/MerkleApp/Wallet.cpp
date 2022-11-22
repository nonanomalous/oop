#include "Wallet.h"

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

std::string Wallet::toString()
{
	return "Hi";
}