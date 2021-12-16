// reading a text file
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

int firstIndexOfBoard(int position) {
  int firstIndexOfBoard = 0;
  for (firstIndexOfBoard = position; (firstIndexOfBoard % 25) != 0;
       firstIndexOfBoard -= 5) {
  }
  return firstIndexOfBoard;
}

void printBoard(const std::vector<int> &boards, int index) {
  std::cout << "Printing board " << (index / 25) + 1 << "\n";
  for (int i = index; i < index + 25; i++) {
    std::cout << boards[i];
    if ((i + 1) % 5 == 0) {
      std::cout << "\n";
    } else {
      std::cout << " ";
    }
  }
}

void printAllBoards(const std::vector<int> &boards) {
  for (int i = 0; i < boards.size(); i += 25) {
    printBoard(boards, i);
  }
}

int checkBingoLines(const std::vector<int> &hasBeenDrawn,
                    const std::vector<int> &ignoredBoards) {
  int bingoIndex = -1;
  for (int i = 0; i < hasBeenDrawn.size() && bingoIndex == -1; i += 5) {
    if (ignoredBoards.size() != 0 &&
        std::find(ignoredBoards.begin(), ignoredBoards.end(),
                  firstIndexOfBoard(i)) != ignoredBoards.end()) {
      // std::cout << "Skipping " << firstIndexOfBoard(i) / 25 + 1 << "\n";
      continue;
    }

    // 0   1  2  3  4
    // X   X  X  X  X
    // 5   6  7  8  9
    // X   X  X  X  X
    // 10 11 12 13 14
    // X   X  X  X  X
    // 15 16 17 18 19
    // X   X  X  X  X
    // 20 21 22 23 24
    // X   X  X  X  X

    if (((hasBeenDrawn[i] == 1) && (hasBeenDrawn[i + 1] == 1) &&
         (hasBeenDrawn[i + 2] == 1) && (hasBeenDrawn[i + 3] == 1) &&
         (hasBeenDrawn[i + 4] == 1))) {
      std::cout << "Line!\n";
      bingoIndex = i;
      break;
    }
  }
  for (int i = 0; i < hasBeenDrawn.size() && bingoIndex == -1; i += 25) {
    if (std::find(ignoredBoards.begin(), ignoredBoards.end(),
                  firstIndexOfBoard(i)) != ignoredBoards.end()) {
      // std::cout << "Skipping " << firstIndexOfBoard(i) / 25 + 1 << "\n";
      continue;
    }
    // std::cout << "\ni: " << i << "\n\n";
    for (int j = i; j < (i + 5); j += 1) {

      // std::cout << "j: " << j << "\n";
      if (((hasBeenDrawn[j] == 1) && (hasBeenDrawn[j + 5] == 1) &&
           (hasBeenDrawn[j + 10] == 1) && (hasBeenDrawn[j + 15] == 1) &&
           (hasBeenDrawn[j + 20] == 1))) {
        std::cout << "Column!\n";
        bingoIndex = i;
        break;
      }
    }
  }
  return bingoIndex;
}

