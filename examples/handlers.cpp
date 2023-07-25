#include "handlers.hpp"

using namespace std;

Response * SubmitHandler::callback(Request * req) {
  Response * res=new Response;
  try {
    server -> activate_api() -> submit_user(req -> getBodyParam("role"), req -> getBodyParam("username"));
  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }
  res = Response::redirect("/Success");
  return res;
}

Response * TaxiReqLoader::callback(Request * req) {
  string body;
  vector < Location > locations = server -> activate_api() -> get_locs();
  Response * res = new Response;
  res -> setHeader("Content-Type", "text/html");

  for (int i = 0; i < locations.size(); i++) {
    cout << locations[i].name << endl;
  }

  body = "<html lang='en'>";
  body += "<head>";
  body += "<meta charset='UTF-8'>";
  body += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  body += "<link rel='stylesheet' href='/style.css'>";
  body += "<title>Taxi_Request</title>";
  body += "</head>";
  body += "<body>";
  body += "<div class='nav-bar'>";
  body += "<ul class='nav-bar-list'>";
  body += "<li class='brand-tag'><span class='brand-tag-span'>U</span>Taxi</li>";
  body += "<li><a style='text-decoration: none;' href='/'>Home</a></li>";
  body += "<li><a style='text-decoration: none;'href='/CancelTrip'>Cancel Trip</a></li>";
  body += "<li><a style='text-decoration: none;'href='/GetTripsList'>Get Trips List</a></li>";
  body += "<li><a style='text-decoration: none;' href='/Submit' class='signup-tag'>Signup</a></li>";
  body += "</ul>";
  body += "</div>";
  body += "<div class='taxi_req_container'>";
  body += "<form action='/TaxiReq' method='post'>";
  body += "<label for='username'>UserName : </label>";
  body += "<br>";
  body += "<input type='text' name='username' id='username'>";
  body += "<br>";
  body += "<br>";
  body += "<label for='origin'>Origin : </label>";
  body += "<select name='origin' id='origin'>";
  for (int i = 0; i < locations.size(); i++) {
    stringstream temp;
    temp << "<option value='" << locations[i].name << "'>" << locations[i].name << "</option>" << "\n";
    body += temp.str();
  }

  body += "</select>";
  body += "<br><br>";
  body += "<label for='destination'>Destination : </label>";
  body += "<select name='destination' id='destination'>";
  for (int i = 0; i < locations.size(); i++) {
    stringstream temp;
    temp << "<option value='" << locations[i].name << "'>" << locations[i].name << "</option>" << "\n";
    body += temp.str();
  }
  body += "</select>";
  body += "<br><br>";
  body += "<label >In_Hurry :  </label>";
  body += "<label >yes </label>";
  body += "<input type='radio' name='In_Hurry_option' id='In_Hurry_option' value='yes'>";
  body += "<label >no </label>";
  body += "<input type='radio' name='In_Hurry_option' id='In_Hurry_option' value='no'>";
  body += "<br><br>";
  body += "<button type='submit'>Send</button>";
  body += "<button type='submit' formaction='/ShowCost'>Cost</button>";
  body += "</form>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res -> setBody(body);
  return res;
}

Response * TaxiReqHandler::callback(Request * req) {
  int trip_id;
  Response * res=new Response;

  try {
    trip_id = server -> activate_api() -> request_for_taxi(req -> getBodyParam("username"), req -> getBodyParam("origin"), req -> getBodyParam("destination"), req -> getBodyParam("In_Hurry_option"));

  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }
  res = Response::redirect("/SuccessTrip?id=" + to_string(trip_id));
  return res;
}

Response * TripsLoaderHandler::callback(Request * req) {
  Response * res = new Response;
  res -> setHeader("Content-Type", "text/html");
  string body;
  vector < string > trips_info;
  try {
    if (req -> getQueryParam("sort") == "on")
      trips_info = server -> activate_api() -> get_travels_list(req -> getQueryParam("username"), true);
    else
      trips_info = server -> activate_api() -> get_travels_list(req -> getQueryParam("username"), false);

  } catch (Exception & e) {
    string err_directory = "/" + e.what();
    Response * res = Response::redirect(err_directory);
    return res;
  }

  body += "<html lang='en'>";
  body += "<head>";
  body += "<meta charset='UTF-8'>";
  body += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  body += "<link rel='stylesheet' href='/style.css'>";
  body += "<title>Trips_List</title>";
  body += "</head>";
  body += "<body>";
  body += "<div class='nav-bar'>";
  body += "<ul class='nav-bar-list'>";
  body += "<li class='brand-tag'><span class='brand-tag-span'>U</span>Taxi</li>";
  body += "<li><a style='text-decoration: none;' href='/'>Home</a></li>";
  body += "</ul>";
  body += "</div>";
  body += "<div class='table_container'>";
  body += "<table class='table'>";
  body += "<tr class='t_header'>";
  body += "<th>ID</th>";
  body += "<th>Passenger</th>";
  body += "<th>Origin</th>";
  body += "<th>Destination</th>";
  body += "<th>Status</th>";
  body += "<th>Cost</th>";
  body += "</tr>";
  for (int i = 0; i < trips_info.size(); i++) {
    body += "<tr class='t_data'>";
    body += trips_info[i];
    body += "</tr>";
  }
  body += "</table>";
  body += "</div>";
  body += "<div class='wrapper'>";
  body += "<a class='sort-btn' href='/TripsList?sort=on&username=" + req -> getQueryParam("username") + "' style='text-decoration: none;'>Sort-By-Cost</a>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res -> setBody(body);
  return res;
}

