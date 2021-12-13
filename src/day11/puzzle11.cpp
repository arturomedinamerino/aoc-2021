// reading a text file
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

static int counter = 0;

bool allFlashing(int x, int y, const std::vector<std::vector<int>> &energymap) {

}

bool isWithinBorders(int x, int y,
                     const std::vector<std::vector<int>> &energymap) {
  bool isWithinBorders{true};
  if ((x < 0) or (y < 0))
    isWithinBorders = false;
  else if ((x >= energymap[0].size()) or (y >= energymap.size()))
    isWithinBorders = false;
  return isWithinBorders;
}

void flash(int x, int y, std::vector<std::vector<int>> &energymap) {
  counter++;
  energymap[y][x] = -1;
  if (isWithinBorders(x - 1, y, energymap) and energymap[y][x - 1] != -1)
    energymap[y][x - 1] += 1;
  if (isWithinBorders(x - 1, y, energymap) and energymap[y][x - 1] > 9)
    flash(x - 1, y, energymap);

  if (isWithinBorders(x + 1, y, energymap) and energymap[y][x + 1] != -1)
    energymap[y][x + 1] += 1;
  if (isWithinBorders(x + 1, y, energymap) and energymap[y][x + 1] > 9)
    flash(x + 1, y, energymap);

  if (isWithinBorders(x, y - 1, energymap) and energymap[y - 1][x] != -1)
    energymap[y - 1][x] += 1;
  if (isWithinBorders(x, y - 1, energymap) and energymap[y - 1][x] > 9)
    flash(x, y - 1, energymap);

  if (isWithinBorders(x, y + 1, energymap) and energymap[y + 1][x] != -1)
    energymap[y + 1][x] += 1;
  if (isWithinBorders(x, y + 1, energymap) and energymap[y + 1][x] > 9)
    flash(x, y + 1, energymap);

  if (isWithinBorders(x - 1, y - 1, energymap) and
      energymap[y - 1][x - 1] != -1)
    energymap[y - 1][x - 1] += 1;
  if (isWithinBorders(x - 1, y - 1, energymap) and energymap[y - 1][x - 1] > 9)
    flash(x - 1, y - 1, energymap);

  if (isWithinBorders(x + 1, y - 1, energymap) and
      energymap[y - 1][x + 1] != -1)
    energymap[y - 1][x + 1] += 1;
  if (isWithinBorders(x + 1, y - 1, energymap) and energymap[y - 1][x + 1] > 9)
    flash(x + 1, y - 1, energymap);

  if (isWithinBorders(x - 1, y + 1, energymap) and
      energymap[y + 1][x - 1] != -1)
    energymap[y + 1][x - 1] += 1;
  if (isWithinBorders(x - 1, y + 1, energymap) and energymap[y + 1][x - 1] > 9)
    flash(x - 1, y + 1, energymap);

  if (isWithinBorders(x + 1, y + 1, energymap) and
      energymap[y + 1][x + 1] != -1)
    energymap[y + 1][x + 1] += 1;
  if (isWithinBorders(x + 1, y + 1, energymap) and energymap[y + 1][x + 1] > 9)
    flash(x + 1, y + 1, energymap);
}

int main() {
  std::string line;
  std::fstream inputFile("input.txt");

  std::vector<std::vector<int>> energymap;
  std::vector<int> currentLine;

  while (getline(inputFile, line)) {
    for (int i = 0; i < line.size(); i++) {
      currentLine.push_back(line[i] - '0');
    }
    energymap.push_back(currentLine);
    currentLine.clear();
  }

  inputFile.close();

  for (int i = 0; i < 1000; i++) {
    for (int x = 0; x < energymap[0].size(); x++) {
      for (int y = 0; y < energymap.size(); y++) {
        energymap[y][x] += 1;
      }
    }

    for (int x = 0; x < energymap[0].size(); x++) {
      for (int y = 0; y < energymap.size(); y++) {
        if (energymap[y][x] != -1 && energymap[y][x] > 9) {
          flash(x, y, energymap);
        }
      }
    }

    int nFlashed{0};
    for (int x = 0; x < energymap[0].size(); x++) {
      for (int y = 0; y < energymap.size(); y++) {
        if (energymap[y][x] == -1) {
          energymap[y][x] = 0;
          nFlashed++;
        }
      }
    }
    if (nFlashed == (energymap[0].size() * energymap.size())) {
      std::cout << "All flashed in iteration " << i + 1 << "!\n";
      break;
    }
  }

  std::cout << "Counter: " << counter << "\n";

  return 0;
}
