#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "CSVReader.h"
using namespace std;

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

 
void MerkelMain::printMenu()
{

        cout << "1: Print help " << endl;
        cout << "2: Print exchange stats " << endl;
        cout << "3: Make an offer " << endl;
        cout << "4: Make a bid " << endl;
        cout << "5: Print wallet " << endl;
        cout << "6: Continue " << endl;
        cout << "============= " << endl;
        cout << "Current time is: " << currentTime << endl;
}

void MerkelMain::printHelp()
{
    cout << "Help - your aim is to make money. Analyse the market and make informed bids and offers. " << endl;
}

void MerkelMain::printMarketStats()
{
    for (string const& p : orderBook.getKnownProducts())
    {
        cout << "Product: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        cout << "Asks seen: " << entries.size() << endl;
        cout << "Max ask: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entries) << endl;



    }
}

void MerkelMain::enterAsk()
{
    cout << "Make an ask - enter the amount: product, price, amount, eg  ETH/BTC,200,0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "Invalid input! " << input << endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                cout << "Wallet looks good. " << endl;
                orderBook.insertOrder(obe);
            }
            else {
                cout << "Wallet has insufficient funds . " << endl;
            }
        }catch (const exception& e)
        {
            cout << " MerkelMain::enterAsk Bad input " << endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    cout << "Make a bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << endl;
    string input;
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        cout << "MerkelMain::enterBid Bad input! " << input << endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                cout << "Your wallet looks good. " << endl;
                orderBook.insertOrder(obe);
            }
            else {
                cout << "Your wallet has insufficient funds . " << endl;
            }
        }catch (const exception& e)
        {
            cout << "Invalid Bad input " << endl;
        }   
    }
}


void MerkelMain::printWallet()
{   cout << "Your wallet contains: " << endl;
    cout << wallet.toString() << endl;
}

void MerkelMain::gotoNextTimeframe()
{
    cout << "Going to next time frame. " << endl;
    for (string p : orderBook.getKnownProducts())
    {
        cout << "matching " << p << endl;
        vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        cout << "Sales: " << sales.size() << endl;
        for (OrderBookEntry& sale : sales)
        {
            cout << "Sale price: " << sale.price << " amount " << sale.amount << endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    string line;
    cout << "Type in 1-6" << endl;
    getline(cin, line);
    try{
        userOption = stoi(line);
    }catch(const exception& e)
    {
        // 
    }
    cout << "You chose: " << userOption << endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{

    if (userOption == 0){
        cout << "Invalid choice. Choose 1-6" << endl;
    }
    if (userOption == 1){
        printHelp();
    }
    if (userOption == 2){
        printMarketStats();
    }
    if (userOption == 3){
        enterAsk();
    }
    if (userOption == 4){
        enterBid();
    }
    if (userOption == 5){
        printWallet();
    }
    if (userOption == 6){
        gotoNextTimeframe();
    }
}