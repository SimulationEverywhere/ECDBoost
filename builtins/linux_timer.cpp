#include <ratio>
#include <ecdboost/builtins/linux_timer.hpp>

bool LinuxTimer::initialized = false;

std::chrono::time_point<std::chrono::high_resolution_clock> LinuxTimer::start = std::chrono::high_resolution_clock::now();

void LinuxTimer::initialize() {
    initialized = true;
    start = std::chrono::high_resolution_clock::now();
}

int LinuxTimer::micro_seconds_since_started() {
    if (!initialized) { initialize(); }

    auto current = std::chrono::high_resolution_clock::now();

    std::chrono::duration<long long, std::nano> difference = (current - start);

    return (int)(difference.count() / 1000);
}

