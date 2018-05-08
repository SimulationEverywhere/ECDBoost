# ECDBoost, towards an embedded systems kernel based on PDEVS.

ECDBoost aims to provide a simulation & modelling approach to develop embedded systems
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

## Installation

It is recommended to install ECDBoost as a
[git submodules](https://gist.github.com/gitaarik/8735255).
By doing this it will be easier to maintain your project and get updates.

## Compilation

To use ECDBoost just include the folder where you cloned the project when compiling.
The core components of this library are header-only files, so you don't need to worry about extra
object files.

For instance, the `g++`'s flag `-I<path>` will suffice (`<path>` being the path to where this
project was cloned).

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
Most probably for your specific case the algorithm will be the same one that can be found on that 
**Timer** object, only changing the used library.

### Model creation

*Note: A lot of improvement can be made in this section.
If you make changes please update this small documentation.*

Refer to 
[A kernel for embedded systems development](docs/a_kernel_for_embedded_systems_development.pdf)
for a detailed explanation about the model creation.

#### Atomic models

Your atomic models must be objects which inherit from `atomic` and implement its `void` methods:  
```cpp
template<class TIME, class MSG>
class MyAtomicModel : public ecdboost::atomic<TIME, MSG> {
  public:
    explicit MyAtomicModel(const std::string &name) noexcept : ecdboost::atomic<TIME, MSG>(name) { }

    void external(const std::vector<MSG>& mb, const TIME& t) noexcept { }
    void internal() noexcept { }
    std::vector<MSG> out() const noexcept { }
    TIME advance() const noexcept { }
    void confluence(const std::vector<MSG>& mb, const TIME& t)  noexcept  { }
    void print() noexcept { }
};
```

To instantiate them use:  
```cpp
auto my_atomic_model = make_atomic_ptr<MyAtomicModel<Time, Message>>();
```

#### Flattened coupled model

To create a flattened couple use the `flattened_coupled` constructor:  
```cpp
flattened_coupled(std::vector<std::shared_ptr<model<TIME>>> models,
            std::vector<std::shared_ptr<model<TIME>>> eic,
            std::vector<std::pair<std::shared_ptr<model<TIME>>, std::shared_ptr<model<TIME>>>> ic,
            std::vector<std::shared_ptr<model<TIME>>> eoc
)
```

And use the following to instantiate it:  
```cpp
shared_ptr<flattened_coupled<Time, Message>> MyFlattenedCoupled(
    new flattened_coupled<Time, Message>{
        { <models> },
        { <eic> },
        { <ic> },
        { <eoc> }
    } 
);
```

#### Ports

Your port objects will have to inherit from `port`:
```cpp
template<class TIME, class MSG>
class MyPort : public port<TIME, MSG> {
  public:
    explicit MyPort(const std::string &name, const TIME &polling) noexcept : port<TIME, MSG>(name, polling) { }
    void print() noexcept {}
    bool pDriver(typename port<TIME, MSG>::CONTENT &content) const noexcept { }
};
```

To instantiate it use:  
```cpp
auto my_port = make_port_ptr<MyPort<Time, Message>, std::string &, TIME&>(<name>, <polling_time>);
```

If you want to send extra parameters to your port objects you can do the following:
```cpp
explicit MyPort(
    ExtraParameterType &extra_parameter,
    const std::string &name,
    const TIME &polling) :
  port<TIME, MSG>(name, polling) {
  // Do something with the extra parameter
}
```

Then:  
```cpp
auto my_port = make_port_ptr<MyPort<Time, Message>, ExtraParameterType&, std::string &, TIME&>(<extra_parameter>, <name>, <polling_time>);
```

#### Starting the model

To start the model a final `root` object needs to be created:
```cpp
  erunner<Time, Message> root{
    MyFlattenedCoupled,  // Top model
    {  // Input ports
      { input_port_1, my_atomic_model_1 },
      { input_port_2, my_atomic_model_1 },
      { input_port_2, my_atomic_model_2 }
    },
    {  // Output ports
      { output_port_1, my_atomic_model_2 },
      { output_port_1, my_atomic_model_2 }
    }
  };
```

Finally, to run your model use:  
```cpp
  Time end_time{Time(0,30,0,0)};
  end_time = root.runUntil(end_time);
```
Note that in the final model for an embedded model you'll probably want to use `Time::Infinity()`.

## Example

In `tests/integration/` you can found a fairly enough complete example to get started.
Note that this example can be run in a desktop computer since the its **Timer** object is prepared
for that.

If that's not enough you can look at the following uses of ECDBoost:
 - [PDEVS wheels robot](https://github.com/SimulationEverywhere/PDEVS-wheels-robot)
 - [PDEVS crazyflie firmware](https://github.com/SimulationEverywhere/PDEVS-crazyflie-firmware)