Response * TripCostHandler::callback(Request * req) {

  Response * res = new Response;
  res -> setHeader("Content-Type", "text/html");
  string body;
  body += "<html lang='en'>";
  body += "<head>";
  body += "<meta charset='UTF-8'>";
  body += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  body += "<link rel='stylesheet' href='/style.css'>";
  body += "<title>Trip Cost</title>";
  body += "</head>";
  body += "<body>";
  body += "<div class='nav-bar'>";
  body += "<ul class='nav-bar-list'>";
  body += "<li class='brand-tag'><span class='brand-tag-span'>U</span>Taxi</li>";
  body += "<li><a style='text-decoration: none;' href='/'>Home</a></li>";
  body += "<li><a style='text-decoration: none;' href='/TaxiReq'>Get A Taxi</a></li>";
  body += "<li><a style='text-decoration: none;' href='/Submit' class='signup-tag'>Signup</a></li>";
  body += "</ul>";
  body += "</div>";
  body += "<div class='err_container'>";
  body += "<h1 class='price_header'>Your trip cost &#128181 will be :</h1>";
  body += "<h2 class='warn-q'>";
  try {
    body += server -> activate_api() -> show_travel_price(req -> getBodyParam("username"), req -> getBodyParam("origin"), req -> getBodyParam("destination"), server -> activate_api() -> determine_in_hurry_status(req -> getBodyParam("In_Hurry_option")));
  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }
  body += "</h2>";
  body += "<div class='span-wrapper'>";
  body += "<h2 class='warn-q'>From : <span>";
  body += req -> getBodyParam("origin");
  body += "</span></h2>";
  body += "<h2 class='warn-q'>To : <span>";
  body += req -> getBodyParam("destination");
  body += "</span></h2>";
  body += "</div>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res -> setBody(body);
  return res;
}

Response * GetTripsHandler::callback(Request * req) {

  Response * res = Response::redirect("/TripsList?username=" + req -> getBodyParam("username"));
  return res;
}

Response * CancelTripHandler::callback(Request * req) {
  Response * res = new Response;
  try {
    server -> activate_api() -> cancel_travel(req -> getBodyParam("username"), req -> getBodyParam("id"));
    res = Response::redirect("/Success");
  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }

  return res;
}

Response * AcceptTripHandler::callback(Request * req) {
  Response * res = new Response;
  try {
    server -> activate_api() -> accept_travel(req -> getQueryParam("username"), req -> getQueryParam("id"));
    res = Response::redirect("/TripsList?username=" + req -> getQueryParam("username"));
  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }
  return res;
}

Response * FinishTripHandler::callback(Request * req) {
  Response * res = new Response;
  try {
    server -> activate_api() -> end_travel(req -> getQueryParam("username"), req -> getQueryParam("id"));
    res = Response::redirect("/TripsList?username=" + req -> getQueryParam("username"));
  } catch (Exception & e) {
    return res=server->handle_errors(e);
  }
  return res;
}

Response * TripSuccessHandler::callback(Request * req) {
  Response * res = new Response;
  res -> setHeader("Content-Type", "text/html");
  string body;
  body += "<html lang='en'>";
  body += "<head>";
  body += "<meta charset='UTF-8'>";
  body += "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
  body += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  body += "<link rel='stylesheet' href='/style.css'>";
  body += "<title>Success</title>";
  body += "</head>";
  body += "<body>";
  body += " <div class='header_home'>";
  body += "<h2 class='success-msg'>DONE &#128077</h2>";
  body += "<h2 class='success-msg' style='margin-left: 65%; margin-top: 3%;'>&#128073 Your Trip ID : ";
  body += req -> getQueryParam("id");
  body += "</h2>";
  body += "<div class='success_bg'></div>";
  body += "<div class='success_container'>";
  body += "<a href='/TaxiReq' style='text-decoration: none;'>Get A Taxi</a>";
  body += "<br><br>";
  body += "<a href='/Sbmit' style='text-decoration: none;'>Signup</a>";
  body += "<br><br>";
  body += "<a href='/CancelTrip' style='text-decoration: none;'>Cancel Trip</a>";
  body += "<br><br>";
  body += "<a href='/GetTripsList' style='text-decoration: none;'>Get Trips List</a>";
  body += "</div>";
  body += "</body>";
  body += "</html>";
  res -> setBody(body);
  return res;
}

