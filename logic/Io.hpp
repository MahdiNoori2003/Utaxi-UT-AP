#ifndef _IO__HH_
#define _IO__HH_

#include <iostream>

#include <vector>

#include <fstream>

#include "Travel.hpp"

#include "Exception.hpp"

class Io {
  public:
    Io(std::string _input_file_name);
  std::vector < Location > read_file_info();
  void string_validation(std::string);

  private:
    std::string input_file_name;
};

#endif