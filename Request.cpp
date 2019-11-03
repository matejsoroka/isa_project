//
// Created by Matej Soroka on 28.10.19.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "Request.h"

Request::Request(const std::string& raw_request)
{
    std::istringstream iss(raw_request);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    this->method = results[0];
    this->url = results[1];
    this->payload = raw_request.substr(raw_request.find("\r\n\r\n") + 4);
}

