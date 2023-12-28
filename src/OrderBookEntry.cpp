#include "OrderBookEntry.h"
using namespace std;

OrderBookEntry::OrderBookEntry( double _price, 
                        double _amount, 
                        string _timestamp, 
                        string _product, 
                        OrderBookType _orderType, 
                        string _username)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType), 
  username(_username)
{
  
    
}

OrderBookType OrderBookEntry::stringToOrderBookType(string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  return OrderBookType::unknown;
}
