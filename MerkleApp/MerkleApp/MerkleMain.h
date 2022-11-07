#pragma once
#include <map>

class MerkleMain
{
public:
	typedef void (MerkleMain::*MFN)();
	std::map<int, MFN> menu;

	MerkleMain();
	void init();
	void printMenu();
	void printHelp();
	void printExchangeStats();
	void enterOffer();
	void enterBid();
	void printWallet();
	void gotoNextTimeFrame();
	int getUserOption();
	void quit();
};

