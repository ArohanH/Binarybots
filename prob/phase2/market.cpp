#include "market.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


bool compare_vec(vector<pair<int,int>>& a,vector<pair<int,int>>& b){
    if(a.size()!=b.size()){
        return false;
    }
    for(int i=0;i<a.size();i++){
        if(a[i].first!=b[i].first || a[i].second!=b[i].second){
            return false;
        }
    }
    return true;
}

void merge(vector<pair<int, int>> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<pair<int, int>> L(n1), R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary vectors back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].first <= R[j].first)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<pair<int, int>> &arr, int left, int right)
{
    if (left < right)
    {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

market::market(int argc, char **argv)
{
}

void market::start()
{
    vector<pair<string, int>> stocks;
    vector<pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>>> buy;
    vector<pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>>> sell;
    // 1st vector<int> has 1->timestamp, 2->validperiod, 3->expiry, 0->validity
    ifstream inputFile("output.txt");
    string line;
    int time = 0;
    while (getline(inputFile, line))
    {
        if (line == "!@")
        {
            break;
        }
        if (line == "TL")
        {
            continue;
        }
        istringstream iss(line);
        // variables
        string clientname, ordertype, stockname, stock_quantity;
        int timestamp, price, quantity, period, expiry, stockquantity;

        iss >> timestamp >> clientname >> ordertype;
        if (timestamp != time)
        {
            for (auto &buy_item : buy)
            {
                if (buy_item.first[3] == time)
                {
                    buy_item.first[0] = 0;
                }
            }
            for (auto &sell_item : sell)
            {
                if (sell_item.first[3] == time)
                {
                    sell_item.first[0] = 0;
                }
            }
        }
        time = timestamp;
        if (ordertype == "BUY")
        {
            pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>> buy_temp;
            buy_temp.first.push_back(1);
            buy_temp.first.push_back(timestamp);
            buy_temp.second.first = clientname;
            bool flag1 = false;
            bool flag2 = false;
            while (iss >> stockname)
            {
                if (stockname[0] == '$')
                {
                    flag1 = true;
                    break;
                }
                bool found = false;
                int hash_val;
                for (auto &stock : stocks)
                {
                    if (stock.first == stockname)
                    {
                        found = true;
                        hash_val = stock.second;
                        break; // Exit the loop since the stock is found
                    }
                }
                int size = stocks.size();
                if (!found)
                {
                    hash_val = size;
                    stocks.push_back(make_pair(stockname, hash_val));
                }
                if (iss >> stock_quantity)
                {
                    if (stock_quantity[0] == '$')
                    {
                        flag2 = true;
                    }
                }
                if (flag2)
                {
                    stockquantity = 1;
                }
                else
                {
                    stockquantity = stoi(stock_quantity);
                }
                buy_temp.second.second.first.push_back(make_pair(hash_val, stockquantity));
                if (flag2)
                {
                    break;
                }
            }
            if (flag2)
            {
                stock_quantity.erase(stock_quantity.begin());
                price = stoi(stock_quantity);
            }
            else if (flag1)
            {
                stockname.erase(stockname.begin());
                price = stoi(stockname);
            }
            string q;
            iss >> q >> period;
            q.erase(q.begin());
            quantity = stoi(q);
            buy_temp.second.second.second.push_back(price);
            buy_temp.second.second.second.push_back(quantity);
            if (period == -1)
                expiry = -1;
            else
            {
                expiry = period + timestamp;
            }
            buy_temp.first.push_back(period);
            buy_temp.first.push_back(expiry);
            mergeSort(buy_temp.second.second.first, 0,buy_temp.second.second.first.size()- 1);

            // processing
            //  vector<pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>>>::iterator a;
            vector<pair<vector<int>, string>> index;
            for (int i = 0; i < sell.size(); i++)
            {
                if (sell[i].first[0] == 0){
                    continue;
                }
                else
                {
                    bool test = compare_vec(sell[i].second.second.first, buy_temp.second.second.first);
                    if (test)
                    {
                        sell[i].second.second.second[0] <= buy_temp.second.second.second[0];
                        vector<int> tmp;
                        tmp.push_back(sell[i].second.second.second[0]);
                        tmp.push_back(sell[i].first[1]);
                        tmp.push_back(i);
                        index.push_back(make_pair(tmp, sell[i].second.first));
                    }
                }
            }
            sort_index(index);
        }

















        if (ordertype == "SELL")
        {
            pair<vector<int>, pair<string, pair<pair<string, int>, vector<int>>>> buy_temp;

            buy_temp.first[0] = timestamp;
            buy_temp.second.first = clientname;
            bool flag = false;
            while (iss >> stockname)
            {
                if (stockname[0] == '$')
                {
                    flag = true;
                    break;
                }
                buy_temp.second.second.first.first = stockname;
                if (!(iss >> stockquantity))
                {
                    iss >> stockname;
                    flag = true;
                    break;
                }
                buy_temp.second.second.first.second = stockquantity;
            }
            if (flag)
            {
                stockname.erase(stockname.begin());
                price = stoi(stockname);
            }
            string q;
            iss >> q >> period;
            q.erase(q.begin());
            quantity = stoi(q);
            expiry = period + timestamp;
            buy_temp.first[1] = period;
            buy_temp.first[2] = expiry;
            sell.push_back(buy_temp);
        }
    }
}