int main() {
  typedef std::vector<std::vector<int>> matrix;
  std::vector<matrix> matrixes;
  std::vector<int> ignoredBoards;

  std::string line;
  std::fstream inputFile("input.txt");

  std::string drawnNumbersStr;
  std::vector<int> drawnNumbers;
  getline(inputFile, drawnNumbersStr);

  // Drawn numbers
  std::istringstream iss(drawnNumbersStr);
  std::string token;
  while (std::getline(iss, token, ',')) {
    drawnNumbers.push_back(std::stoi(token));
  }

  // Discard first empty line
  getline(inputFile, line);

  // Bingo boards
  int number;
  std::vector<int> boardNumbers;
  while (getline(inputFile, line)) {
    if (line.empty()) {
      continue;
    }

    // Parse numbers in board line
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ' ')) {
      // std::cout << "token: " << token << "\n";
      if (not token.empty() and token != " ") {
        number = std::stoi(token);
        boardNumbers.push_back(number);
      }
    }
  }

  inputFile.close();

  int bingoIndex = -1;
  int lastDrawnNumber = -1;
  std::vector<int> hasBeenDrawn(boardNumbers.size(), 0);
  for (int i = 0; i < drawnNumbers.size(); i++) {
    for (int j = 0; j < boardNumbers.size(); j++) {
      if (boardNumbers[j] == drawnNumbers[i]) {
        hasBeenDrawn[j] = 1;
      }
    }
    if ((bingoIndex = checkBingoLines(hasBeenDrawn, ignoredBoards)) != -1) {
      std::cout << "Bingo! Index of the line is: " << bingoIndex << "\n";
      std::cout << boardNumbers[bingoIndex] << " ";
      std::cout << boardNumbers[bingoIndex + 1] << " ";
      std::cout << boardNumbers[bingoIndex + 2] << " ";
      std::cout << boardNumbers[bingoIndex + 3] << " ";
      std::cout << boardNumbers[bingoIndex + 4] << "\n";
      lastDrawnNumber = drawnNumbers[i];
      std::cout << "Last drawn number was: " << lastDrawnNumber << "\n";
      break;
    }
  }

  int firstIndexOnThatBoard = bingoIndex;
  for (int firstIndexOnThatBoard = bingoIndex;
       (firstIndexOnThatBoard % 25) != 0; firstIndexOnThatBoard -= 5) {
  }
  std::cout << "First index on that board: " << firstIndexOnThatBoard << "\n";

  int total{0};
  for (int i = firstIndexOnThatBoard; i < firstIndexOnThatBoard + 25; i++) {
    if (hasBeenDrawn[i] == 0)
      total += boardNumbers[i];
  }

  std::cout << "Total: " << total << std::endl;
  std::cout << "Result: " << total * lastDrawnNumber << std::endl;

  // Part 2
  int totalBoards = boardNumbers.size() / 25;
  int remmainingBoards = totalBoards;
  bingoIndex = -1;
  lastDrawnNumber = -1;
  std::fill(hasBeenDrawn.begin(), hasBeenDrawn.end(), 0);
  for (int i = 0; i < drawnNumbers.size() && remmainingBoards > 0; i++) {
    for (int j = 0; j < boardNumbers.size(); j++) {
      if (boardNumbers[j] == drawnNumbers[i]) {
        lastDrawnNumber = drawnNumbers[i];
        hasBeenDrawn[j] = 1;

        // TODO could be optimized by only checking the last modified board
        if ((bingoIndex = checkBingoLines(hasBeenDrawn, ignoredBoards)) != -1) {
          firstIndexOnThatBoard = firstIndexOfBoard(bingoIndex);
          ignoredBoards.push_back(firstIndexOnThatBoard);
          remmainingBoards--;
          printBoard(hasBeenDrawn, firstIndexOnThatBoard);
          std::cout << "Bingo! Index of the line/column is: " << bingoIndex
                    << "\n";
          std::cout << "First index of that board is: " << firstIndexOnThatBoard
                    << "\n";
          std::cout << "Size of ignoredBoards " << ignoredBoards.size() << "\n";
          std::cout << "Remmaining boards: " << remmainingBoards << "\n";
          std::cout << "Last drawn number: " << lastDrawnNumber << "\n";
          if (remmainingBoards == 0) {
            break;
          } else {
            continue;
          }
        }
      }
    }
  }

  total = 0;
  for (int i = firstIndexOnThatBoard; i < firstIndexOnThatBoard + 25; i++) {
    if (hasBeenDrawn[i] == 0)
      total += boardNumbers[i];
  }
  // printAllBoards(hasBeenDrawn);

  std::cout << "Total: " << total << std::endl;
  std::cout << "Result: " << total * lastDrawnNumber << std::endl;

  return 0;
}
