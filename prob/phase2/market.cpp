#include "market.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

market::market(int argc, char **argv)
{
}

bool compare_vec(vector<pair<int, int>> &a, vector<pair<int, int>> &b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].first != b[i].first || a[i].second != b[i].second)
        {
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
////////////////////////////////////////////////

bool customComparator(const pair<vector<int>, string> &a, const pair<vector<int>, string> &b)
{
    // 1. Sort in decreasing order of vector<int>[0]
    if (a.first[0] != b.first[0])
    {
        return a.first[0] > b.first[0];
    }

    // 2. Sort in increasing order of vector<int>[1]
    if (a.first[1] != b.first[1])
    {
        return a.first[1] < b.first[1];
    }

    // 3. Sort in increasing alphabetical order for string
    return a.second < b.second;
}

void merge1(vector<pair<vector<int>, string>> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<pair<vector<int>, string>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (customComparator(L[i], R[j]))
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

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort1(vector<pair<vector<int>, string>> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort1(arr, l, m);
        mergeSort1(arr, m + 1, r);

        merge1(arr, l, m, r);
    }
}

//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
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
            time = timestamp;
        }

        if (ordertype == "BUY")
        {
            pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>> buy_temp;
            buy_temp.first.push_back(1);
            buy_temp.first.push_back(timestamp);
            buy_temp.second.first = clientname;
            bool flag1 = false;
            bool flag2 = false;
            string printout;
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
                printout+=stockname+" "+to_string(stockquantity)+" ";
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
            mergeSort(buy_temp.second.second.first, 0, buy_temp.second.second.first.size() - 1);

            // processing
            vector<pair<vector<int>, string>> index;
            for (int i = 0; i < sell.size(); i++)
            {
                if (sell[i].first[0] == 0)
                {
                    continue;
                }
                else
                {
                    bool test = compare_vec(sell[i].second.second.first, buy_temp.second.second.first);
                    if (test)
                    {
                        if (sell[i].second.second.second[0] <= buy_temp.second.second.second[0])
                        {
                            vector<int> tmp;
                            tmp.push_back(sell[i].second.second.second[0]);
                            tmp.push_back(sell[i].first[1]);
                            tmp.push_back(i);
                            index.push_back(make_pair(tmp, sell[i].second.first));
                        }
                    }
                }
            }
            if (index.size() > 0)
            {
                mergeSort1(index, 0, index.size() - 1);
            }
            for (int i = 0; i < index.size(); i++)
            {
                int t = index[i].first[2];
                if (buy_temp.second.second.second[1] >= sell[t].second.second.second[1])
                {
                    buy_temp.second.second.second[1] = buy_temp.second.second.second[1] - sell[t].second.second.second[1];
                    cout <<buy_temp.second.first<<" purchased "<<sell[t].second.second.second[1]<<" share of "<<printout<<"from "<<sell[t].second.first<<" for $"<<sell[t].second.second.second[0]<<"/share"<<endl;
                    sell[t].second.second.second[1] = 0;
                    sell[t].first[0] = 0;
                }
                else
                {
                    sell[t].second.second.second[1] = sell[t].second.second.second[1] - buy_temp.second.second.second[1];
                    cout <<buy_temp.second.first<<" purchased "<<buy_temp.second.second.second[1]<<" share of "<<printout<<"from "<<sell[t].second.first<<" for $"<<sell[t].second.second.second[0]<<"/share"<<endl;
                    buy_temp.second.second.second[1] = 0;
                    buy_temp.first[0] = 0;
                    break;
                }
            }
            if (buy_temp.first[0] != 0)
            {
                buy.push_back(buy_temp);
            }
        }

        ///////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////

        if (ordertype == "SELL")
        {
            pair<vector<int>, pair<string, pair<vector<pair<int, int>>, vector<int>>>> sell_temp;
            sell_temp.first.push_back(1);
            sell_temp.first.push_back(timestamp);
            sell_temp.second.first = clientname;
            bool flag1 = false;
            bool flag2 = false;
            string printout;
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
                printout+=stockname+" "+to_string(stockquantity)+" ";
                sell_temp.second.second.first.push_back(make_pair(hash_val, stockquantity));
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
            sell_temp.second.second.second.push_back(price);
            sell_temp.second.second.second.push_back(quantity);
            if (period == -1)
                expiry = -1;
            else
            {
                expiry = period + timestamp;
            }
            sell_temp.first.push_back(period);
            sell_temp.first.push_back(expiry);
            mergeSort(sell_temp.second.second.first, 0, sell_temp.second.second.first.size() - 1);

            // processing
            vector<pair<vector<int>, string>> index;
            for (int i = 0; i < buy.size(); i++)
            {
                if (buy[i].first[0] == 0)
                {
                    continue;
                }
                else
                {
                    bool test = compare_vec(buy[i].second.second.first, sell_temp.second.second.first);
                    if (test)
                    {
                        if (buy[i].second.second.second[0] >= sell_temp.second.second.second[0])
                        {
                            vector<int> tmp;
                            tmp.push_back(buy[i].second.second.second[0]);
                            tmp.push_back(buy[i].first[1]);
                            tmp.push_back(i);
                            index.push_back(make_pair(tmp, buy[i].second.first));
                        }
                    }
                }
            }
            if (index.size() > 0)
            {
                mergeSort1(index, 0, index.size() - 1);
            }
            for (int i = 0; i < index.size(); i++)
            {
                int t = index[i].first[2];
                if (sell_temp.second.second.second[1] >= buy[t].second.second.second[1])
                {
                    sell_temp.second.second.second[1] = sell_temp.second.second.second[1] - buy[t].second.second.second[1];
                    cout <<buy[t].second.first<<" purchased "<<buy[t].second.second.second[1]<<" share of "<<printout<<"from "<<sell_temp.second.first<<" for $"<<buy[t].second.second.second[0]<<"/share"<<endl;
                    buy[t].second.second.second[1] = 0;
                    buy[t].first[0] = 0;
                }
                else
                {
                    buy[t].second.second.second[1] = buy[t].second.second.second[1] - sell_temp.second.second.second[1];
                    cout <<buy[t].second.first<<" purchased "<<sell_temp.second.second.second[1]<<" share of "<<printout<<"from "<<sell_temp.second.first<<" for $"<<buy[t].second.second.second[0]<<"/share"<<endl;
                    sell_temp.second.second.second[1] = 0;
                    sell_temp.first[0] = 0;
                    break;
                }
            }
            if (sell_temp.first[0] != 0)
            {
                sell.push_back(sell_temp);
            }
        }
    }
}
