# ECDBoost, towards an embedded systems kernel based on PDEVS.

ECDBoost aims to provide a simulation & modelling approach to develop embedded systemes
controllers.
This methods allows to test algorithms via simulation.
Once satisfied with the results, the controllers can be directly embedded by only adding an
interface which would allow the model to communicate with the hardware via its specific drivers.
Note that is allows to develop hardware-agnostic controllers but which are easily testable.

More details can be found in
[A kernel for embedded systems development](docs/a_kernel_for_embedded_systems_development.pdf)
and
[Developing a quadcopter controller using demes](docs/developing_a_quadcopter_controller_using_demes.pdf)

## Dependencies

ECDBoost has [Boost C++ Library](http://www.boost.org/) as a dependency (version 1.57.0 has been
being used but you are welcome to test other verions aswell).  
After installation you need to let your compiler know where this library is placed.

## Installation

It is recommended to install ECDBoost as a
[git submodules](https://gist.github.com/gitaarik/8735255).
By doing this it will be easier to maitain your project and get updates.

## Compilation

To use ECDBoost just include the folder where you cloned the project when compiling.
The core components of this library are header-only files, so you don't need to worry about extra
object files.

For instance the `g++`'s flag `-I<path>` will suffice, `<path>` being the path to where this
project was cloned.

Some extra builtins components are however divided into source and header files.

## Usage

### Template instantiantion

ECDBoost works with C++ templates and needs to be instantiated.  
The user needs to provide a **Timer** object, a **Time** object (which uses the **Timer**) and a
**Message** object (which uses the **Time**).
Working versions for the last two can be found at `utilities/embedded_message.hpp` and
`utilities/embedded_time.hpp`

Since the rest of ECDBoost objects use a **Time** object and a **Message** object, it's recommended
to use
C++ `using` keyword as in the following example:
```
using Time = EmbeddedTime<LinuxTimer>;
using Message = EmbeddedMessage<Time, int>;
```

#### Timer object

In the other hand the **Timer** is dependant on the hardware for which the controllers are being
developed.
Hence for each application a different object might be needed.
Because of this, the user needs to provide an object implementing the following functions:

```
static void initialize();
static int micro_seconds_since_started();
```
This object will be used keep track of the time when running the PDEVS model.

A working timer is provided as an example in `buitlins/linux_timer.hpp`.

### Model creation

Refer to 
[A kernel for embedded systems development](docs/a_kernel_for_embedded_systems_development.pdf)
for explanations about the model creation

## Example

In `tests/integration/` you can found a fairly enough complete example to get started.
Note that this example can be run in a desktop computer since the its **Timer** object is prepared
for that.

If that's not enough you can look at the following uses of ECDBoost:
 - [PDEVS wheels robot](https://github.com/SimulationEverywhere/PDEVS-wheels-robot)
 - [PDEVS crazyflie firmware](https://github.com/SimulationEverywhere/PDEVS-crazyflie-firmware)

