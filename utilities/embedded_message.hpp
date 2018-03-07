#ifndef EMBEDDED_MESSAGE__HPP
#define EMBEDDED_MESSAGE__HPP

#include <iostream>
#include <string>
#include <memory>

#include <ecdboost/simulation/model.hpp>

using namespace std;
using namespace ecdboost;

using tofromPort = string;

template<class TIME, class CONTENT_TYPE>
struct EmbeddedMessage {

  using inner_type = CONTENT_TYPE;

  TIME tm;
  std::shared_ptr<model<TIME>> to;
  tofromPort port;
  CONTENT_TYPE val;

  EmbeddedMessage() :
    tm(TIME::Zero),
    to(nullptr),
    port(""),
    val() {  }

  EmbeddedMessage(const std::shared_ptr<model<TIME>>& other_model, const tofromPort& other_port, const CONTENT_TYPE& other_val) :
    tm(TIME::currentTime()),
    to(other_model),
    port(other_port),
    val(other_val) {  }

  EmbeddedMessage(const tofromPort& other_port, const CONTENT_TYPE& other_val) :
    tm(TIME::currentTime()), 
    to(nullptr),
    port(other_port),
    val(other_val) {  }

  EmbeddedMessage(const tofromPort& other_port) :
    tm(TIME::currentTime()),
    to(nullptr),
    port(other_port),
    val(0) {  }

  EmbeddedMessage(const EmbeddedMessage<TIME, CONTENT_TYPE>& other) :
    tm(other.tm),
    to(other.to),
    port(other.port),
    val(other.val) {  }

  EmbeddedMessage(EmbeddedMessage<TIME, CONTENT_TYPE>* other) :
    tm(other->tm),
    to(other->to),
    port(other->port),
    val(other->val) {  }

  void clear() {
    tm   =  TIME::Zero;
    to   =  nullptr;
    port =  "";
    val  =  CONTENT_TYPE();
  }

  bool isEmpty() {
    return (tm == TIME::Zero) && (to==nullptr) && (port.compare("")==0) && (val == 0);
  }

  void print() { }
};

template<class TIME, class CONTENT_TYPE>
ostream& operator<<(ostream& os, const EmbeddedMessage<TIME, CONTENT_TYPE>& msg) {
  os << "Message("
    << "time: "       << msg.tm.asString() 
    << ", to-model: " << "TODO"             // add model name later here 
    << ", port: "     << msg.port 
    << ", value: "    << msg.val
  << ")";

  return os;
}


#endif // EMBEDDED_MESSAGE__HPP

