#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main() {

  std::ifstream file("input.txt");
  std::string entry;

  int x1, y1, x2, y2;
  std::vector<std::vector<int>> matrix(1000, std::vector<int>(1000, 0));
  // std::vector<std::vector<int>> matrix(10, std::vector<int>(10, 0));

  std::string regexStr =
      R"regexbody((\d{1,3}),(\d{1,3}) -> (\d{1,3}),(\d{1,3}))regexbody";
  std::regex entryRegex(regexStr);
  std::smatch match;

  // Part 1
  while (std::getline(file, entry)) {
    std::regex_match(entry, match, entryRegex);
    x1 = std::stoi(match.str(1));
    y1 = std::stoi(match.str(2));
    x2 = std::stoi(match.str(3));
    y2 = std::stoi(match.str(4));
    if (x1 == x2) {
      if (y1 < y2) {
        for (int i = y1; i <= y2; i++) {
          matrix[x1][i] += 1;
        }
      } else if (y2 < y1) {
        for (int i = y2; i <= y1; i++) {
          matrix[x1][i] += 1;
        }
      }
    } else if (y1 == y2) {
      if (x1 < x2) {
        for (int i = x1; i <= x2; i++) {
          matrix[i][y1] += 1;
        }
      } else if (x2 < x1) {
        for (int i = x2; i <= x1; i++) {
          matrix[i][y1] += 1;
        }
      }
    } else {
      continue;
    }
  }

  int total{0};
  for (int j = 0; j < matrix.size(); j++) {
    for (int i = 0; i < matrix[j].size(); i++) {
      // std::cout << matrix[i][j] << " ";
      if (matrix[i][j] >= 2) {
        total++;
      }
    }
    // std::cout <<  "\n";
  }
  std::cout << "Total: " << total << "\n";

  // Part 2
  // Start reading from the beggining of the file
  std::fill(matrix.begin(), matrix.end(), std::vector<int>(1000, 0));
  file.clear();
  file.seekg(0, std::ios::beg);
  while (std::getline(file, entry)) {
    std::regex_match(entry, match, entryRegex);
    x1 = std::stoi(match.str(1));
    y1 = std::stoi(match.str(2));
    x2 = std::stoi(match.str(3));
    y2 = std::stoi(match.str(4));
    if (y1 == y2) {
      if (x1 < x2) {
        for (int x = x1; x <= x2; x++) {
          matrix[y1][x] += 1;
        }
      } else if (x2 < x1) {
        for (int x = x2; x <= x1; x++) {
          matrix[y1][x] += 1;
        }
      }
    } else if (x1 == x2) {
      if (y1 < y2) {
        for (int y = y1; y <= y2; y++) {
          matrix[y][x1] += 1;
        }
      } else if (y2 < y1) {
        for (int y = y2; y <= y1; y++) {
          matrix[y][x1] += 1;
        }
      }
    } else {
      int x{0}, y{0};
      std::cout << "Entry " << entry << "\n";
      if ((y1 < y2) && (x1 < x2)) {
        for (y = y1, x = x1; y <= y2 && x <= x2; y++, x++) {
          matrix[y][x] += 1;
        }
      } else if ((y1 < y2) && (x1 > x2)) {
        for (y = y2, x = x2; y >= y1 && x <= x1; y--, x++) {
          matrix[y][x] += 1;
        }
      } else if ((y1 > y2) && (x1 < x2)) {
        for (y = y1, x = x1; y >= y2 && x <= x2; y--, x++) {
          matrix[y][x] += 1;
        }
      } else if ((y1 > y2) && (x1 > x2)) {
        for (y = y2, x = x2; y <= y1 && x <= x1; y++, x++) {
          matrix[y][x] += 1;
        }
      }
    }
  }

  total = 0;
  // std::cout << "  1 1 2 3 4 5 6 7 8 9\n";
  for (int y = 0; y < matrix.size(); y++) {
    // std::cout << y << " ";
    for (int x = 0; x < matrix[y].size(); x++) {
      // std::cout << matrix[y][x] << " ";
      if (matrix[y][x] >= 2) {
        total++;
      }
    }
    // std::cout << "\n";
  }
  std::cout << "Total: " << total << "\n";

  return 0;
}
