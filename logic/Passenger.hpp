#ifndef _PASS__HH_
#define _PASS__HH_

#include "User.hpp"

class Passenger: public User {
  public: Passenger(std::string _username);
  bool can_get_taxi();
  bool is_driver();
  void accept_travel();
  bool can_pick_passenger();
  bool can_end_travel();
  void end_travel();
  void get_a_taxi_req();
  void cancel_taxi_req();
  private: bool is_on_board;
  bool has_taxi_req;
};

#endif
