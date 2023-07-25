#include "User.hpp"

using namespace std;

User::User(std::string _username) {
  username = _username;
}

bool User::has_the_same_username_with(string user_name) {
  if (user_name == this -> username)
    return true;

  return false;
}