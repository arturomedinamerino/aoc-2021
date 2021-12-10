
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

int main() {

  std::ifstream inputFile("input.txt");
  std::string entry;
  std::vector<std::vector<std::string>> signals;
  std::vector<std::string> currentEntrySignals;
  std::vector<std::vector<std::string>> digits;
  std::vector<std::string> currentEntryDigits;

  while (getline(inputFile, entry)) {
    if (entry.empty()) {
      continue;
    }
    currentEntrySignals.clear();
    currentEntryDigits.clear();

    std::istringstream iss(entry);
    std::string token;
    bool parseDigits = false;
    while (std::getline(iss, token, ' ')) {
      // std::cout << "token: " << token << "\n";
      if (token == "|") {
        parseDigits = true;
        continue;
      }

      if (parseDigits == true) {
        if (not token.empty() and token != " ") {
          currentEntryDigits.push_back(token);
        }
      } else {
        if (not token.empty() and token != " ") {
          currentEntrySignals.push_back(token);
        }
      }
    }
    signals.push_back(currentEntrySignals);
    digits.push_back(currentEntryDigits);
  }

  // std::vector<char> top;
  // std::vector<char> bottom;
  // std::vector<char> topLeft;
  // std::vector<char> topRight;
  // std::vector<char> bottomLeft;
  // std::vector<char> bottomRigth;
  // std::vector<char> middle;
  std::string segments{"abcdefg"};
  std::map<int, std::string> signalMap;
  for (auto entrySignals = signals.begin(); entrySignals != signals.end();
       entrySignals++) {
    for (auto it = (*entrySignals).begin(); it != (*entrySignals).end(); it++) {
      std::cout << *it << " ";
      if ((*it).size() == 2) {
        signalMap.emplace(1, *it);
      } else if ((*it).size() == 4) {
        signalMap.emplace(4, *it);
      } else if ((*it).size() == 3) {
        signalMap.emplace(7, *it);
      } else if ((*it).size() == 7) {
        signalMap.emplace(8, *it);
      }
    }
    // for (auto i = 0; i < segments.size(); i++) {
    // if (signalMap[7].at(segments[i]) != signalMap[7].end() &&
    //}
    std::cout << "\n";
  }

  int specialDigits = 0;
  for (auto entryDigits = digits.begin(); entryDigits != digits.end();
       entryDigits++) {
    for (auto it = (*entryDigits).begin(); it != (*entryDigits).end(); it++) {
      if ((*it).size() == 2 or (*it).size() == 4 or (*it).size() == 3 or
          (*it).size() == 7) {
        specialDigits++;
      }
    }
  }
  std::cout << specialDigits << std::endl;

  return 0;
}
