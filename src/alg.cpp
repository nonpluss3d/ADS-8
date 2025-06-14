// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return;
  }

  std::string word;
  int ch;

  while ((ch = file.get()) != EOF) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(std::tolower(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> list;
  tree.getFrequencyList(list);

  std::sort(list.begin(), list.end(),
            [](const auto& a, const auto& b) { return b.second < a.second; });

  std::ofstream out("result/freq.txt");
  for (const auto& [w, f] : list) {
    out << w << " " << f << "\n";
    std::cout << w << " " << f << "\n";
  }
  out.close();
}
