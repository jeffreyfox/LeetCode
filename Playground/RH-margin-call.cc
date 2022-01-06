// https://leetcode.com/playground/XfAK8ggA

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;

void trade(const string &symbol, const string &action, int shares, int price, map<string, int> &symbol2shares, int &cash) {
  if (action == "B") {
    cash -= shares * price;
    symbol2shares[symbol] += shares;
  } else { // "S"
    cash += shares * price;
    symbol2shares[symbol] -= shares;
    if (symbol2shares[symbol] == 0) {
      symbol2shares.erase(symbol);
    }
  }
}

void marginCall(map<string, int> &symbol2shares,
  map<string, int> &symbol2price, int &cash) {
  if (cash >= 0) return;
  
  map<int, set<string>> price2symbols;
  for (const auto &[symbol, price] : symbol2price) {
    price2symbols[price].insert(symbol);
  }

  while (cash < 0) {
    assert(!price2symbols.empty());
    int price = price2symbols.rbegin()->first;
    const string &symbol = *price2symbols.rbegin()->second.begin();
    int max_shares = symbol2shares[symbol];
    int shares_to_sell = min(max_shares, (-cash-1) / price + 1);
    trade(symbol, "S", shares_to_sell, price, symbol2shares, cash);
    price2symbols.rbegin()->second.erase(symbol);
  }
}

vector<vector<string>> getUserPortfolio(const vector<vector<string>>& records) {
  map<string, int> symbol2shares;
  map<string, int> symbol2price;
  int cash = 1000;
  for (const auto &record : records) {
    const auto symbol = record[1];
    const auto action = record[2];
    const int shares = stoi(record[3]);
    const int price = stoi(record[4]);
    trade(symbol, action, shares, price, 
    symbol2shares, cash);
    symbol2price[symbol] = price;
    marginCall(symbol2shares, symbol2price, cash);
  }
  vector<vector<string>> portfolio;
  portfolio.push_back({"CASH", to_string(cash)});
  for (const auto &[symbol, shares] : symbol2shares) {
    portfolio.push_back({symbol, to_string(shares)});
  }
  return portfolio;
}

void printPortfolio(const vector<vector<string>> &portfolio) {
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
  printPortfolio(getUserPortfolio(records1));
  // margin-call
  vector<vector<string>> records2 = {
    {"1", "AAPL", "B", "10", "100"},
    {"2", "AAPL", "S", "2", "80"},
    {"3", "GOOG", "B", "15", "20"},
  };

  // should be
  // [["CASH", "20"], ["AAPL", "6"], ["GOOG", "15"]]
  printPortfolio(getUserPortfolio(records2));
  
  return 0;
}
