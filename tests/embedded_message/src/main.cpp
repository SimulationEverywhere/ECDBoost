#include <iostream>
#include <unistd.h>
#include <string>

#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/utilities/embedded_message.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

using Time = EmbeddedTime<LinuxTimer>;
int main () {
    std::cout << "Basic embedded message testing ";
    std::cout <<  "(one second sleep between messages)\n" << std::endl;

    using IntMessage = EmbeddedMessage<Time, int>;
    std::cout << "Message with ints" << std::endl;

    IntMessage m1 = IntMessage("to-'message not carrying the answer'-port", 41);
    sleep(1);
    IntMessage m2 = IntMessage("to-'message carrying the answer'-port", 42);
    sleep(1);
    IntMessage m3 = IntMessage("to-'message not carrying the answer'-port", 43);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;
    std::cout << std::endl;

    using StringMessage = EmbeddedMessage<Time, std::string>;
    std::cout << "Message with strings" << std::endl;

    StringMessage _m1 = StringMessage("to-'message carrying the answer'-port", "Cuarenta y dos");
    sleep(1);
    StringMessage _m2 = StringMessage("to-'message carrying the answer too'-port", "Quarante-deux");
    sleep(1);
    StringMessage _m3 = StringMessage("to-'same thing :)'-port", "Forty two");

    std::cout << _m1 << std::endl;
    std::cout << _m2 << std::endl;
    std::cout << _m3 << std::endl;

    return 0;
}

