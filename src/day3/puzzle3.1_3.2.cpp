#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::ifstream file("input.txt");
  std::string entry;
  std::vector<std::string> entries;

  int binaryNumberLength = 12;
  std::vector<int> nOfOnes(binaryNumberLength, 0);
  std::vector<int> nOfZeroes(binaryNumberLength, 0);

  std::vector<int> gamma(binaryNumberLength, 0);
  std::vector<int> epsilon(binaryNumberLength, 0);

  // Part 1

  // Determine most common number (0 or 1) in each entry
  while (std::getline(file, entry)) {
    for (int i = 0; i < entry.length(); i++) {
      if (entry[i] == '1')
        nOfOnes[i] = nOfOnes[i] + 1;
      if (entry[i] == '0')
        nOfZeroes[i] = nOfZeroes[i] + 1;
    }

    entries.push_back(entry);
  }
  for (int i = 0; i < nOfOnes.size(); i++) {
    if (nOfOnes[i] > nOfZeroes[i]) {
      gamma[i] = 1;
      epsilon[i] = 0;
    } else {
      gamma[i] = 0;
      epsilon[i] = 1;
    }
  }

  int dec_value = 0;
  int base = 1;
  int len = gamma.size();
  for (int i = len - 1; i >= 0; i--) {
    if (gamma[i] == 1)
      dec_value += base;
    base = base * 2;
  }
  std::cout << dec_value << "\n";

  int gammaDec = dec_value;

  dec_value = 0;
  base = 1;
  len = epsilon.size();
  for (int i = len - 1; i >= 0; i--) {
    if (epsilon[i] == 1)
      dec_value += base;
    base = base * 2;
  }
  std::cout << dec_value << "\n";

  int epsilonDec = dec_value;

  std::cout << gammaDec * epsilonDec << "\n";

  // Part 2

  std::vector<std::string> candidateEntries{entries};
  std::vector<std::string> newEntries;
  for (int i = 0; (i < binaryNumberLength) && (candidateEntries.size() > 1);
       i++) {

    int numberOfOnes{0}, numberOfZeroes{0};
    bool chooseOnes = false;
    for (auto currentEntry = candidateEntries.begin();
         currentEntry != candidateEntries.end(); currentEntry++) {
      if (((*currentEntry)[i] == '1')) {
        numberOfOnes += 1;
      } else {
        numberOfZeroes += 1;
      }
    }

    if (numberOfZeroes <= numberOfOnes)
      chooseOnes = true;

    for (auto currentEntry = candidateEntries.begin();
         currentEntry != candidateEntries.end(); currentEntry++) {
      if ((chooseOnes == false) && ((*currentEntry)[i] == '0')) {
        newEntries.push_back(*currentEntry);
      } else if ((chooseOnes == true) && ((*currentEntry)[i] == '1')) {
        newEntries.push_back(*currentEntry);
      }
    }
    candidateEntries = newEntries;
    newEntries.clear();

    // for (auto currentEntry = candidateEntries.begin(); currentEntry !=
    // candidateEntries.end(); currentEntry++) { std::cout << *currentEntry <<
    // "\n";
    //}
    // std::cout <<  "\n";
  }

  dec_value = 0;
  base = 1;
  len = binaryNumberLength;
  for (int i = len - 1; i >= 0; i--) {
    if (candidateEntries[0][i] == '1')
      dec_value += base;
    base = base * 2;
  }
  std::cout << dec_value << "\n";
  int oxigen = dec_value;

  candidateEntries = entries;
  for (int i = 0; (i < binaryNumberLength) && (candidateEntries.size() > 1);
       i++) {

    int numberOfOnes{0}, numberOfZeroes{0};
    bool chooseOnes = false;
    for (auto currentEntry = candidateEntries.begin();
         currentEntry != candidateEntries.end(); currentEntry++) {
      if (((*currentEntry)[i] == '1')) {
        numberOfOnes += 1;
      } else {
        numberOfZeroes += 1;
      }
    }

    if (numberOfOnes < numberOfZeroes)
      chooseOnes = true;

    for (auto currentEntry = candidateEntries.begin();
         currentEntry != candidateEntries.end(); currentEntry++) {
      if ((chooseOnes == false) && ((*currentEntry)[i] == '0')) {
        newEntries.push_back(*currentEntry);
      } else if ((chooseOnes == true) && ((*currentEntry)[i] == '1')) {
        newEntries.push_back(*currentEntry);
      }
    }
    candidateEntries = newEntries;
    newEntries.clear();

    // for (auto currentEntry = candidateEntries.begin(); currentEntry !=
    // candidateEntries.end(); currentEntry++) { std::cout << *currentEntry <<
    // "\n";
    //}
    // std::cout <<  "\n";
  }

  dec_value = 0;
  base = 1;
  len = binaryNumberLength;
  for (int i = len - 1; i >= 0; i--) {
    if (candidateEntries[0][i] == '1')
      dec_value += base;
    base = base * 2;
  }
  std::cout << dec_value << "\n";
  int co2 = dec_value;

  std::cout << oxigen * co2 << std::endl;

  return 0;
}
