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
    std::string host;    // host address
    std::string raw;     // raw request
    std::string generate_request();
    int set_request(const std::string &host, const std::string &url, const std::string &method, const std::string &payload);
};


#endif //ISA_PROJECT_REQUEST_H
