#include <functional>
#include <iostream>
#include <map>
#include "MerkleMain.h"
#include "CSVReader.h"

MerkleMain::MerkleMain() {}

void MerkleMain::loadOrderBook()
{
    orders = CSVReader::readCSV("data.csv");
}

void MerkleMain::init() {
    
    loadOrderBook();
    printMenu();
    while (true) std::invoke(menu[getUserOption()], this);
}

void MerkleMain::printMenu()
{
    std::cout << "1: Print Help " << std::endl;
    std::cout << "2: Print Exchange Stats " << std::endl;
    std::cout << "3: Make an Offer " << std::endl;
    std::cout << "4: Make a Bid " << std::endl;
    std::cout << "5: Print Wallet " << std::endl;
    std::cout << "6: Continue " << std::endl;
    std::cout << "7: Quit " << std::endl;

    std::cout << "===============" << std::endl;
    std::cout << "Type in 1-7 " << std::endl;
}

void MerkleMain::printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
    printMenu();
}

void MerkleMain::printMarketStats()
{
    std::cout << "OrderBook contains : " << orders.size() << " entries " << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == OrderBookType::ask)
            asks++;
        if (e.orderType == OrderBookType::bid)
            bids++;        
    }
    std::cout << "OrderBook asks : " << asks << " OrderBook bids : " << bids << std::endl;
}

void MerkleMain::enterOffer()
{
    std::cout << "Make an Offer" << std::endl;
}

void MerkleMain::enterBid()
{
    std::cout << "Make a Bid" << std::endl;
}

void MerkleMain::printWallet()
{
    std::cout << "Here is your wallet" << std::endl;
}

void MerkleMain::gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
}

void MerkleMain::quit() {
    std::cout << "Goodbye!" << std::endl;
    exit(0);
}

int MerkleMain::getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << std::endl;
    if (!std::cin.good() || !(userOption > 0 && userOption <= 7))
    {
        std::cout << "Invalid Choice -- Type in 1-7 " << std::endl;
        userOption = 0;
    }
    return userOption;
}