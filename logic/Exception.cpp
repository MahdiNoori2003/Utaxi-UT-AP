#include "Exception.hpp"

using namespace std;

Exception::Exception(const std::string & _msg) {
  msg = _msg;
}

void Exception::handle_exception() {
  cerr << msg << endl;
}

Empty_Exception::Empty_Exception(): Exception(EMPTY_ERR) {}

Bad_Req_Exception::Bad_Req_Exception(): Exception(BAD_REQ_ERR) {}

Not_Found_Exception::Not_Found_Exception(): Exception(NOT_FOUND_ERR) {}

Denied_Exception::Denied_Exception(): Exception(DENIED_ERR) {}

string Empty_Exception::what() {
  return EMPTY_ERR;
}
string Bad_Req_Exception::what() {
  return BAD_REQ_ERR;
}
string Not_Found_Exception::what() {
  return NOT_FOUND_ERR;
}
string Denied_Exception::what() {
  return DENIED_ERR;
}