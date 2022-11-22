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
    //MerkleMain app{};
    //app.init();
    Wallet wallet;
    wallet.insertCurrency("BTC",5);
    std::cout << "Wallet has BTC: " << wallet.containsCurrency("BTC", 10) << std::endl;
    std::cout << wallet.toString() << std::endl;
    return 0;
}
