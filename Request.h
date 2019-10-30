//
// Created by matthew on 28.10.19.
//

#ifndef ISA_PROJECT_REQUEST_H
#define ISA_PROJECT_REQUEST_H


#include <string>

class Request {
    std::string payload;
public:
    explicit Request(const std::string& raw_request);

    std::string url;
    std::string metod;
};


#endif //ISA_PROJECT_REQUEST_H
