#include "my_server.hpp"

MyServer::MyServer(std::string loctions_file,int port) : Server(loctions_file,port) {}

void MyServer::initialize(){
    this->get(_404_IMAGE,new ShowImage(_404_IMAGE_LOC));
    this->setNotFoundErrPage(_404_PAGE_LOC);
    this->get(SUBMIT_PAGE, new ShowPage(SUBMIT_PAGE_LOC));
    this->post(SUBMIT_PAGE,new SubmitHandler(this));
    this->get(CSS_FILE,new ShowFile(CSS_FILE_LOC,"text/css"));
    this->get(TAXI_REQ_PAGE,new TaxiReqLoader(this));
    this->post(TAXI_REQ_PAGE,new TaxiReqHandler(this));
    this->get("/"+BAD_REQ_ERR+".png",new ShowImage(BAD_REQ_IMAGE_LOC));
    this->get("/"+NOT_FOUND_ERR+".png",new ShowImage(NOT_FOUND_IMAGE_LOC));
    this->get("/"+EMPTY_ERR+".png",new ShowImage(EMPTY_IMAGE_LOC));
    this->get("/"+DENIED_ERR+".png",new ShowImage(DENIED_IMAGE_LOC));
    this->get("/"+BAD_REQ_ERR,new ShowPage(BAD_REQ_PAGE_LOC));
    this->get("/"+EMPTY_ERR,new ShowPage(EMPTY_PAGE_LOC));
    this->get("/"+NOT_FOUND_ERR,new ShowPage(NOT_FOUND_PAGE_LOC));
    this->get("/"+DENIED_ERR,new ShowPage(DENIED_PAGE_LOC));
    this->get("/home.png",new ShowImage(HOME_IMAGE_LOC));
    this->get(HOME_PAGE,new ShowPage(HOME_PAGE_LOC));
    this->get("/success.png",new ShowImage(SUCCESS_IMAGE_LOC));
    this->get(SUCCESS_PAGE,new ShowPage(SUCCESS_PAGE_LOC));
    this->get(TRIPS_PAGE,new TripsLoaderHandler(this));
    this->post(COST_PAGE,new TripCostHandler(this));
    this->get(GET_TRIPS_PAGE,new ShowPage(GET_TRIPS_PAGE_LOC));
    this->post(GET_TRIPS_PAGE,new GetTripsHandler());
    this->get(CANCEL_TRIP_PAGE,new ShowPage(CANCEL_TRIP_PAGE_LOC));
    this->post(CANCEL_TRIP_PAGE,new CancelTripHandler(this));
    this->get(ACCEPT_TRIP_PAGE,new AcceptTripHandler(this));
    this->get(FINISH_TRIP_PAGE,new FinishTripHandler(this));
    this->get(SUUCCESS_TRIP_PAGE,new TripSuccessHandler(NULL));
}
