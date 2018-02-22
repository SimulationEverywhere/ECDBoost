#include <iostream>
#include <fstream>


using Value = int;

template<class TIME, class MSG>
class FileWriter: public port<TIME, MSG> {
  public:
    mutable std::ofstream outfile;

    explicit FileWriter(const std::string &name) noexcept : port<TIME, MSG>(name) {
      outfile.open("output.txt", std::fstream::trunc);
      outfile.close();
    }

    void print() noexcept {}
    bool pDriver(Value &v) const noexcept {
      outfile.open("output.txt", std::fstream::app);
      outfile << v << " @ " << TIME::currentTime() << std::endl;
      outfile.close();
    }
};
