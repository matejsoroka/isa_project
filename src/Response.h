//
// Created by Matej Soroka on 28.10.19.
//

#ifndef ISA_PROJECT_RESPONSE_H
#define ISA_PROJECT_RESPONSE_H


#include <string>

class Response {
public:
    int code;             // return code
    std::string payload;  // payload
    std::string raw;      // raw generated response

    /**
     * Generate date for HTTP response
     * @return date for HTTP response
     */
    static std::string generate_date();

    /**
     * Generate response with all data
     * @return HTTP response
     */
    std::string generate_response();
};


#endif //ISA_PROJECT_RESPONSE_H
