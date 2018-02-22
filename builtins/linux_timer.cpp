#include <time.h>

#include <ecdboost/builtins/linux_timer.hpp>


bool LinuxTimer::initialized = false;
int LinuxTimer::start = 0;

int LinuxTimer::get_microseconds(){
    timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);

    int seconds = (int) ts.tv_sec;
    int nanoseconds = (int) ts.tv_nsec;

    return 1000000 * seconds + nanoseconds / 1000;

}

void LinuxTimer::initialize() {
    initialized = true;
    start = get_microseconds();
}

int LinuxTimer::micro_seconds_since_started() {
    if (!initialized) {
        initialize();
    }

    return (get_microseconds() - start);
}

