#ifndef EMBEDDED_MESSAGE__HPP
#define EMBEDDED_MESSAGE__HPP

#include <iostream>
#include <string>
#include <memory>

#include <ecdboost/simulation/model.hpp>

using namespace std;
using namespace ecdboost;

using tofromPort = string;

template<class TIME, class VALUE>
struct EmbeddedMessage {

  using inner_type = VALUE;

  TIME tm;
  std::shared_ptr<model<TIME>> to;
  tofromPort port;
  VALUE val;

  EmbeddedMessage() :
    tm(TIME::Zero),
    to(nullptr),
    port(""),
    val(0) {  }

  EmbeddedMessage(const std::shared_ptr<model<TIME>>& other_model, const tofromPort& other_port, const VALUE& other_val) :
    tm(TIME::currentTime()),
    to(other_model),
    port(other_port),
    val(other_val) {  }

  EmbeddedMessage(const tofromPort& other_port, const VALUE& other_val) :
    tm(TIME::currentTime()), 
    to(nullptr),
    port(other_port),
    val(other_val) {  }

  EmbeddedMessage(const tofromPort& other_port) :
    tm(TIME::currentTime()),
    to(nullptr),
    port(other_port),
    val(0) {  }

  EmbeddedMessage(const EmbeddedMessage<TIME, VALUE>& other) :
    tm(other.tm),
    to(other.to),
    port(other.port),
    val(other.val) {  }

  EmbeddedMessage(EmbeddedMessage<TIME, VALUE>* other) :
    tm(other->tm),
    to(other->to),
    port(other->port),
    val(other->val) {  }

  void clear() {
    tm   =  TIME::Zero;
    to   =  nullptr;
    port =  "";
    val  =  0;
  }

  bool isEmpty() {
    return (tm == TIME::Zero) && (to==nullptr) && (port.compare("")==0) && (val == 0);
  }

  void print() { }
};

template<class TIME, class VALUE>
ostream& operator<<(ostream& os, const EmbeddedMessage<TIME, VALUE>& msg) {
  os << "Message("
    << "time: "       << msg.tm.asString() 
    << ", to-model: " << "TODO"             // add model name later here 
    << ", port: "     << msg.port 
    << ", value: "    << msg.val
  << ")";

  return os;
}


#endif // EMBEDDED_MESSAGE__HPP

