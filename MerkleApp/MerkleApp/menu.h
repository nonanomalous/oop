#pragma once
#include <map>

void printMenu();
void printHelp();
void enterOffer();
void enterBid();
void printWallet();
void gotoNextTimeFrame();
std::map<int, void (*)()> setupMenu();
int getUserOption();
