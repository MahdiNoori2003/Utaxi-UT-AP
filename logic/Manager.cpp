#include "Manager.hpp"

using namespace std;

Manager::Manager(string input_file_addr) {
  last_travel_id = 0;
  io = new Io(input_file_addr);
  locations = io -> read_file_info();
}

Role Manager::determine_user_role(string role) {
  if (role == DRIVER_TAG)
    return driver;

  return passenger;
}

void Manager::submit_user(string user_role, string user_name) {
  io -> string_validation(user_role);
  io -> string_validation(user_name);
  if (find_user(user_name))
    throw (Bad_Req_Exception());

  users.push_back(new_user(determine_user_role(user_role), user_name));

}

User * Manager::find_user(string user_name) {
  for (auto & user: users) {
    if (user -> has_the_same_username_with(user_name))
      return user;
  }

  return NULL;
}

User * Manager::new_user(Role user_role, std::string user_name) {
  if (user_role == driver) {
    return new Driver(user_name);
  } else {
    return new Passenger(user_name);
  }
}

bool Manager::determine_in_hurry_status(std::string in_hurry_statement) {

  if (in_hurry_statement == "yes") {
    return true;
  } else if (in_hurry_statement == "no") {
    return false;
  } else {
    throw (Bad_Req_Exception());
  }
}

int Manager::request_for_taxi(string user_name, string origin, string dest, string is_in_hurry) {
  io -> string_validation(user_name);
  io -> string_validation(origin);
  io -> string_validation(dest);
  io -> string_validation(is_in_hurry);
  if (origin == dest) {
    throw (Bad_Req_Exception());
  }

  Location dest_loc = find_location(dest);
  Location origin_loc = find_location(origin);

  if (!find_user(user_name)) {
    throw (Not_Found_Exception());
  }
  if (find_user(user_name) -> is_driver()) {
    throw (Denied_Exception());
  }
  if (!find_user(user_name) -> can_get_taxi()) {
    throw (Bad_Req_Exception());
  }

  last_travel_id++;
  travels.push_back(new Travel(dest_loc, origin_loc, last_travel_id,
    user_name, determine_in_hurry_status(is_in_hurry), this -> calculate_cost(origin_loc, dest_loc, determine_in_hurry_status(is_in_hurry))));
  find_user(user_name) -> get_a_taxi_req();
  return last_travel_id;
}

Location Manager::find_location(string name) {
  for (auto loc: locations) {
    if (loc.name == name)
      return loc;
  }

  throw (Not_Found_Exception());

}

vector < string > Manager::get_travels_list(string user_name, bool be_sorted) {
  vector < string > result;
  vector < Travel * > temp_travels = travels;
  io -> string_validation(user_name);
  if (!find_user(user_name)) {
    throw (Not_Found_Exception());
  }

  if (!find_user(user_name) -> is_driver()) {
    throw (Denied_Exception());
  }

  if (be_sorted) {
    sort(temp_travels.begin(), temp_travels.end(), sort_travels_by_price_parameter);
  }

  for (auto travel: temp_travels) {
    result.push_back(travel -> get_info(user_name).str());
  }

  if (travels.empty()) {
    throw (Empty_Exception());
  }

  return result;
}

int Manager::find_travel_index(int id) {
  int i;
  for (i = 0; i < travels.size(); i++) {
    if (travels[i] -> has_the_same_id_with(id)) {

      return i;
    }
  }

}

void Manager::cancel_travel(string user_name, string _id) {
  io -> string_validation(user_name);
  io -> string_validation(_id);
  int id = stoi(_id);
  if (!find_travel(id) || !find_user(user_name)) {
    throw (Not_Found_Exception());
  }

  if (find_user(user_name) -> is_driver()) {
    throw (Denied_Exception());
  }

  if (!find_travel(id) -> own_travel(user_name)) {
    throw (Denied_Exception());
  }

  if (!find_travel(id) -> can_be_cancelled()) {
    throw (Bad_Req_Exception());
  }

  int travel_index = find_travel_index(id);
  delete find_travel(id);
  find_user(user_name) -> cancel_taxi_req();
  travels.erase(travels.begin() + travel_index);

}

void Manager::accept_travel(string user_name, string _id) {
  io -> string_validation(user_name);
  io -> string_validation(_id);
  int id = stoi(_id);
  if (!find_user(user_name) -> can_pick_passenger()) {
    throw (Bad_Req_Exception());
  }

  find_user(user_name) -> accept_travel();
  find_travel(id) -> get_accepted(user_name);
  find_user(find_travel(id) -> get_passenger_name()) -> accept_travel();
}

void Manager::end_travel(string user_name, string _id) {
  io -> string_validation(user_name);
  io -> string_validation(_id);
  int id = stoi(_id);
  if (!find_user(user_name) -> can_end_travel()) {
    throw (Bad_Req_Exception());
  }
  if (!find_travel(id) -> can_be_finished_by(user_name)) {
    throw (Denied_Exception());
  }

  find_user(user_name) -> end_travel();
  find_travel(id) -> get_ended();
  find_user(find_travel(id) -> get_passenger_name()) -> end_travel();
}

Travel * Manager::find_travel(int id) {
  for (int i = 0; i < travels.size(); i++) {
    if (travels[i] -> has_the_same_id_with(id)) {
      return travels[i];
    }
  }

  return NULL;
}

void Manager::kill() {
  delete io;
  for (int i = 0; i < users.size(); i++) {
    delete users[i];
  }
  for (int j = 0; j < travels.size(); j++) {
    delete travels[j];
  }
}

double Manager::calculate_cost(Location origin, Location dest, bool is_in_hurry) {
  double latitude_dist = dest.latitude - origin.latitude;
  double longtitude_dist = dest.longtitude - origin.longtitude;
  double dist = DISTANCE_CONSTANT * (sqrt(pow(latitude_dist, 2) + pow(longtitude_dist, 2)));

  if (is_in_hurry) {
    return HURRY_CONSTANT * dist * PRICE_CONSTANT * (dest.traffic + origin.traffic);
  }

  return dist * PRICE_CONSTANT * (dest.traffic + origin.traffic);
}

string Manager::show_travel_price(string user_name, string origin, string dest, bool is_in_hurry) {
  io -> string_validation(user_name);
  io -> string_validation(origin);
  io -> string_validation(dest);
  if (!find_user(user_name)) {
    throw (Not_Found_Exception());
  }
  if (find_user(user_name) -> is_driver()) {
    throw (Denied_Exception());
  }
  if (origin == dest) {
    throw (Bad_Req_Exception());
  }

  double cost = calculate_cost(find_location(origin), find_location(dest), is_in_hurry);
  stringstream temp_cost;
  temp_cost << fixed << setprecision(2) << cost;

  return temp_cost.str();
}

bool Manager::sort_travels_by_price_parameter(Travel * t1, Travel * t2) {
  return t1 -> get_cost() > t2 -> get_cost();
}