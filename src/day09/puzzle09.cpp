// reading a text file
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

void explore(const int &x, const int &y,
             const std::vector<std::vector<int>> &heightmap,
             std::vector<std::pair<int, int>> &basin) {
  // std::cout << "(" << x << "," << y << "): " << heightmap[y][x] << "\n";

  int newX = x;
  int newY = y;

  if ((x != (heightmap[0].size() - 1)) and heightmap[y][x + 1] != 9) {
    newX = x + 1;
    newY = y;
    std::pair<int, int> newPos(newX, newY);
    if (std::find(basin.begin(), basin.end(), newPos) == basin.end()) {
      basin.push_back(newPos);
      explore(newX, newY, heightmap, basin);
    }
  }
  if ((x != 0) and heightmap[y][x - 1] != 9) {
    newX = x - 1;
    newY = y;
    std::pair<int, int> newPos(newX, newY);
    if (std::find(basin.begin(), basin.end(), newPos) == basin.end()) {
      basin.push_back(newPos);
      explore(newX, newY, heightmap, basin);
    }
  }
  if ((y != (heightmap.size() - 1)) and heightmap[y + 1][x] != 9) {
    newY = y + 1;
    newX = x;
    std::pair<int, int> newPos(newX, newY);
    if (std::find(basin.begin(), basin.end(), newPos) == basin.end()) {
      basin.push_back(newPos);
      explore(newX, newY, heightmap, basin);
    }
  }
  if ((y != 0) and heightmap[y - 1][x] != 9) {
    newY = y - 1;
    newX = x;
    std::pair<int, int> newPos(newX, newY);
    if (std::find(basin.begin(), basin.end(), newPos) == basin.end()) {
      basin.push_back(newPos);
      explore(newX, newY, heightmap, basin);
    }
  }
}

int main() {
  std::string line;
  std::fstream inputFile("input.txt");

  std::vector<std::vector<int>> heightmap;
  std::vector<int> currentLine;

  while (getline(inputFile, line)) {
    for (int i = 0; i < line.size(); i++) {
      currentLine.push_back(line[i] - '0');
    }
    heightmap.push_back(currentLine);
    currentLine.clear();
  }

  inputFile.close();

  std::vector<int> lows;
  std::vector<std::pair<int, int>> lowsPositions;
  bool isLow{false};
  for (int x = 0; x < heightmap[0].size(); x++) {
    for (int y = 0; y < heightmap.size(); y++) {
      if ((x == 0)) {
        if (y == 0) {
          if ((heightmap[y][x] < heightmap[y + 1][x]) and
              (heightmap[y][x] < heightmap[y][x + 1])) {
            isLow = true;
          }
        } else if (y == (heightmap.size() - 1)) {
          if ((heightmap[y][x] < heightmap[y - 1][x]) and
              (heightmap[y][x] < heightmap[y][x + 1])) {
            isLow = true;
          }
        } else {
          if ((heightmap[y][x] < heightmap[y - 1][x]) and
              (heightmap[y][x] < heightmap[y + 1][x]) and
              (heightmap[y][x] < heightmap[y][x + 1])) {
            isLow = true;
          }
        }
      } else if (x == (heightmap[0].size() - 1)) {
        if (y == 0) {
          if ((heightmap[y][x] < heightmap[y + 1][x]) and
              (heightmap[y][x] < heightmap[y][x - 1])) {
            isLow = true;
          }
        } else if (y == (heightmap.size() - 1)) {
          if ((heightmap[y][x] < heightmap[y - 1][x]) and
              (heightmap[y][x] < heightmap[y][x - 1])) {
            isLow = true;
          }
        } else {
          if ((heightmap[y][x] < heightmap[y - 1][x]) and
              (heightmap[y][x] < heightmap[y + 1][x]) and
              (heightmap[y][x] < heightmap[y][x - 1])) {
            isLow = true;
          }
        }

      } else if (y == 0) {
        if ((heightmap[y][x] < heightmap[y + 1][x]) and
            (heightmap[y][x] < heightmap[y][x - 1]) and
            (heightmap[y][x] < heightmap[y][x + 1])) {
          isLow = true;
        }
      } else if (y == (heightmap.size() - 1)) {
        if ((heightmap[y][x] < heightmap[y - 1][x]) and
            (heightmap[y][x] < heightmap[y][x - 1]) and
            (heightmap[y][x] < heightmap[y][x + 1])) {
          isLow = true;
        }

      } else {
        if ((heightmap[y][x] < heightmap[y - 1][x]) and
            (heightmap[y][x] < heightmap[y + 1][x]) and
            (heightmap[y][x] < heightmap[y][x - 1]) and
            (heightmap[y][x] < heightmap[y][x + 1])) {
          isLow = true;
        }
      }
      if (isLow) {
        lows.push_back(heightmap[y][x]);
        lowsPositions.push_back(std::pair<int, int>(x, y));
        isLow = false;
      }
    }
  }

  // Part 1
  int total = 0;
  for (int i = 0; i < lows.size(); i++) {
    total += (lows[i] + 1);
  }
  std::cout << total << std::endl;

  // Part 2
  std::vector<std::pair<int, int>> basin;
  std::vector<std::vector<std::pair<int, int>>> basins;
  for (auto it = lowsPositions.begin(); it != lowsPositions.end(); it++) {
    std::cout << (*it).first << " " << (*it).second << "\n";
    explore((*it).first, (*it).second, heightmap, basin);
    basins.push_back(basin);
    basin.clear();
  }

  std::vector<int> sizes;
  for (auto it = basins.begin(); it != basins.end(); it++) {
    sizes.push_back((*it).size());
  }
  std::sort(sizes.begin(), sizes.end(), std::greater<int>());
  std::cout << sizes[0] * sizes[1] * sizes[2] << std::endl;

  return 0;
}
