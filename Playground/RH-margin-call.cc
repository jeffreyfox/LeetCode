// https://leetcode.com/playground/XfAK8ggA

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
using namespace std;

void ProcessTrade(const string &symbol, const string &action, int shares, int price, map<string, int> &symbol2shares, int &cash) {
  if (action == "B") {  // "B": buy
    cash -= shares * price;
    symbol2shares[symbol] += shares;
  } else { // "S": sell
    cash += shares * price;
    symbol2shares[symbol] -= shares;
  }
}

vector<vector<string>> getUserPortfolio(const vector<vector<string>>& records) {
  map<string, int> symbol2shares;
  int cash = 1000;
  for (const auto &record : records) {
    const auto symbol = record[1];
    const auto action = record[2];
    const int shares = stoi(record[3];
    const int price = stoi(record[4]);
    ProcessTrade(symbol, action, shares, price, symbol2shares, cash);
  }
  vector<vector<string>> portfolio;
  portfolio.push_back({"CASH", to_string(cash)});
  for (const auto &[symbol, shares] : symbol2shares) {
    portfolio.push_back({symbol, to_string(shares)});
  }
  return portfolio;
}

void PrintPortfolio(const vector<vector<string>> &portfolio) {
  for (const auto &entry : portfolio) {
    std::cout << entry[0] << " " << entry[1] << std::endl;
  }
  std::cout << std::endl;
}
                            
int main() {
  vector<vector<string>> records1 = {
    {"1", "AAPL", "B", "10", "10"},
    {"3", "GOOG", "B", "20", "5"},
    {"3", "AAPL", "S", "5", "15"}
  };
  // should be
  // [["CASH", "875"], ["AAPL", "5"], ["GOOG", "20"]]
  PrintPortfolio(getUserPortfolio(records1));

  // margin-call
  vector<vector<string>> records2 = {
    {"1", "AAPL", "B", "10", "100"},
    {"2", "AAPL", "S", "2", "80"},
    {"3", "GOOG", "B", "15", "20"}
  };
  
  return 0;
}
