#include <ecdboost/simulation.hpp>
#include <ecdboost/utilities/embedded_time.hpp>
#include <ecdboost/utilities/embedded_message.hpp>
#include <ecdboost/builtins/linux_timer.hpp>

#include "atomic_models/adder.hpp"
#include "ports/file_reader.hpp"
#include "ports/file_writer.hpp"

using namespace std;
using namespace ecdboost::simulation;
using namespace ecdboost::simulation::pdevs;
using namespace ecdboost::simulation::pdevs::basic_models;

using Time = EmbeddedTime<LinuxTimer>;
using Message = EmbeddedMessage<Time>;

int main(){
    auto atomic_adder = make_atomic_ptr<Adder<Time, Message>>();

    shared_ptr<flattened_coupled<Time, Message>> top_component( new flattened_coupled<Time, Message>{{atomic_adder}, {atomic_adder}, {}, {atomic_adder}});

    auto file_reader_port = make_port_ptr< FileReader<Time, Message>, const string &, const Time & >("reader_port", Time(0,0,1,0));
    auto file_writer_port = make_port_ptr< FileWriter<Time, Message>, const string &>("writer_port");

    erunner<Time, Message> root{
        top_component,
        { {file_reader_port, atomic_adder} },
        { {file_writer_port, atomic_adder} }
    };

    root.runUntil(Time(0,0,10,0));

    return 0;
}
