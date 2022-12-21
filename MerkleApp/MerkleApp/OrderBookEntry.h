#pragma once
#include <string>
enum class OrderBookType
{
    bid,
    ask,
    bidsale,
    asksale,
    unknown
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;

    static OrderBookType stringToOrderBookType(std::string s);
    static std::string typeToStr(OrderBookType type);

    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _orderType,
        std::string _username = "dataset")
        : price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType), username(_username) {};
        

    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    }

    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }

    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }
};