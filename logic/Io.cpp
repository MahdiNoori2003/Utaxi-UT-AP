#include "Io.hpp"

using namespace std;

Io::Io(string _input_file_name) {
  input_file_name = _input_file_name;
}

std::vector < Location > Io::read_file_info() {
  std::vector < Location > result;
  ifstream file;
  file.open(input_file_name, ios:: in );
  string b;
  getline(file, b);
  while (file.good()) {
    Location temp_loc;
    getline(file, temp_loc.name, ',');
    string temp;
    getline(file, temp, ',');
    temp_loc.latitude = stod(temp);
    getline(file, temp, ',');
    temp_loc.longtitude = stod(temp);
    getline(file, temp);
    temp_loc.traffic = stoi(temp);
    result.push_back(temp_loc);
  }
  file.close();
  return result;
}

void Io::string_validation(string input) {
  if (input.empty()) {
    throw (Bad_Req_Exception());
  }
  int space_count = 0;
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == ' ')
      space_count++;
  }

  if (space_count == input.length())
    throw (Bad_Req_Exception());
}