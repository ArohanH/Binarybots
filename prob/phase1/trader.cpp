#include "receiver.h"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    Receiver rcv;
    unordered_map<string, int> stock_prices; // To keep track of the best prices
    string input = rcv.readIML();
    int j=0;
    int len=input.size();
    while (j<len) {
        string stock_name=NULL;
        string p=NULL;
        int price;
        char act=NULL;
        int i=j;
        
        while (true) {
            char c = input[i];
            i++;
            if(c==' '){
                break;
            }
            else stock_name+=c;
        }
        while (true) {
            char c = input[i];
            i++;
            if(c==' '){
                break;
            }
            else p +=c;
        }
        price=stoi(p);
        while (true) {
            char c = input[i];
            i++;
            if(c=='#'){
                break;
            }
            else act = c;
        }
        j=i;
        if (act == 'b') {
            if (stock_prices.find(stock_name) == stock_prices.end() || price > stock_prices[stock_name]) {
                stock_prices[stock_name] = price; // Update the best buy price
                cout << stock_name << " " << price << " s" << endl;
            } else {
                cout << "No Trade" << endl;
            }
        } else if (act == 's') {
            if (stock_prices.find(stock_name) == stock_prices.end() || price < stock_prices[stock_name]) {
                stock_prices[stock_name] = price; // Update the best sell price
                cout << stock_name << " " << price << " b" << endl;
            } else {
                cout << "No Trade" << endl;
            }
        }
    }
    return 0;
}