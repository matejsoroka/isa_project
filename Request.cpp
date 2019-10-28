//
// Created by matthew on 28.10.19.
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

    // TODO: if method not in list of methods
    this->metod = results[0];
    // TODO: if method not in list of urls
    this->url = results[1];
}

