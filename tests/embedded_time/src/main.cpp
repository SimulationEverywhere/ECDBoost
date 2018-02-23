#include <iostream>
#include <unistd.h>

#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

using Time = EmbeddedTime<LinuxTimer>;

int main () {
    Time::initializeTimer();

    Time t1 = Time::currentTime();
    sleep(1);
    Time t2 = Time::currentTime();
    sleep(1);
    Time t3 = Time::currentTime();

    std::cout << "Current time and difference with the previous" << std::endl;

    std::cout << t1 << std::endl;
    std::cout << t2 << ": " << (t2 - t1) << std::endl;
    std::cout << t3 << ": " << (t3 - t2) << std::endl;

    return 0;
}

