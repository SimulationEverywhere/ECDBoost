#ifndef LINUX_TIMER__HPP
#define LINUX_TIMER__HPP


class LinuxTimer {
    public:
        static void initialize();
        static int micro_seconds_since_started();
        static int get_microseconds();

    private:
        static bool initialized;
        static int start;
};


#endif  // LINUX_TIMER_HPP 
