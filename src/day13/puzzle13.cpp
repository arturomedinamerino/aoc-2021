#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

void printPaper(std::vector<std::vector<int>> &paper) {
  for (int y = 0; y < paper.size(); y++) {
    for (int x = 0; x < paper[0].size(); x++) {
      if (paper[y][x] == 0)
        std::cout << "#";
      else
        std::cout << ".";
    }
    std::cout << "\n";
  }
}

void fold(const std::string &axis, const int &axisNumber,
          std::vector<std::vector<int>> &paper) {
  if (axis == "x") {
    for (int y = 0; y < paper.size(); y++) {
      int nElementsInRow = paper[y].size();
      for (int x = 0; x < axisNumber; x++) {
        paper[y][x] = paper[y][x] * paper[y][nElementsInRow - 1 - x];
      }
      paper[y].erase(paper[y].begin() + axisNumber, paper[y].end());
      paper[y].shrink_to_fit();
    }
  } else if (axis == "y") {
    for (int x = 0; x < paper[0].size(); x++) {
      int nElementsInColumn = paper.size();
      for (int y = 0; y < axisNumber; y++) {
        paper[y][x] = paper[y][x] * paper[nElementsInColumn - 1 - y][x];
      }
    }
    paper.erase(paper.begin() + axisNumber, paper.end());
    paper.shrink_to_fit();
  }
}

void countDots(std::vector<std::vector<int>> &paper) {
  int dots{0};
  for (int y = 0; y < paper.size(); y++) {
    for (int x = 0; x < paper[0].size(); x++) {
      if (paper[y][x] == 0)
        dots++;
    }
  }
  std::cout << "Dots: " << dots << "\n";
}

int main() {

  std::ifstream file("input.txt");
  std::string entry;

  int x, y;
  std::vector<std::vector<int>> paper(3000, std::vector<int>(3000, 1));

  std::string regexStr =
      R"regexbody((\d+),(\d+))regexbody";
  std::regex entryRegex(regexStr);
  std::smatch match;

  while (std::getline(file, entry)) {
    if (entry.empty())
      break;

    std::regex_match(entry, match, entryRegex);
    x = std::stoi(match.str(1));
    y = std::stoi(match.str(2));
    std::cout << x << " " << y << "\n";
    paper[y][x] = 0;
  }

  std::string axis;
  int axisNumber;
  std::vector<std::pair<std::string, int>> axisNumbers;

  std::string regexStrFolds =
      R"regexbody(fold along (\w{1})=(\d+))regexbody";
  std::regex entryRegexFolds(regexStrFolds);
  std::smatch matchFolds;

  while (std::getline(file, entry)) {
    std::regex_match(entry, matchFolds, entryRegexFolds);
    axis = matchFolds.str(1);
    axisNumber = std::stoi(matchFolds.str(2));
    axisNumbers.push_back(std::pair<std::string, int>(axis, axisNumber));
  }

  // TODO we should not assume that x comes at [0] and y at [1]
  paper.erase(paper.begin() + axisNumbers[1].second * 2 + 1, paper.end());
  paper.shrink_to_fit();
  for (int y = 0; y < paper.size(); y++) {
    paper[y].erase(paper[y].begin() + axisNumbers[0].second * 2 + 1,
                   paper[y].end());
    paper[y].shrink_to_fit();
  }

  std::cout << "Initial number of dots..."
            << "\n";
  countDots(paper);
  std::cout << "Start folding..."
            << "\n";
  for (int i = 0; i < axisNumbers.size(); i++) {
    std::cout << "Folding along " << axisNumbers[i].first << "="
              << axisNumbers[i].second << "\n";
    fold(axisNumbers[i].first, axisNumbers[i].second, paper);
    // printPaper(paper);
    countDots(paper);
  }

  printPaper(paper);

  return 0;
}
