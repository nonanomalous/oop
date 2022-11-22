#include <functional>
#include <iostream>
#include <map>
#include "MerkleMain.h"
#include "CSVReader.h"

MerkleMain::MerkleMain() {}

void MerkleMain::init() {
    wallet.insertCurrency("BTC", 10);
    currentTime = orderBook.getEarliestTime();
    printMenu();
    while (true) std::invoke(menu[getUserOption()], this);
}

void MerkleMain::printMenu()
{
    std::cout << "1: Print Help " << std::endl;
    std::cout << "2: Print Exchange Stats " << std::endl;
    std::cout << "3: Make an Ask " << std::endl;
    std::cout << "4: Make a Bid " << std::endl;
    std::cout << "5: Print Wallet " << std::endl;
    std::cout << "6: Continue " << std::endl;
    std::cout << "7: Quit " << std::endl;

    std::cout << "===============" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkleMain::printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
    printMenu();
}

void MerkleMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max: " << OrderBook::getHighPrice(entries) 
                  << "  Min: " << OrderBook::getLowPrice(entries)
                  << "  Mean: " << OrderBook::getMeanPrice(entries)
                  << "  Median: " << OrderBook::getMedianPrice(entries)
                  << std::endl;
    }
    
    /* std::cout << "OrderBook contains : " << orders.size() << " entries " << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == OrderBookType::ask)
            asks++;
        if (e.orderType == OrderBookType::bid)
            bids++;        
    }
    std::cout << "OrderBook asks : " << asks << " OrderBook bids : " << bids << std::endl;*/
}

void MerkleMain::enterOrder(OrderBookType type)
{
    std::cout << "Make an " << OrderBookEntry::typeToStr(type) << ", enter product, price, amount -- e.g. BTC/ETH,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You typed: " << input << std::endl;
    auto tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() == 3)
    {
        auto order = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], type, "simuser");
        if (wallet.canFulfillOrder(order))
            orderBook.insertOrder(order);
        else std::cout << "Insufficient funds." << std::endl;
    }
    else
        std::cout << "received bad input!" << std::endl;
}

void MerkleMain::enterAsk()
{
    enterOrder(OrderBookType::ask);
}

void MerkleMain::enterBid()
{
    enterOrder(OrderBookType::bid);
}

void MerkleMain::printWallet()
{
    std::cout << wallet.toString();
}

void MerkleMain::gotoNextTimeFrame()
{
    currentTime = orderBook.getNextTime(currentTime);
    auto sales = orderBook.matchAskToBids("DOGE/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl;
    for (auto sale : sales) 
        std::cout << "Amount: " << sale.amount << "  Price: " << sale.price << std::endl;
    printMenu();
}

void MerkleMain::quit() {
    std::cout << "Goodbye!" << std::endl;
    exit(0);
}

int MerkleMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (std::exception& e) { std::cout << e.what() << std::endl; };

    if (!std::cin.good() || !(userOption > 0 && userOption <= 7))
    {
        std::cout << "Invalid Choice -- Type in 1-7 " << std::endl;
        userOption = 0;
    }
    return userOption;
}