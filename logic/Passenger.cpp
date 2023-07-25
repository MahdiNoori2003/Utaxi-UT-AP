#include "Passenger.hpp"

using namespace std;

Passenger::Passenger(string _username): User(_username) {
  role = passenger;
  is_on_board = false;
  has_taxi_req=false;
}

bool Passenger::can_get_taxi() {
  if(has_taxi_req||is_on_board){
    return false;
  }
  return true;
}

bool Passenger::is_driver() {
  return false;
}

void Passenger::accept_travel() {
  is_on_board = true;
}

bool Passenger::can_pick_passenger() {
  return false;
}

bool Passenger::can_end_travel() {
  return false;
}

void Passenger::end_travel() {
  is_on_board = false;
  has_taxi_req=false;
}

void Passenger::get_a_taxi_req(){
  has_taxi_req=true;
}

void Passenger::cancel_taxi_req(){
  has_taxi_req=false;
}