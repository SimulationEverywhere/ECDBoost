#ifndef EMBEDDED_MESSAGE__HPP
#define EMBEDDED_MESSAGE__HPP

#include <iostream>
#include <string>
#include <memory>

#include <ecdboost/simulation/model.hpp>

using namespace std;
using namespace ecdboost::simulation;

using Value      = int;
using tofromPort = string;

template<class Time>
struct EmbeddedMessage {

  Time tm;
  std::shared_ptr<model<Time>> to;
  tofromPort port;
  Value val;

  EmbeddedMessage()
  : tm(Time::Zero), to(nullptr), port(""), val(0){}

  EmbeddedMessage(const std::shared_ptr<model<Time>>& other_model, const tofromPort& other_port, const Value& other_val)
  :tm(Time::currentTime()), to(other_model), port(other_port), val(other_val){}

  //Default conStructor to use for testing
  EmbeddedMessage(const tofromPort& other_port, const Value& other_val)
  :tm(Time::currentTime()), to(nullptr), port(other_port), val(other_val){}

  EmbeddedMessage(const tofromPort& other_port)
  :tm(Time::currentTime()), to(nullptr), port(other_port), val(0){}

  EmbeddedMessage(const EmbeddedMessage<Time>& other)
  : tm(other.tm), to(other.to), port(other.port), val(other.val){}

  EmbeddedMessage(EmbeddedMessage<Time>* other)
  : tm(other->tm), to(other->to), port(other->port), val(other->val){}

  void clear() {
    tm     =  Time::Zero;
    to     =  nullptr;
    port   =  "";
    val    =  0;
  }

  bool isEmpty(){
    if((tm == Time::Zero) && (to==nullptr) && (port.compare("")==0) && (val == 0))
      return true;
    else
      return false;
  }

  void print(){
    //Testing - Debugging purposes
    //char buf[20];

    //SWO_PrintString((" Time: " + tm.asString() + "\n").c_str());
    //SWO_PrintString((" Port: " + port).c_str());
    //sprintf(buf," Value : %d \n", val); SWO_PrintString(buf);
  }
};

template<class Time>
ostream& operator<<(ostream& os, const EmbeddedMessage<Time>& msg) {
  os << "Message("
    << "time: "       << msg.tm.asString() 
    << ", to-model: " << "TODO"             // add model name later here 
    << ", port: "     << msg.port 
    << ", value: "    << msg.val
  << ")";

  return os;
}


#endif // EMBEDDED_MESSAGE__HPP
