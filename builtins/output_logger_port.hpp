#include <fstream>
#include <string>

template<class TIME, class MSG>
class OutputLoggerPort : public port<TIME, MSG> {
  public:
    explicit OutputLoggerPort (const std::string &name, std::ostream &_o_stream) noexcept :
      port<TIME, MSG>(name),
      output_stream(_o_stream) { }

    void print() noexcept {}
    bool pDriver(typename port<TIME, MSG>::CONTENT &v) const noexcept {
      output_stream 
        << port<TIME, MSG>::portName
        << " received: " << v
        << " @ " << TIME::currentTime() << std::endl;
    }

  protected:
    std::ostream & output_stream;
};
