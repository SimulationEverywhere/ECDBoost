#include <iostream>
#include <unistd.h>

#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

using Time = EmbeddedTime<LinuxTimer>;

int main () {
    int tt1 = LinuxTimer::get_microseconds();
    sleep(1);
    int tt2 = LinuxTimer::get_microseconds();
    sleep(1);
    int tt3 = LinuxTimer::get_microseconds();

    Time::initializeTimer();

    Time t1 = Time::currentTime();
    sleep(1);
    Time t2 = Time::currentTime();
    sleep(1);
    Time t3 = Time::currentTime();

    std::cout << "Current time and difference with the previous" << std::endl;

    std::cout << "Results directly getting the microseconds" << std::endl;
    std::cout << tt1 << std::endl;
    std::cout << tt2 << ": " << (tt2 - tt1) << std::endl;
    std::cout << tt3 << ": " << (tt3 - tt2) << std::endl;

    std::cout << "Results using the Time abstraction" << std::endl;
    std::cout << t1 << std::endl;
    std::cout << t2 << ": " << (t2 - t1) << std::endl;
    std::cout << t3 << ": " << (t3 - t2) << std::endl;

    return 0;
}

