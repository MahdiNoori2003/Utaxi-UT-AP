#include "./examples/handlers.hpp"
#include "./logic/Exception.hpp"
#include "./examples/my_server.hpp"
#include <iostream>

const int PORT=5000;

using namespace std;

int main(int argc, char **argv) {
  try {
    MyServer server(argv[1],PORT);
    server.initialize();
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
