//
// Created by Matej Soroka on 28.10.19.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "Request.h"

Request::Request(const std::string& raw_request) {
    std::istringstream iss(raw_request);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    if (results.size() > 2) {
        this->method = results[0];
        this->url = results[1];
        this->payload = raw_request.substr(raw_request.find("\r\n\r\n") + 4);
    } else {
        this->method = "ERROR";
    }
}

int Request::set_request(const std::string& host, const std::string& url, const std::string& method, const std::string& payload)
{
    this->host = host;
    this->url = url;
    this->method = method;
    this->payload = payload;
    this->raw = this->generate_request();
}

std::string
Request::generate_request()
{
    std::stringstream ss;
    std::string code_msg;

    ss << this->method << " " << this->url << " HTTP/1.1 \n"
       << "Host: " << this->host << "\n"
       << "User-Agent: ISA Client\n"
       << "Content-Type: text/plain\n"
       << "Content-Length: " << this->payload.length() << "\n"
       << "Accept: */*\n\n"
       << this->payload;

    return ss.str();
}

