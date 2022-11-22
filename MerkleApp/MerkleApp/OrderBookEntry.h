#pragma once
#include <string>
enum class OrderBookType
{
    bid,
    ask,
    sale,
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

    static OrderBookType stringToOrderBookType(std::string s);

    OrderBookEntry(
        double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _orderType)
        : price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType) {};

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