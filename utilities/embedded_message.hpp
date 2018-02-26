#ifndef EMBEDDED_MESSAGE__HPP
#define EMBEDDED_MESSAGE__HPP

#include <iostream>
#include <string>
#include <memory>

#include <ecdboost/simulation/model.hpp>

using namespace std;
using namespace ecdboost;

using Value      = int;
using tofromPort = string;

template<class TIME>
struct EmbeddedMessage {

  TIME tm;
  std::shared_ptr<model<TIME>> to;
  tofromPort port;
  Value val;

  EmbeddedMessage()
  : tm(TIME::Zero), to(nullptr), port(""), val(0){}

  EmbeddedMessage(const std::shared_ptr<model<TIME>>& other_model, const tofromPort& other_port, const Value& other_val)
  :tm(TIME::currentTime()), to(other_model), port(other_port), val(other_val){}

  //Default conStructor to use for testing
  EmbeddedMessage(const tofromPort& other_port, const Value& other_val)
  :tm(TIME::currentTime()), to(nullptr), port(other_port), val(other_val){}

  EmbeddedMessage(const tofromPort& other_port)
  :tm(TIME::currentTime()), to(nullptr), port(other_port), val(0){}

  EmbeddedMessage(const EmbeddedMessage<TIME>& other)
  : tm(other.tm), to(other.to), port(other.port), val(other.val){}

  EmbeddedMessage(EmbeddedMessage<TIME>* other)
  : tm(other->tm), to(other->to), port(other->port), val(other->val){}

  void clear() {
    tm     =  TIME::Zero;
    to     =  nullptr;
    port   =  "";
    val    =  0;
  }

  bool isEmpty(){
    if((tm == TIME::Zero) && (to==nullptr) && (port.compare("")==0) && (val == 0))
      return true;
    else
      return false;
  }

  void print(){
    //Testing - Debugging purposes
    //char buf[20];

    //SWO_PrintString((" TIME: " + tm.asString() + "\n").c_str());
    //SWO_PrintString((" Port: " + port).c_str());
    //sprintf(buf," Value : %d \n", val); SWO_PrintString(buf);
  }
};

template<class TIME>
ostream& operator<<(ostream& os, const EmbeddedMessage<TIME>& msg) {
  os << "Message("
    << "time: "       << msg.tm.asString() 
    << ", to-model: " << "TODO"             // add model name later here 
    << ", port: "     << msg.port 
    << ", value: "    << msg.val
  << ")";

  return os;
}


#endif // EMBEDDED_MESSAGE__HPP
