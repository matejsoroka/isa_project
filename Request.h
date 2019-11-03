//
// Created by Matej Soroka on 28.10.19.
//

#ifndef ISA_PROJECT_REQUEST_H
#define ISA_PROJECT_REQUEST_H


#include <string>

class Request {
public:
    /**
     * Parse HTTP request
     * @param raw_request HTTP raw request
     */
    explicit Request(const std::string& raw_request);
    std::string url;     // URL
    std::string method;  // HTTP method
    std::string payload; // HTTP payload
};


#endif //ISA_PROJECT_REQUEST_H
