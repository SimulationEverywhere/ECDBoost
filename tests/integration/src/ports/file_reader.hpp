#include <vector>
#include <iostream>
#include <fstream>


template<class TIME, class MSG>
class FileReader: public port<TIME, MSG> {
  public:
    mutable int vector_index;
    std::vector<int> values;

    explicit FileReader(const std::string &name, const TIME &polling) noexcept :
      port<TIME, MSG>(name, polling)
    {
      std::ifstream infile("input.txt");
      int v;
      while (infile >> v) { values.push_back(v); }
      vector_index = 0;
    }

    void print() noexcept {}
    bool pDriver(typename port<TIME, MSG>::CONTENT &v) const noexcept {
      if (vector_index >= values.size()) {
        v = -1;
      } else {
        v = values[vector_index];
        vector_index++;
      }
    }
};
