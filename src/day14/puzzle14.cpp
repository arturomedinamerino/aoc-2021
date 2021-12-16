#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <vector>

int main() {

  std::ifstream file("input.txt");
  std::string entry;

  std::getline(file, entry);
  std::string polymerTemplate = entry;
  std::cout << polymerTemplate << "\n";

  // remove empty line
  std::getline(file, entry);

  std::string pair, elementToInsert;
  std::vector<std::pair<std::string, std::string>> pairInsertionRules;

  std::string regexStr =
      R"regexbody((\w{2}) -> (\w))regexbody";
  std::regex entryRegex(regexStr);
  std::smatch match;

  // std::string polymerTemplateModified = polymerTemplate;
  while (std::getline(file, entry)) {
    // polymerTemplateModified = polymerTemplate;

    std::regex_match(entry, match, entryRegex);
    pair = match.str(1);
    elementToInsert = match.str(2);

    // polymerTemplate = polymerTemplateModified;
    // polymerTemplateModified.clear();

    pairInsertionRules.push_back(
        std::pair<std::string, std::string>(pair, elementToInsert));
    std::cout << pair << " " << elementToInsert << "\n";
  }

  std::list<char> polymerTemplateAsList;
  for (auto i = 0; i < polymerTemplate.size(); i++) {
    polymerTemplateAsList.push_back(polymerTemplate[i]);
  }

  for (int iterations = 0; iterations < 4; iterations++) {

    std::vector<std::vector<std::list<char>::iterator>> pairPositions;
    std::vector<std::list<char>::iterator> currentPairPositions;
    for (auto rule = pairInsertionRules.begin();
         rule != pairInsertionRules.end(); rule++) {
      char firstChar = (*rule).first[0];
      char secondChar = (*rule).first[1];
      for (auto it = polymerTemplateAsList.begin();
           it != (polymerTemplateAsList.end()); it++) {
        if (*it == firstChar && *std::next(it, 1) == secondChar)
          currentPairPositions.push_back(it);
      }
      pairPositions.push_back(currentPairPositions);
      currentPairPositions.clear();
    }

    for (int i = 0; i < pairInsertionRules.size(); i++) {
      for (int j = 0; j < pairPositions[i].size(); j++) {
        polymerTemplateAsList.insert(std::next(pairPositions[i][j], 1),
                                     pairInsertionRules[i].second[0]);
      }
    }
  }

  for (char i : polymerTemplateAsList) {
    std::cout << i;
  }
  std::cout << "\n";

  std::map<char, int> occurrences;
  for (const auto &element : polymerTemplateAsList) {
    ++occurrences[element];
  }

  std::cout << "Total count:\n";
  for (const auto &letter : occurrences) {
    std::cout << letter.first << " " << letter.second << "\n";
  }

  return 0;
}
