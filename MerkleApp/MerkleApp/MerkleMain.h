#pragma once
#include <map>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkleMain
{
public:
	typedef void (MerkleMain::*MFN)();
	std::map<int, MFN> menu{
		{0, &MerkleMain::printMenu},
		{1, &MerkleMain::printHelp},
		{2, &MerkleMain::printMarketStats},
		{3, &MerkleMain::enterAsk},
		{4, &MerkleMain::enterBid},
		{5, &MerkleMain::printWallet},
		{6, &MerkleMain::gotoNextTimeFrame},
		{7, &MerkleMain::quit}
	};
	
	MerkleMain();	
	void init();

private:
	void printMenu();
	void printHelp();
	void printMarketStats();
	void enterOrder(OrderBookType type);
	void enterAsk();
	void enterBid();
	void printWallet();
	void gotoNextTimeFrame();
	int getUserOption();
	void quit();

	std::string currentTime;

	OrderBook orderBook{"20200317.csv"};
	Wallet wallet;
};

