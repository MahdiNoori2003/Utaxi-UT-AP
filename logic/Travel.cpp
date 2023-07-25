#include "Travel.hpp"

using namespace std;

Travel::Travel(Location _dest, Location _origin, int _id, string _passenger_name, bool _is_in_hurry, double _cost) {
  dest = _dest;
  origin = _origin;
  id = _id;
  status = waiting;
  passenger_name = _passenger_name;
  cost = _cost;
  is_in_hurry = _is_in_hurry;
}

void Travel::change_travel_status(travel_status new_status) {
  this -> status = new_status;
}

stringstream Travel::get_info(string driver_username) {
  std::stringstream info;

  info << "<td>" << id << "</td>" <<
    "<td>" << passenger_name << "</td>" <<
    "<td>" << origin.name << "</td>" <<
    "<td>" << dest.name << "</td>" <<
    "<td>" << status_to_string(status) << "</td>" <<
    "<td>" << fixed << setprecision(2) << cost << "</td>";
  if (this -> can_be_accepted())
    info << "<td><a href='/AcceptTrip?id=" << id << "&username=" << driver_username << "'class='list_btn'style='text-decoration: none;'>accept</a></td>";
  if (this -> can_be_finished())
    info << "<td><a href='/FinishTrip?id=" << id << "&username=" << driver_username << "'class='list_btn'style='text-decoration: none;'>finish</a></td>";
  return info;
}

bool Travel::has_the_same_id_with(int id) {
  return this -> id == id;
}

bool Travel::can_be_cancelled() {
  if (this -> status == finished || this -> status == traveling) {
    return false;
  }

  return true;
}

bool Travel::own_travel(string user_name) {
  return this -> passenger_name == user_name;
}

void Travel::get_accepted(string _driver_name) {
  change_travel_status(traveling);
  this -> driver_name = _driver_name;
}

void Travel::get_ended() {
  change_travel_status(finished);
  this -> driver_name.clear();
}

bool Travel::can_be_accepted() {
  if (this -> status == finished || this -> status == traveling) {
    return false;
  }

  return true;
}

bool Travel::can_be_finished() {
  if (this -> status == finished || this -> status == waiting) {
    return false;
  }

  return true;
}

bool Travel::can_be_finished_by(string user_name) {
  if (driver_name != user_name) {
    return false;
  }
  return true;
}

string Travel::status_to_string(travel_status _status) {
  string result;
  switch (status) {
  case traveling:
    result = "traveling";
    break;
  case waiting:
    result = "waiting";
    break;
  case finished:
    result = "finished";
    break;

  default:
    break;
  }

  return result;
}