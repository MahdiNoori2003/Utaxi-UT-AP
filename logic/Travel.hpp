#ifndef _TRAVEL__HH_
#define _TRAVEL__HH_

#include <iostream>

#include <math.h>

#include <sstream>

#include <iomanip>

const std::string SPACE = " ";
const double DISTANCE_CONSTANT = 110.5;
const int PRICE_CONSTANT = 10000;
const double HURRY_CONSTANT = 1.2;

typedef struct {
  double latitude;
  double longtitude;
  std::string name;
  int traffic;
}
Location;

enum travel_status {
  finished,
  waiting,
  traveling
};

class Travel {
  public:
    Travel(Location _dest, Location _origin, int _id, std::string _passenger_name, bool _is_in_hurry, double _cost);
  void change_travel_status(travel_status new_status);
  std::stringstream get_info(std::string driver_username);
  bool has_the_same_id_with(int id);
  bool can_be_cancelled();
  bool can_be_accepted();
  bool can_be_finished();
  bool can_be_finished_by(std::string user_name);
  bool own_travel(std::string user_name);
  void get_accepted(std::string _driver_name);
  void get_ended();
  std::string status_to_string(travel_status _status);
  std::string get_passenger_name() {
    return passenger_name;
  }
  double get_cost() {
    return cost;
  }

  private:
    Location dest;
  Location origin;
  travel_status status;
  std::string passenger_name;
  std::string driver_name;
  int id;
  double cost;
  bool is_in_hurry;

};

#endif