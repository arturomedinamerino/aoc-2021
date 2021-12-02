#include <fstream>
#include <iostream>
#include <regex>

int main() {

  // std::ifstream file("test_input.txt");
  std::ifstream file("input.txt");
  std::string entry;

  int depth{0};
  int horizontalPos{0};
  int aim{0};

  int digit{0};
  std::string command;

  std::string regexStr = R"regexbody((forward|down|up) (\d{1}))regexbody";
  std::regex entryRegex(regexStr);
  std::smatch match;

  // Part 1
  while (std::getline(file, entry)) {
    std::regex_match(entry, match, entryRegex);
    digit = std::stoi(match.str(2));
    command = match.str(1);

    if (command == "forward") {
      horizontalPos += digit;
    } else if (command == "down") {
      depth += digit;
    } else if (command == "up") {
      depth -= digit;
    }

    // std::cout << command << " " << digit << "\n";
  }
  std::cout << horizontalPos << " " << depth << "\n";
  std::cout << horizontalPos * depth << "\n";

  // Part 2
  depth = 0;
  horizontalPos = 0;
  aim = 0;

  // Start reading from the beggining of the file
  file.clear();
  file.seekg(0, std::ios::beg);

  while (std::getline(file, entry)) {
    std::regex_match(entry, match, entryRegex);
    digit = std::stoi(match.str(2));
    command = match.str(1);

    if (command == "forward") {
      horizontalPos += digit;
      depth += (aim * (digit));
    } else if (command == "down") {
      aim += digit;
    } else if (command == "up") {
      aim -= digit;
    }

    // std::cout << command << " " << digit << "\n";
  }
  std::cout << horizontalPos << " " << depth << "\n";
  std::cout << horizontalPos * depth << "\n";

  return 0;
}
