#ifndef ATOMIC_ADDER_HPP
#define ATOMIC_ADDER_HPP

#include <ecdboost/simulation.hpp>

using namespace ecdboost;
using namespace ecdboost::simulation;
using namespace ecdboost::simulation::pdevs;

template<class TIME, class MSG>
class Adder : public pdevs::atomic<TIME, MSG> {
  private:
    TIME next_internal;
    int my_value;

  public:
    explicit Adder() noexcept :
    atomic<TIME, MSG>("adder") {
      next_internal = pdevs::atomic<TIME, MSG>::infinity;
    }

    void internal() noexcept {
      next_internal = pdevs::atomic<TIME, MSG>::infinity;
    }

    TIME advance() const noexcept {
      return next_internal;
    }

    std::vector<MSG> out() const noexcept {
      MSG out_msg("writer_port", my_value);
      std::vector<MSG> out_vec{ out_msg };
      return out_vec;
    }

    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {
      my_value = mb.front().val;

      my_value++;

      next_internal = TIME::Zero;
    }

    void confluence(const std::vector<MSG>& mb, const TIME& t) noexcept {
      internal();
    }

    void print() noexcept {}

};

#endif  // ATOMIC_ADDER_HPP
