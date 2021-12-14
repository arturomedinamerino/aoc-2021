#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

struct node {
  std::string name;
  bool small;
  std::vector<std::shared_ptr<node>> connections;
};

bool isSmall(std::string name) {
  std::string regexStr =
      R"(([a-z]+))";
  std::regex nameRegex(regexStr);
  std::smatch match;
  if (std::regex_match(name, match, nameRegex))
    return true;
  else
    return false;
}

int main() {

  std::ifstream file("input.txt");
  std::string entry;

  std::string firstCaveName, secondCaveName;
  std::map<std::string, std::shared_ptr<node>> caves;

  std::string regexStr =
      R"regexbody((\w+)-(\w+))regexbody";
  std::regex entryRegex(regexStr);
  std::smatch match;

  while (std::getline(file, entry)) {
    std::regex_match(entry, match, entryRegex);
    firstCaveName = match.str(1);
    secondCaveName = match.str(2);
    std::cout << firstCaveName << " " << secondCaveName << "\n";
    if (caves.find(firstCaveName) == caves.end()) {
      bool small = isSmall(firstCaveName);
      std::shared_ptr<node> newNode = std::make_shared<node>();
      newNode->name = firstCaveName;
      newNode->small = isSmall;
      caves.emplace(firstCaveName, newNode);
    }
    if (caves.find(secondCaveName) == caves.end()) {
      bool small = isSmall(secondCaveName);
      std::shared_ptr<node> newNode = std::make_shared<node>();
      newNode->name = secondCaveName;
      newNode->small = isSmall;
      caves.emplace(firstCaveName, newNode);
    }
    auto firstCaveIt = caves.find(firstCaveName);
    auto secondCaveIt = caves.find(secondCaveName);
    firstCaveIt->second->connections.push_back(secondCaveIt->second);
    secondCaveIt->second->connections.push_back(firstCaveIt->second);
  }

  return 0;
}
