#include "receiver.h"
#include <string>
#include <vector>

using namespace std;

int main()
{
    Receiver rcv;
    vector<pair<string, int>> stock_prices; // To keep track of the best prices
    string input_file = rcv.readIML();
    input_file.pop_back();
    vector<string> lines;
    string line;

    istringstream stream(input_file);

    while (getline(stream, line, '#'))
    {
        // Remove any trailing '#' character
        if (!line.empty() && line.back() == '#')
        {
            line.pop_back();
        }

        lines.push_back(line);
    }

    int j = 0;
    while (j < lines.size())
    {
        string stock_name;
        string p;
        int price;
        char act;
        istringstream stream(lines[j]);
        stream >> stock_name >> p >> act;
        price = stoi(p);

        if (act == 'b')
        {
            bool check = false;
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
        j++;
    }
    return 0;
}