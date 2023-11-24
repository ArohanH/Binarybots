#include "market.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

market::market(int argc, char **argv)
{
}

void market::start()
{
    vector<pair<vector<int>, pair<string, pair<pair<string, int>, vector<int>>>>> buy;
    vector<pair<vector<int>, pair<string, pair<pair<string, int>, vector<int>>>>> sell;
    // 1st vector<int> has 0->timestamp, 1->valid, 2->expiry
    ifstream inputFile("output.txt");
    ofstream outputFile("output.txt", std::ios::app);
    string line;

    while (getline(inputFile, line))
    {
        if (line == "TL")
        {
            continue;
        }
        istringstream iss(line);
        int timestamp;
        string clientname, ordertype, stockname;
        int price, quantity, period, expiry,stockquantity;
        iss >> timestamp >> clientname >> ordertype;
        if (ordertype == "BUY")
        {
            pair<vector<int>, pair<string, pair<pair<string, int>, vector<int>>>> buy_temp;

            buy_temp.first[0] = timestamp;
            buy_temp.second.first = clientname;
            bool flag=false;
            while (iss >> stockname)
            {
                if (stockname[0] == '$'){
                    flag=true;
                    break;
                }
                buy_temp.second.second.first.first=stockname;
                if(!(iss>>stockquantity)){
                    iss>>stockname;
                    flag=true;
                    break;
                }
                buy_temp.second.second.first.second=stockquantity;
            }
            if(flag){
                stockname.erase(stockname.begin());
                price=stoi(stockname);
            }
            string q;
            iss>>q>>period;
            q.erase(q.begin());
            quantity=stoi(q);
            expiry=period+timestamp;
            buy_temp.first[1] = period;
            buy_temp.first[2] = expiry;
            buy.push_back(buy_temp);
        }
        if (ordertype == "SELL")
        {
            pair<vector<int>, pair<string, pair<pair<string, int>, vector<int>>>> buy_temp;

            buy_temp.first[0] = timestamp;
            buy_temp.second.first = clientname;
            bool flag=false;
            while (iss >> stockname)
            {
                if (stockname[0] == '$'){
                    flag=true;
                    break;
                }
                buy_temp.second.second.first.first=stockname;
                if(!(iss>>stockquantity)){
                    iss>>stockname;
                    flag=true;
                    break;
                }
                buy_temp.second.second.first.second=stockquantity;
            }
            if(flag){
                stockname.erase(stockname.begin());
                price=stoi(stockname);
            }
            string q;
            iss>>q>>period;
            q.erase(q.begin());
            quantity=stoi(q);
            expiry=period+timestamp;
            buy_temp.first[1] = period;
            buy_temp.first[2] = expiry;
            sell.push_back(buy_temp);
        }
    }
}
