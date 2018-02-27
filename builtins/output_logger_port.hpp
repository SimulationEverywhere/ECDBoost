#include <fstream>
#include <string>

template<class TIME, class MSG>
class OutputLoggerPort : public port<TIME, MSG> {
  public:
    std::string file_name;

    explicit OutputLoggerPort (const std::string &name, const std::string &_file_name) noexcept :
      port<TIME, MSG>(name),
      file_name(_file_name) {
      out_file.open(file_name, std::fstream::trunc);
      out_file.close();
    }

    void print() noexcept {}
    bool pDriver(typename port<TIME, MSG>::MSG_VALUE &v) const noexcept {
      out_file.open(file_name, std::fstream::app);

      out_file
        << port<TIME, MSG>::portName << " received: "
        << v << " @ "
        << TIME::currentTime() << std::endl;

      out_file.close();
    }

  protected:
    mutable std::ofstream out_file;
};
