#ifndef _USER__HH_
#define _USER__HH_

#include <iostream>

enum Role {
  driver,
  passenger
};

class User {
  public:
    User(std::string _username);
  bool has_the_same_username_with(std::string user_name);
  virtual bool can_get_taxi() = 0;
  virtual bool is_driver() = 0;
  virtual void accept_travel() = 0;
  virtual bool can_pick_passenger() = 0;
  virtual bool can_end_travel() = 0;
  virtual void end_travel() = 0;
  virtual void get_a_taxi_req()=0;
  virtual void cancel_taxi_req()=0;

  protected:
    std::string username;
  Role role;

};

#endif