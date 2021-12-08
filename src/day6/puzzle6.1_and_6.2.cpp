#include <iostream>
#include <vector>

#include <numeric>

int main() {
  // std::vector<int> lanternfishes{3,4,3,1,2};
  std::vector<int> lanternfishes{
      1, 4, 3, 3, 1, 3, 1, 1, 1, 2, 1, 1, 1, 4, 4, 1, 5, 5, 3, 1, 3, 5, 2, 1,
      5, 2, 4, 1, 4, 5, 4, 1, 5, 1, 5, 5, 1, 1, 1, 4, 1, 5, 1, 1, 1, 1, 1, 4,
      1, 2, 5, 1, 4, 1, 2, 1, 1, 5, 1, 1, 1, 1, 4, 1, 5, 1, 1, 2, 1, 4, 5, 1,
      2, 1, 2, 2, 1, 1, 1, 1, 1, 5, 5, 3, 1, 1, 1, 1, 1, 4, 2, 4, 1, 2, 1, 4,
      2, 3, 1, 4, 5, 3, 3, 2, 1, 1, 5, 4, 1, 1, 1, 2, 1, 1, 5, 4, 5, 1, 3, 1,
      1, 1, 1, 1, 1, 2, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1,
      1, 1, 1, 1, 1, 4, 5, 1, 3, 1, 4, 4, 2, 3, 4, 1, 1, 1, 5, 1, 1, 1, 4, 1,
      5, 4, 3, 1, 5, 1, 1, 1, 1, 1, 5, 4, 1, 1, 1, 4, 3, 1, 3, 3, 1, 3, 2, 1,
      1, 3, 1, 1, 4, 5, 1, 1, 1, 1, 1, 3, 1, 4, 1, 3, 1, 5, 4, 5, 1, 1, 5, 1,
      1, 4, 1, 1, 1, 3, 1, 1, 4, 2, 3, 1, 1, 1, 1, 2, 4, 1, 1, 1, 1, 1, 2, 3,
      1, 5, 5, 1, 4, 1, 1, 1, 1, 3, 3, 1, 4, 1, 2, 1, 3, 1, 1, 1, 3, 2, 2, 1,
      5, 1, 1, 3, 2, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 5, 1, 1, 1, 1,
      3, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1};

  std::vector<int> totalSizes;
  int groupSize{5};
  int numberOfGroups = 300 / groupSize;
  int simulationDays{80};
  int initialSize = lanternfishes.size();
  std::vector<std::vector<int>> groups(numberOfGroups,
                                       std::vector<int>(groupSize, 0));
  int i, j;
  for (i = 0, j = 0; i < initialSize; i = i + groupSize, j++) {
    groups[j].assign(lanternfishes.begin() + i,
                     lanternfishes.begin() + i + groupSize);
  }
  for (i = 0; i < groups.size(); i++) {
    for (int day = 0; day < simulationDays; day++) {
      initialSize = groups[i].size();
      for (int k = 0; k < initialSize; k++) {
        if (groups[i][k] == 0) {
          groups[i][k] = 6;
          groups[i].push_back(8);
        } else {
          groups[i][k]--;
        }
      }
      std::cout << "Size: " << groups[i].size() << "\n";
    }
    std::cout << "Final size: " << groups[i].size() << "\n";
    totalSizes.push_back(groups[i].size());
  }
  std::cout << std::accumulate(totalSizes.begin(), totalSizes.end(), 0);

  return 0;
}
