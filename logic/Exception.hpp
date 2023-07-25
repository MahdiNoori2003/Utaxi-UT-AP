#ifndef _EXCEPTION__HH_
#define _EXCEPTION__HH_

#include<iostream>

const std::string BAD_REQ_ERR = "BadRequest";
const std::string NOT_FOUND_ERR = "NotFound";
const std::string DENIED_ERR = "PermissionDenied";
const std::string EMPTY_ERR = "EMPTY";

class Exception {

  public:
    Exception(const std::string & _msg);
  void handle_exception();
  virtual std::string what() = 0;
  private:
    std::string msg;
};

class Empty_Exception: public Exception {

  public: Empty_Exception();
  std::string what();
  private:

};

class Bad_Req_Exception: public Exception {

  public: Bad_Req_Exception();
  std::string what();
  private:

};

class Not_Found_Exception: public Exception {

  public: Not_Found_Exception();
  std::string what();
  private:

};

class Denied_Exception: public Exception {

  public: Denied_Exception();
  std::string what();
  private:

};

#endif