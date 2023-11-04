#include "receiver.h"
#include <string>
#include <vector>

using namespace std;

void calcSubset(vector<pair<vector<pair<int,int>>,pair<int,int>>>& A, vector<pair<vector<pair<int,int>>,pair<int,int>>>& subset, int index){
    subsets_of_all_the_stock_combinations_part_2.push_back(subset);
    if(subset.second)
    for(int i=index; i< A.size(); i++){
        subset.push_back(A[i]);
        calcSubset(A, subset, i+1);
        subset.pop_back();
    }
}
void subsets(vector<pair<vector<pair<int,int>>,pair<int,int>>>& A){
    vector<pair<vector<pair<int,int>>,pair<int,int>>> subset;
   //vector<vector<pair<vector<pair<int,int>>,pair<int,int>>>> res;
    int index=0;
    calcSubset(A, subset, index);
    return res;
}

vector<vector<pair<vector<pair<int,int>>,pair<int,int>>>> subsets_of_all_the_stock_combinations_part_2;
vector<pair<vector<pair<int,int>>,pair<int,int>>> max_profit_combination; 
int max_profit_subset;
int max_profit;
int main()
{
    Receiver rcv;
    vector<pair<string, int>> stock_prices; // To keep track of the best prices
    vector<pair<string, int>> stock_prices_best_buy_price; //to store the best buy order of a stock(for cancellation and other stuff)
    vector<pair<string, int>> stock_prices_best_sell_price; //to store the best sell order of a stock(for cancellation and other stuff)
    string input_file = rcv.readIML();
    input_file.pop_back(); // remove the $ at the end of the input_file
    string line;

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

            if(!stock_prices_best_buy_price.empty()){
                for(int i=0; i< stock_prices_best_buy_price.size(), i++){
                    if(stock_prices_best_buy_price[i].first==stock_name){
                        if(stock_prices_best_buy_price[i].second>price){
                            check=true;    
                        }
                        break;
                    }
                }
            }

            for (int i = 0; i < stock_prices.size(); i++)
            {
                if (stock_prices[i].first == stock_name)
                {
                    if (stock_prices[i].second < price)
                    {
                        stock_prices[i].second = price;
                        cout << stock_name << " " << price << " s" << endl;
                    }
                    else
                    {
                        cout << "No Trade" << endl;
                    }
                    check = true;
                    break;
                }
            }
            if (check == false)
            {
                stock_prices.push_back(make_pair(stock_name, price));
                cout << stock_name << " " << price << " s" << endl;
            }
        }

        if (act == 's')
        {
            bool check = false;
            for (int i = 0; i < stock_prices.size(); i++)
            {
                if (stock_prices[i].first == stock_name)
                {
                    if (stock_prices[i].second > price)
                    {
                        stock_prices[i].second = price;
                        cout << stock_name << " " << price << " b" << endl;
                    }
                    else
                    {
                        cout << "No Trade" << endl;
                    }
                    check = true;
                    break;
                }
            }
            if (check == false)
            {
                stock_prices.push_back(make_pair(stock_name, price));
                cout << stock_name << " " << price << " b" << endl;
            }
        }
    }

    //Part 2 Code
    //A vector would be used to store all the inputs of part2 type till now
    vector<pair<vector<pair<int,int>>,pair<int,int>>> overall_stock_info;
    //vector<pair<int, int>> price_and_act_for_allstocks;  
    vector<pair<string, int>> stock_name_code;
    //Input strings are taken just like part1
    int j=0;
    while(j<lines.size())
    {   
        vector<pair<int,int>> current_stock_info;//Here vector<LC,price-signal pair>, LC:vector<stock_code,quantity>
        //overall_stock_info.push_back(current_stock_info);
        int price;
        char act; 
        current_stock_info.push_back(make_pair(1,j+1));//first element is 1 means the stock has not been used for arbitrage and j+1 is printing which line of input it is
        istringstream stream(lines[j]);
        j++;
        int no_of_stocks=0;// for number of stocks in the LC 
        vector<pair<int, int>> k_values_and_quantity; 
        while(stream){
            int k=0; //variable to be used for stock_name_code
            string stock_name;
            string q;
            stream >> stock_name >> q;
            no_of_stocks++;
            if(isalpha(q)){
                act=q;
                int price=stoi(stock_name);
                break;
            }
            int quantity=stoi(q);
            for(int i=0;i<stock_name_code.size();i++){
                if(stock_name_code[i].first==stock_name){
                    k=i;
                    break;
                }
            }
            if(k==0){
                stock_name_code.push_back(make_pair(stock_name,stock_name_code.size()));
                k=stock_name_code.size()-1;
            }
            k_values_and_quantity.push_back(make_pair(k,quantity));
        }
        for(int i=0;i<stock_name_code.size();i++){ //This loop is for creating space inside the vector current_stock_info
            current_stock_info.push_back(make_pair(-1,0)); //This means every stock code for a particular stock name is initialised to -1(that means stock is not there)
            //current_stock_info.push_back(0);// stock not there hence quantity is zero:)
        }
        for(int i=0;i<k_values_and_quantity.size();i++){
            current_stock_info[2*k_values_and_quantity[i].first+1]=k_values_and_quantity[i].first;
            current_stock_info[2*k_values_and_quantity[i].first+2]=k_values_and_quantity[i].second;
        }
        if(act=='b') overall_stock_info.push_back(make_pair(current_stock_info,make_pair(price,1)));// 1 for buy
        else overall_stock_info.push_back(make_pair(current_stock_info,make_pair(price,-1)));// -1 for sell
        //overall_stock_info.push_back(current_stock_info);
        //algorithm to do the trade
        for(int i=0;i<overall_stock_info.size()-1;i++){
            if(overall.stock_info[i].first.size()<overall_stock_info[overall_stock_info.size()-1].first.size()){
                while(overall.stock_info[i].first.size()!=overall_stock_info[overall_stock_info.size()-1].first.size()){
                    overall_stock_info[i].first.push_back((-1,0));
                }
            }
            if(overall_stock_info[i].first==overall_stock_info[overall_stock_info.size()-1].first && overall_stock_info[i].second.second==overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info)
            if(overall_stock_info[i].first==overall_stock_info[overall_stock_info.size()-1].first && overall_stock_info[i].second.second==-overall_stock_info[overall_stock_info.size()-1].second.second){
                overall_stock_info
            }
        }
        max_profit_subset=0;
        max_profit=INT_MIN();
        subsets(overall_stock_info);//my max
        
    }


    return 0;
}