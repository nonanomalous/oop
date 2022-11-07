#include <iostream>
#include <map>

void printMenu()
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

void printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
    printMenu();
}

void printExchangeStats()
{
    std::cout << "Exchange is online" << std::endl;
}

void enterOffer()
{
    std::cout << "Make an Offer" << std::endl;
}

void enterBid()
{
    std::cout << "Make a Bid" << std::endl;
}

void printWallet()
{
    std::cout << "Here is your wallet" << std::endl;
}

void gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
}

void quit() {
    std::cout << "Goodbye!" << std::endl;
    exit(0);
}

std::map<int, void (*)()> setupMenu()
{
    std::map<int, void (*)()> menu;
    menu[0] = printMenu;
    menu[1] = printHelp;
    menu[2] = printExchangeStats;
    menu[3] = enterOffer;
    menu[4] = enterBid;
    menu[5] = printWallet;
    menu[6] = gotoNextTimeFrame;
    menu[7] = quit;
    printMenu();
    return menu;
}

int getUserOption()
{
    int userOption;
    std::cin >> userOption;
    std::cout << std::endl;
    if (!std::cin.good() || !(userOption > 0 && userOption <= 7))
    {
        std::cout << "Invalid Choice -- Type in 1-6 " << std::endl;
        userOption = 0;
    }
    return userOption;
}