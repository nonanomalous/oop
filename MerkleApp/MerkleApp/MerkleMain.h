#pragma once
#include <map>
#include <vector>
#include "OrderBookEntry.h"

class MerkleMain
{
public:
	typedef void (MerkleMain::*MFN)();
	std::map<int, MFN> menu{
		{0, &MerkleMain::printMenu},
		{1, &MerkleMain::printHelp},
		{2, &MerkleMain::printMarketStats},
		{3, &MerkleMain::enterOffer},
		{4, &MerkleMain::enterBid},
		{5, &MerkleMain::printWallet},
		{6, &MerkleMain::gotoNextTimeFrame},
		{7, &MerkleMain::quit}
	};
	
	MerkleMain();	
	void init();
	void printMenu();
	void printHelp();
	void printMarketStats();
	void enterOffer();
	void enterBid();
	void printWallet();
	void gotoNextTimeFrame();
	int getUserOption();
	void quit();

private:
	std::vector<OrderBookEntry> orders;
	void loadOrderBook();
};

