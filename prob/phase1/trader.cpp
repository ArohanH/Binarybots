#include "receiver.h"
#include <string>
#include <vector>

using namespace std;

void calcSubset(vector<pair<vector<pair<int,int>>,pair<int,int>>>& A, vector<pair<vector<pair<int,int>>,pair<int,int>>>& subset, int index){
    subsets_of_all_the_stock_combinations_part_2.push_back(subset);
    //Algorithm for choosing the best subset
    if(!subset.empty()){
        vector<int> sum_of_quantities(subset[0].first.size(),0);
        int profit=0;
        for(int i=0; i<subset[0].first.size();i++){
            for(int j=0; j<subset.size()){
                sum_of_quantities[i+1]+=subset[j].first[i+1].second;// i+1, since first pair is (string, stock_number)
                profit+=subset[j].second.first*subset[j].second.second;
            }
        }
        bool allZeros = std::all_of(sum_of_quantities.begin(), sum_of_quantities.end(), [](int element) {
        return element == 0;});//To Check whether all elements are zero or not
        if(allZeros){
            if(max_profit<profit){
                max_profit=profit;
                max_profit_subset.clear();//to clear previous data
                for(int i=0;i<subset.size(),i++){
                    max_profit_subset.push(subset[i].first[0].second);
                }
            }
        }
    }
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
    //return res;
}

vector<vector<pair<vector<pair<int,int>>,pair<int,int>>>> subsets_of_all_the_stock_combinations_part_2;
vector<pair<vector<pair<int,int>>,pair<int,int>>> max_profit_combination; 
vector<int> max_profit_subset;
int max_profit;


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

        // if case  for buy ******************************************************

        if (act == 'b')
        {
            bool ftest = false;
            for (int i = 0; i < buy_update.size(); i++)
            {
                if (buy_update[i].first == stock_name)
                {
                    if (buy_update[i].second >= price)
                    {
                        cout << "No Trade" << endl;
                        ftest = true;
                    }
                    else if (buy_update[i].second < price)
                    {
                        buy_update.erase(buy_update.begin() + i);
                    }
                    break;
                }
            }
            if (ftest == false)
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
                                cout << stock_name << " " << price << " s" << endl;
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
        }

        // next if case  for sell ******************************************************

        if (act == 's')
        {
            bool ftest = false;
            for (int i = 0; i < sell_update.size(); i++)
            {
                if (sell_update[i].first == stock_name)
                {
                    if (sell_update[i].second <= price)
                    {
                        cout << "No Trade" << endl;
                        ftest = true;
                    }
                    else if (sell_update[i].second > price)
                    {
                        sell_update.erase(sell_update.begin() + i);
                    }
                    break;
                }
            }
            if (ftest == false)
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
                                cout << stock_name << " " << price << " b" << endl;
                            }
                            else
                            {
                                bool c = false;
                                for (int i = 0; i < sell_update.size(); i++)
                                {
                                    if (sell_update[i].first == stock_name)
                                    {
                                        if (sell_update[i].second > price)
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
        vector<pair<string,int>> current_stock_info;//Here vector<LC,price-signal pair>, LC:vector<stock_code,quantity>
        //overall_stock_info.push_back(current_stock_info);
        int price;
        char act; 
        istringstream stream(lines[j]);
        current_stock_info.push_back(make_pair(lines[j],j+1));//first element is 1 means the stock has not been used for arbitrage and j+1 is printing which line of input it is
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
            current_stock_info.push_back(make_pair(stock_name_code[i].second,0)); //This means every stock code for a particular stock name is initialised to -1(that means stock is not there)
            //current_stock_info.push_back(0);// stock not there hence quantity is zero:)
        }
        for(int i=0;i<k_values_and_quantity.size();i++){
            current_stock_info[k_values_and_quantity[i].first+1]=make_pair(stock_name_code[k_values_and_quantity[i].first],k_values_and_quantity[i].second);
            //current_stock_info[2*k_values_and_quantity[i].first+2]=k_values_and_quantity[i].second;
        }
        if(act=='b') overall_stock_info.push_back(make_pair(current_stock_info,make_pair(price,1)));// 1 for buy
        else overall_stock_info.push_back(make_pair(current_stock_info,make_pair(price,-1)));// -1 for sell
        //overall_stock_info.push_back(current_stock_info);
        //algorithm to do the trade
        int brk=0;
        for(int i=0;i<overall_stock_info.size()-1;i++){
            if(overall_stock_info[i].first.size()<overall_stock_info[overall_stock_info.size()-1].first.size()){
                while(overall_stock_info[i].first.size()!=overall_stock_info[overall_stock_info.size()-1].first.size()){
                    overall_stock_info[i].first.push_back(make_pair(-1,0));
                }
            }
            if(overall_stock_info[i].first==overall_stock_info[overall_stock_info.size()-1].first){
                if(overall_stock_info[i].second.second==overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info[i].second.second==1 && overall_stock_info[i].second.first>overall_stock_info[overall_stock_info.size()-1].second.first){ //better buy price and the current order cancelled
                    //overall_stock_info.erase(overall_stock_info.begin()+i);
                    overall_stock_info.erase(overall_stock_info.begin()+overall_stock_info.size()-1);
                    brk=1;
                }
                else if(overall_stock_info[i].second.second==overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info[i].second.second==1 && overall_stock_info[i].second.first<=overall_stock_info[overall_stock_info.size()-1].second.first){ //better buy price and the previous order cancelled
                    overall_stock_info.erase(overall_stock_info.begin()+i);
                    //overall_stock_info.erase(overall_stock_info.begin()+overall_stock_info.size()-1);
                }
                else if(overall_stock_info[i].second.second==overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info[i].second.second==-1 && overall_stock_info[i].second.first<overall_stock_info[overall_stock_info.size()-1].second.first){ //better sell price and the current order cancelled
                    //overall_stock_info.erase(overall_stock_info.begin()+i);
                    overall_stock_info.erase(overall_stock_info.begin()+overall_stock_info.size()-1);
                    brk=1;
                }
                else if(overall_stock_info[i].second.second==overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info[i].second.second==-1 && overall_stock_info[i].second.first>=overall_stock_info[overall_stock_info.size()-1].second.first){ //better sell price and the previous order cancelled
                    overall_stock_info.erase(overall_stock_info.begin()+i);
                    //overall_stock_info.erase(overall_stock_info.begin()+overall_stock_info.size()-1);
                }
                else if(overall_stock_info[i].second.second==-overall_stock_info[overall_stock_info.size()-1].second.second && overall_stock_info[i].second.first==-overall_stock_info[overall_stock_info.size()-1].second.first){ //buy-sell cancellation of same LC with same price
                    overall_stock_info.erase(overall_stock_info.begin()+i);
                    overall_stock_info.erase(overall_stock_info.begin()+overall_stock_info.size()-1);
                    brk=1;
                }    
            }
        }
        if(brk==1){
            cout << "No Trade" << endl;
        }
        else{
            max_profit_subset.clear();
            max_profit=INT_MIN();
            subsets(overall_stock_info);//my max
            if(max_profit==INT_MIN()){
                cout << "No Trade" << endl;
            }
            else{
                int iter=0;
                for(int i=0;i<overall_stock_info.size(),i++){
                    if(max_profit_subset[iter]==overall_stock_info[i].first[0].second){
                        iter++;
                        cout << overall_stock_info[i].first[0].first << '#' << endl;
                    }
                    if(iter==max_profit_subset.size()){
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
