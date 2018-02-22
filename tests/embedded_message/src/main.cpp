#include <iostream>
#include <unistd.h>

#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/utilities/embedded_message.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

using Time = EmbeddedTime<LinuxTimer>;
using Message = EmbeddedMessage<Time>;

int main () {
    std::cout << "Basic embedded message testing ";
    std::cout <<  "(one second sleep between messages)\n" << std::endl;

    Message m1 = Message("to-'message not carrying the answer'-port", 41);
    sleep(1);
    Message m2 = Message("to-'message carrying the answer'-port", 42);
    sleep(1);
    Message m3 = Message("to-'message not carrying the answer'-port", 43);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;

    return 0;
}

