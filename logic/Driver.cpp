#include "Driver.hpp"

using namespace std;

Driver::Driver(string _username): User(_username) {
  role = driver;
  has_passenger = false;
}

bool Driver::can_get_taxi() {
  return false;
}

bool Driver::is_driver() {
  return true;
}

void Driver::accept_travel() {
  has_passenger = true;
}

bool Driver::can_pick_passenger() {
  return !has_passenger;
}

bool Driver::can_end_travel() {
  return has_passenger;
}

void Driver::end_travel() {
  has_passenger = false;
}

void Driver::get_a_taxi_req(){}

void Driver::cancel_taxi_req(){}