#ifndef _DRIVER__HH_
#define _DRIVER__HH_

#include "User.hpp"

class Driver: public User {
  public: Driver(std::string _username);
  bool can_get_taxi();
  bool is_driver();
  void accept_travel();
  bool can_pick_passenger();
  bool can_end_travel();
  void end_travel();
  void get_a_taxi_req();
  void cancel_taxi_req();
  private: bool has_passenger;
};

#endif
