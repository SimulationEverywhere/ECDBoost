#include <iostream>
#include <unistd.h>

#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

using Time = EmbeddedTime<LinuxTimer>;

int main () {
    std::cout << "Basic EmbeddedTime testing" << std::endl;
    std::cout << std::endl;

    std::cout << "Testing constructors..." << std::endl;
    Time _t1;
    Time _t2(1, 23, 30, 300);    
    Time _t2bis(0, 23, 30, 300);    
    Time _t3(1, 23, 30, 300, 500);     
    Time _t4("01:23:30:300");    
    Time _t5(_t3);
    std::cout << std::endl;

    std::cout << "Testing operators..." << std::endl;
    std::cout << (_t2 - _t2bis) << std::endl;
    std::cout << (_t2 + _t2bis) << std::endl;
    _t1 = _t4;
    std::cout << _t1 << std::endl;
    std::cout << (_t4 == _t2) << std::endl;
    std::cout << (_t4 != _t2) << std::endl;
    std::cout << (_t2 < _t2bis) << std::endl;
    std::cout << std::endl;

    std::cout << "Testing realtime..." << std::endl;
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

