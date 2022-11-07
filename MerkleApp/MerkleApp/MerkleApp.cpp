#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "menu.h"

int main()
{
    std::vector<OrderBookEntry> orders;
    ;
    orders.push_back(OrderBookEntry{
        10000,
        0.002,
        "2020/03/17 17:01:24.884492",
        "DOGE/USDT",
        OrderBookType::bid });

    std::cout << orders[0].timestamp << std::endl;
    std::map<int, void (*)()> menu = setupMenu();
    while (true)
    {
        int userOption = getUserOption();
        menu[userOption]();
    }
    return 0;
}