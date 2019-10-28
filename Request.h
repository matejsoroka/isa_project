//
// Created by matthew on 28.10.19.
//

#ifndef ISA_PROJECT_REQUEST_H
#define ISA_PROJECT_REQUEST_H


#include <string>

class Request {
    std::string metod;
    std::string url;
    std::string payload;
public:
    explicit Request(const std::string& raw_request);
};


#endif //ISA_PROJECT_REQUEST_H
