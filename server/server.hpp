#ifndef __SERVER__
#define __SERVER__
#include "../utils/include.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include "../utils/template_parser.hpp"
#include "../logic/Manager.hpp"
#include "route.hpp"
#include <exception>
#include <string>
#include <vector>

class TemplateParser;
class Server;

class RequestHandler {
public:
  RequestHandler(Server* _server=NULL);
  virtual ~RequestHandler();
  virtual Response *callback(Request *req) = 0;
  protected:
  Server* server;
};

class ShowFile : public RequestHandler {
  std::string filePath;
  std::string fileType;

public:
  ShowFile(std::string filePath, std::string fileType);
  Response *callback(Request *req);
};

class ShowPage : public ShowFile {

public:
  ShowPage(std::string _filePath);
};

class ShowImage : public ShowFile {

public:
  ShowImage(std::string _filePath);
};

class TemplateHandler : public RequestHandler {
  std::string filePath;
  TemplateParser *parser;

public:
  TemplateHandler(std::string _filePath);
  Response *callback(Request *req);
  virtual std::map<std::string, std::string> handle(Request *req);
};

class Server {
public:
  Server(std::string _locations_path,int port = 5000);
  ~Server();
  void run();
  void get(std::string path, RequestHandler *handler);
  void post(std::string path, RequestHandler *handler);
  void setNotFoundErrPage(std::string);
  Manager * activate_api();
  Response* handle_errors(Exception& e);

  class Exception : public std::exception {
  public:
    Exception() {}
    Exception(const std::string);
    std::string getMessage();

  private:
    std::string message;
  };


private:
  int sc;
  int port;
  Manager* app_manager;
  std::vector<Route *> routes;
  RequestHandler *notFoundHandler;
};
#endif
