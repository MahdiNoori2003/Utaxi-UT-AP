#include "request.hpp"
#include "../utils/utilities.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

Request::Request(string _method) {
  if (_method == "GET")
    method = GET;
  if (_method == "POST")
    method = POST;
}

string Request::getQueryParam(string key) { return urlDecode(query[key]); }

string Request::getBodyParam(string key) { return urlDecode(body[key]); }

string Request::getHeader(string key) { return urlDecode(headers[key]); }

string Request::getPath() { return path; }

void Request::setPath(string _path) { path = _path; }

Method Request::getMethod() { return method; }

void Request::setMethod(Method _method) { method = _method; }

void Request::setQueryParam(string key, string value, bool encode) {
  query[key] = encode ? urlEncode(value) : value;
}

void Request::setBodyParam(string key, string value, bool encode) {
  body[key] = encode ? urlEncode(value) : value;
}

void Request::setHeader(string key, string value, bool encode) {
  headers[key] = encode ? urlEncode(value) : value;
}

string Request::getBody() {
  string bs = "";
  for (auto it = body.begin(); !body.empty() && it != body.end(); it++)
    bs += it->first + "=" + it->second + "&";
  return bs;
}

string Request::getSessionId() {
  string cookie = getHeader("cookie");
  if (cookie == "")
    return "";
  vector<string> v = split(cookie, ";");
  for (string kv : v) {
    vector<string> k = split(kv, "=");
    if (k[0] == "sessionId")
      return k[1];
  }
  return "";
}

void Request::log() {
  const string NC = "\033[0;39m";
  const string K = "\033[1m";
  const string H = "\033[33;1m";
  string log = "";
  log += H + string("------- Request --------") + NC + string("\n");
  log +=
      K + string("Method:\t") + NC + (method ? "POST" : "GET") + string("\n");
  log += K + string("Path:\t") + NC + path + string("\n");
  log += K + string("Headers:") + NC + string("\n");
  for (auto it = headers.begin(); !headers.empty() && it != headers.end(); it++)
    log += "  " + urlDecode(it->first) + ": " + urlDecode(it->second) +
           string("\n");
  log += "[ " + K + string("SessionId:\t") + NC + this->getSessionId() + " ]" +
         string("\n");
  log += K + string("Query:") + NC + string("\n");
  for (auto it = query.begin(); !query.empty() && it != query.end(); it++)
    log += "  " + urlDecode(it->first) + ": " + urlDecode(it->second) +
           string("\n");
  log += K + string("Body:") + NC + string("\n");
  for (auto it = body.begin(); !body.empty() && it != body.end(); it++)
    log += "  " + urlDecode(it->first) + ": " + urlDecode(it->second) +
           string("\n");
  log += H + string("------------------------") + NC + string("\n");
  cerr << log << endl;
}

cimap Request::getHeaders() {
  vector<string> res;
  for (map<string, string>::iterator i = headers.begin();
       !headers.empty() && i != headers.end(); i++) {
    res.push_back(i->first);
    res.push_back(i->second);
  }
  return headers;
}

string Request::getQueryString() {
  if (query.empty())
    return "";
  string res = "?";
  for (map<string, string>::iterator i = query.begin();
       !query.empty() && i != query.end(); i++) {
    res += i->first;
    res += "=";
    res += i->second;
    res += "&";
  }
  return res;
}

string Request::getHeadersString() {
  string headerString = "";
  for (auto it = headers.begin(); !headers.empty() && it != headers.end(); it++)
    headerString += it->first + "=" + it->second + "&";
  return headerString;
}

void Request::setHeaders(string _headers) {
  headers = getCimapFromString(_headers);
}

void Request::setQuery(std::string _query) {
  _query = _query.substr(1);
  query = getCimapFromString(_query);
}

void Request::setBody(std::string _body) { body = getCimapFromString(_body); }

void Request::serializeToFile(Request *req, string filePath) {
  string reqString = to_string(req->getMethod());
  reqString += "\n";
  reqString += req->getPath();
  reqString += "\n";
  reqString += req->getHeadersString();
  reqString += "\n";
  reqString += req->getBody();
  reqString += "\n";
  reqString += req->getQueryString();
  writeToFile(reqString, filePath);
}

void Request::deserializeFromFile(Request *req, string filePath) {
  vector<string> fields = tokenize(readFile(filePath), '\n');
  switch (fields.size()) {
  case 5:
    req->setQuery(fields[4]);
  case 4:
    req->setBody(fields[3]);
  case 3:
    req->setHeaders(fields[2]);
  case 2:
    req->setPath(fields[1]);
  case 1:
    req->setMethod(stoi(fields[0]) == GET ? GET : POST);
  }
}