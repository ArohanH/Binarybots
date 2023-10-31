#include "receiver.h"
#include <string>
#include <vector>

using namespace std;

int main()
{
    Receiver rcv;
    vector<pair<string, int>> stock_prices; // To keep track of the best prices
    string input_file = rcv.readIML();
    input_file.pop_back(); // remove the $ at the end of the input_file
    string line;
    vector<pair<string, int>> buy_update;
    vector<pair<string, int>> sell_update;

    istringstream stream(input_file);

    while (getline(stream, line, '#'))
    {
        string stock_name;
        string p;
        int price;
        char act;
        istringstream stream(line);
        stream >> stock_name >> p >> act;
        price = stoi(p);

        if (act == 'b')
        {
            bool check = false;
            for (int i = 0; i < sell_update.size(); i++)
            {
                if (sell_update[i].first == stock_name)
                {
                    if (sell_update[i].second == price)
                    {
                        sell_update.erase(sell_update.begin() + i);
                        cout << "No Trade" << endl;
                        check = true;
                        break;
                    }
                }
            }
            if (check == false)
            {
                bool check1 = false;
                for (int i = 0; i < stock_prices.size(); i++)
                {
                    if (stock_prices[i].first == stock_name)
                    {
                        if (stock_prices[i].second < price)
                        {
                            stock_prices[i].second = price;
                            cout << stock_name << " "<< price << " s" << endl;
                        }
                        else
                        {
                            bool c = false;
                            for (int i = 0; i < buy_update.size(); i++)
                            {
                                if (buy_update[i].first == stock_name)
                                {
                                    if (buy_update[i].second < price)
                                    {
                                        buy_update[i].second = price;
                                    }
                                    c = true;
                                    break;
                                }
                            }
                            if (c == false)
                            {
                                buy_update.push_back(make_pair(stock_name, price));
                            }
                            cout << "No Trade" << endl;
                        }
                        check1 = true;
                        break;
                    }
                }
                if (check1 == false)
                {
                    stock_prices.push_back(make_pair(stock_name, price));
                    cout << stock_name << " " << price << " s" << endl;
                }
            }
        }

        if (act == 's')
        {
            bool check = false;
            for (int i = 0; i < buy_update.size(); i++)
            {
                if (buy_update[i].first == stock_name)
                {
                    if (buy_update[i].second == price)
                    {
                        buy_update.erase(buy_update.begin() + i);
                        cout << "No Trade" << endl;
                        check = true;
                        break;
                    }
                }
            }
            if (check == false)
            {
                bool check1 = false;
                for (int i = 0; i < stock_prices.size(); i++)
                {
                    if (stock_prices[i].first == stock_name)
                    {
                        if (stock_prices[i].second > price)
                        {
                            stock_prices[i].second = price;
                            cout << stock_name << " "<< price << " b" << endl;
                        }
                        else
                        {
                            bool c = false;
                            for (int i = 0; i < sell_update.size(); i++)
                            {
                                if (sell_update[i].first == stock_name)
                                {
                                    if (sell_update[i].second >price)
                                    {
                                        sell_update[i].second = price;
                                    }
                                    c = true;
                                    break;
                                }
                            }
                            if (c == false)
                            {
                                sell_update.push_back(make_pair(stock_name, price));
                            }
                            cout << "No Trade" << endl;
                        }
                        check1 = true;
                        break;
                    }
                }
                if (check1 == false)
                {
                    stock_prices.push_back(make_pair(stock_name, price));
                    cout << stock_name << " " << price << " b" << endl;
                }
            }
        }
        
    }

    // Part 2 Code
    // A vector would be used to store all the inputs of part2 type till now
    //  vector<vector<int>> overall_stock_info;
    //  vector<pair<int, int>> price_and_act_for_allstocks;
    //  vector<pair<string, int>> stock_name_code;
    //  //Input strings are taken just like part1
    //  int j=0;
    //  while(j<lines.size())
    //  {
    //      vector<int> current_stock_info;
    //      //overall_stock_info.push_back(current_stock_info);
    //      int price;
    //      char act;
    //      current_stock_info.push_back(1);//first element is 1 means the stock has not been used for arbitrage
    //      istringstream stream(lines[j]);
    //      int no_of_stocks=0;// for number of stocks in the LC
    //      vector<pair<int, int>> k_values_and_quantity;
    //      while(stream){
    //          int k=0; //variable to be used for stock_name_code
    //          string stock_name;
    //          string q;
    //          stream >> stock_name >> q;
    //          no_of_stocks++;
    //          if(isalpha(q)){
    //              act=q;
    //              int price=stoi(stock_name);
    //              break;
    //          }
    //          int quantity=stoi(q);
    //          for(int i=0;i<stock_name_code.size();i++){
    //              if(stock_name_code[i].first==stock_name){
    //                  k=i;
    //                  break;
    //              }
    //          }
    //          if(k==0){
    //              stock_name_code.push_back(make_pair(stock_name,stock_name_code.size()));
    //              k=stock_name_code.size()-1;
    //          }
    //          k_values_and_quantity.push_back((k,quantity));
    //      }
    //      for(int i=0;i<stock_name_code.size();i++){ //This loop is for creating space inside the vector current_stock_info
    //          current_stock_info.push_back(-1); //This means every stock code for a particular stock name is initialised to -1(that means stock is not there)
    //          current_stock_info.push_back(0);// stock not there hence quantity is zero:)
    //      }
    //      for(int i=0;i<k_values_and_quantity.size();i++){
    //          current_stock_info[2*k_values_and_quantity[i].first+1]=k_values_and_quantity[i].first;
    //          current_stock_info[2*k_values_and_quantity[i].first+2]=k_values_and_quantity[i].second;
    //      }
    //      if(act=='b') price_and_act_for_allstocks.push_back((price,1));// 1 for buy
    //      else price_and_act_for_allstocks.push_back((price,-1));// -1 for sell
    //      overall_stock_info.push_back(current_stock_info);
    //      //algorithm to do the trade
    //      vector<int> sum_of_LC_of_trades;
    //      for(int a=0;a<overall_stock_info.size();a++){
    //          if(overall_stock_info[a][0]==1){
    //              for(int b=0;b<a;b++){
    //                  if(overall_stock_info[b][0]==1){
    //                      for(int i=2;i<current_stock_info.size();i=i+2){
    //                          sum_of_LC_of_trades.push_back(overall_stock_info[b][i]+overall_stock_info[a][i]+current_stock_info[i]);
    //                          if(sum_of_LC_of_trades[sum_of_LC_of_trades.size-1]!=0){

    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    return 0;
}
