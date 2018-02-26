// ECDBoost files
#include <ecdboost/simulation.hpp>
#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/utilities/embedded_message.hpp>
#include <ecdboost/builtins/linux_timer.hpp>
#include <ecdboost/builtins/output_logger_port.hpp>

// Own files
#include "atomic_models/adder.hpp"
#include "ports/file_reader.hpp"

using namespace std;
using namespace ecdboost;

using Time = EmbeddedTime<LinuxTimer>;
using Message = EmbeddedMessage<Time>;

int main(){

#ifdef ENABLE_SIMULATION
    auto atomic_adder = make_atomic_ptr<Adder<Time, Message>>();

    shared_ptr<flattened_coupled<Time, Message>> top_component( new flattened_coupled<Time, Message>{{atomic_adder}, {atomic_adder}, {}, {atomic_adder}});

    auto file_reader_port = make_port_ptr< FileReader<Time, Message>, const string &, const Time & >("reader_port", Time(0,0,0,200));
    auto file_writer_port = make_port_ptr< OutputLoggerPort<Time, Message>, const string &, const string & >("writer_port", "output.txt");

    erunner<Time, Message> root{
        top_component,
        { {file_reader_port, atomic_adder} },
        { {file_writer_port, atomic_adder} }
    };

    root.runUntil(Time(0,0,3,0));
#endif

    return 0;
}
