#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkleMain.h"
#include "CSVReader.h"
#include "Wallet.h"

int main()
{
    MerkleMain app{};
    app.init();
    /*
    Wallet wallet;
    wallet.insertCurrency("BTC",5);
    wallet.insertCurrency("USDT", 10);
    std::cout << "Wallet has BTC: " << wallet.containsCurrency("BTC", 10) << std::endl;
    wallet.removeCurrency("BTC", 4);
    wallet.removeCurrency("USDT", 11);
    std::cout << wallet.toString() << std::endl;
    */
    return 0;
}
