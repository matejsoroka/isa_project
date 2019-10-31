//
// Created by matthew on 28.10.19.
//

#ifndef ISA_PROJECT_RESPONSE_H
#define ISA_PROJECT_RESPONSE_H


#include <string>

class Response {
public:
    int code;
    std::string payload;
    std::string date;
    std::string raw;
    static std::string generate_date();
    std::string generate_response();
};


#endif //ISA_PROJECT_RESPONSE_H
