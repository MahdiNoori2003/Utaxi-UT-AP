#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"

#include "../logic/Exception.hpp"

#include "../logic/Travel.hpp"

#include <cstdlib> 

#include <ctime>   

#include <iostream>

#include <sstream>

class SubmitHandler: public RequestHandler {
  public: SubmitHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class TaxiReqLoader: public RequestHandler {
  public: TaxiReqLoader(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class TaxiReqHandler: public RequestHandler {
  public: TaxiReqHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class TripsLoaderHandler: public RequestHandler {
  public: TripsLoaderHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class TripCostHandler: public RequestHandler {
  public: TripCostHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class GetTripsHandler: public RequestHandler {
  public: GetTripsHandler(Server * _server = NULL): RequestHandler(_server) {}
  Response * callback(Request * );
};

class AcceptTripHandler: public RequestHandler {
  public: AcceptTripHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class FinishTripHandler: public RequestHandler {
  public: FinishTripHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class CancelTripHandler: public RequestHandler {
  public: CancelTripHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

class TripSuccessHandler: public RequestHandler {
  public: TripSuccessHandler(Server * _server): RequestHandler(_server) {}
  Response * callback(Request * );
};

#endif