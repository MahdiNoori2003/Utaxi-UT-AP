#ifndef _MANAGER__HH_
#define _MANAGER__HH_

#include <iostream>

#include <algorithm>

#include<vector>

#include <sstream>

#include "Io.hpp"

#include "Travel.hpp"

#include "Passenger.hpp"

#include "Driver.hpp"

#include "Exception.hpp"

const std::string SUCCESS_MESSAGE = "Ok";
const std::string DRIVER_TAG = "driver";
const std::string PASSENGER_TAG = "passenger";

class Manager {
  public:
    Manager(std::string input_file_addr);
  void submit_user(std::string user_role, std::string user_name);
  Role determine_user_role(std::string role);
  User * new_user(Role user_role, std::string user_name);
  User * find_user(std::string user_name);
  int request_for_taxi(std::string user_name, std::string origin, std::string dest, std::string is_in_hurry);
  Location find_location(std::string name);
  Travel * find_travel(int id);
  std::vector < std::string > get_travels_list(std::string user_name, bool be_sorted);
  std::string get_travel_info(std::string user_name, int id);
  void show_travel_info(std::string info);
  void cancel_travel(std::string user_name, std::string id);
  int find_travel_index(int id);
  void accept_travel(std::string user_name, std::string id);
  void end_travel(std::string user_name, std::string id);
  void kill();
  double calculate_cost(Location origin, Location dest, bool is_in_hurry);
  std::string show_travel_price(std::string user_name, std::string origin, std::string dest, bool is_in_hurry);
  static bool sort_travels_by_price_parameter(Travel * t1, Travel * t2);
  std::vector < Location > get_locs() {
    return locations;
  }
  bool determine_in_hurry_status(std::string in_hurry_statement);

  private:
    int last_travel_id;
  Io * io;
  std::vector < User * > users;
  std::vector < Travel * > travels;
  std::vector < Location > locations;
};

#endif