#ifndef __MY_SERVER__
#define __MY_SERVER__

#include "../server/server.hpp"
#include "../examples/handlers.hpp"
#include <iostream>

const std::string _404_IMAGE= "/404.png";
const std::string _404_IMAGE_LOC= "static/PNGs/404.png";\
const std::string _404_PAGE_LOC="static/404.html";
const std::string SUBMIT_PAGE="/Submit";
const std::string SUBMIT_PAGE_LOC="static/Submit.html";
const std::string CSS_FILE="/style.css";
const std::string CSS_FILE_LOC="static/style.css";
const std::string TAXI_REQ_PAGE="/TaxiReq";
const std::string BAD_REQ_IMAGE_LOC="static/PNGs/BadRequest.png";
const std::string NOT_FOUND_IMAGE_LOC="static/PNGs/NotFound.png";
const std::string EMPTY_IMAGE_LOC="static/PNGs/EMPTY.png";
const std::string DENIED_IMAGE_LOC="static/PNGs/PermissionDenied.png";
const std::string BAD_REQ_PAGE_LOC="static/BadRequest.html";
const std::string EMPTY_PAGE_LOC="static/EMPTY.html";
const std::string NOT_FOUND_PAGE_LOC="static/NotFound.html";
const std::string DENIED_PAGE_LOC="static/PermissionDenied.html";
const std::string HOME_IMAGE_LOC="static/PNGs/home.png";
const std::string HOME_PAGE_LOC="static/Home.html";
const std::string SUCCESS_IMAGE_LOC="static/PNGs/success.png";
const std::string SUCCESS_PAGE_LOC="static/Success.html";
const std::string HOME_PAGE="/";
const std::string SUCCESS_PAGE="/Success";
const std::string TRIPS_PAGE="/TripsList";
const std::string COST_PAGE="/ShowCost";
const std::string GET_TRIPS_PAGE="/GetTripsList";
const std::string GET_TRIPS_PAGE_LOC="static/GetTripsList.html";
const std::string CANCEL_TRIP_PAGE="/CancelTrip";
const std::string CANCEL_TRIP_PAGE_LOC="static/CancelTrip.html";
const std::string ACCEPT_TRIP_PAGE="/AcceptTrip";
const std::string FINISH_TRIP_PAGE="/FinishTrip";
const std::string SUUCCESS_TRIP_PAGE="/SuccessTrip";

class MyServer : public Server {
public:
  MyServer(std::string loctions_file,int port = 5000);
  void initialize();
};

#endif
