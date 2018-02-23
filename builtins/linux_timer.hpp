#ifndef LINUX_TIMER__HPP
#define LINUX_TIMER__HPP

#include <chrono>

class LinuxTimer {
    public:
        static void initialize();
        static int micro_seconds_since_started();

    private:
        static bool initialized;
        static std::chrono::time_point<std::chrono::high_resolution_clock> start;
};


#endif  // LINUX_TIMER_HPP 
